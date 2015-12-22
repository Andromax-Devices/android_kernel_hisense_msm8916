/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/delay.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/reboot.h>
#include <linux/pm.h>
#include <linux/delay.h>
#include <linux/qpnp/power-on.h>
#include <linux/of_address.h>

#include <asm/cacheflush.h>
#include <asm/system_misc.h>

#include <soc/qcom/scm.h>
#include <soc/qcom/restart.h>
#include <soc/qcom/watchdog.h>

#define EMERGENCY_DLOAD_MAGIC1    0x322A4F99
#define EMERGENCY_DLOAD_MAGIC2    0xC67E4350
#define EMERGENCY_DLOAD_MAGIC3    0x77777777

#define SCM_IO_DISABLE_PMIC_ARBITER	1
#define SCM_WDOG_DEBUG_BOOT_PART	0x9
#define SCM_DLOAD_MODE			0X10
#define SCM_EDLOAD_MODE			0X01
#define SCM_DLOAD_CMD			0x10


static int restart_mode;
void *restart_reason;
static bool scm_pmic_arbiter_disable_supported;
/* Download mode master kill-switch */
static void __iomem *msm_ps_hold;

#ifdef CONFIG_MSM_DLOAD_MODE
#define EDL_MODE_PROP "qcom,msm-imem-emergency_download_mode"
#define DL_MODE_PROP "qcom,msm-imem-download_mode"

static int in_panic;
static void *dload_mode_addr;
static bool dload_mode_enabled;
static void *emergency_dload_mode_addr;
static bool scm_dload_supported;

static int dload_set(const char *val, struct kernel_param *kp);
static int download_mode = 1;
module_param_call(download_mode, dload_set, param_get_int,
			&download_mode, 0644);
static int panic_prep_restart(struct notifier_block *this,
			      unsigned long event, void *ptr)
{
	in_panic = 1;
	return NOTIFY_DONE;
}

static struct notifier_block panic_blk = {
	.notifier_call	= panic_prep_restart,
};

#ifdef CONFIG_HS_PANIC_HANDLE
#include <soc/qcom/subsystem_restart.h>
extern void set_subsys_restart_level(int restart_level);
extern void hs_set_pm_pon_reset(int debug);
static void set_dload_mode(int on);

static int debug_flag = 0;
static struct delayed_work check_lk_flag_work;
static int is_built_in_battery = 0;

void hs_enable_debug(int value)
{
	if (0 == value)
	{
		debug_flag = 0;
		// 子系统异常，只重启子系统
		set_subsys_restart_level(RESET_SUBSYS_COUPLED);
		hs_set_pm_pon_reset(0);
		set_dload_mode(1);
	}
	else
	{
		debug_flag = 1;
		// 子系统异常，整个系统重启
		set_subsys_restart_level(RESET_SOC);
		hs_set_pm_pon_reset(1);
		set_dload_mode(1);
	}
}

static ssize_t debug_flag_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	int value;

	if (sscanf(buf, "%d", &value) != 1){
		printk(KERN_ERR "debug_store: sscanf is wrong! \n");
		return -EINVAL;
	}

	hs_enable_debug(value);

	return len;
}

static ssize_t debug_flag_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", debug_flag);
}

static DEVICE_ATTR(debug_flag, S_IWUSR | S_IWGRP | S_IRUGO,
		debug_flag_show, debug_flag_store);

static struct attribute *msm_poweroff_attrs[] = {
	&dev_attr_debug_flag.attr,
	NULL,
};

static struct attribute_group msm_poweroff_attr_group = {
	.attrs = msm_poweroff_attrs,
};

static void hs_debug_control_init(void)
{
	int ret;
	struct kobject *debug_kobj;

	debug_kobj = kobject_create_and_add("debug_control", NULL);
	if (!debug_kobj)
	{
		printk(KERN_ERR "hs_msm_poweroff_init: kobject create Failed!\n");
		return;
	}
	
	ret = sysfs_create_group(debug_kobj, &msm_poweroff_attr_group);
	if (ret < 0) 
	{
		printk(KERN_ERR "Error creating poweroff sysfs group\n");
		return;
	}

	printk(KERN_INFO "hs_msm_poweroff_init: OK.\n");
	return;
}

static void hs_check_lk_flag_work(struct work_struct *work)
{
	printk(KERN_INFO "hs_check_lk_flag_work enter\n");

	hs_enable_debug(1);
}

static void hs_check_lk_flag(void)
{
#define LK_ENABLE_DBG_FLAG				(0x4847<<16)
#define BUILT_IN_BATTERY_FLAG			(1<<0)
	int read_data = 0;

	if (dload_mode_addr) 
	{
		read_data = __raw_readl(dload_mode_addr + 2*sizeof(unsigned int));
		if (LK_ENABLE_DBG_FLAG == (read_data & 0xffff0000))
		{
			printk(KERN_INFO "LK set debug enable.\n");
			debug_flag = 1;
			INIT_DELAYED_WORK(&check_lk_flag_work, hs_check_lk_flag_work);
			schedule_delayed_work(&check_lk_flag_work, msecs_to_jiffies(5000));
		}

		if (read_data & BUILT_IN_BATTERY_FLAG)
		{
			printk(KERN_INFO "HS Built In Battery!\n");
			is_built_in_battery = 1;
		}
		else
		{
			printk(KERN_INFO "HS Not Built In Battery!\n");
		}
	}
}

int hs_is_built_in_battery(void)
{
	return is_built_in_battery;
}

#endif	/*#ifdef CONFIG_HS_PANIC_HANDLE*/


int scm_set_dload_mode(int arg1, int arg2)
{
	struct scm_desc desc = {
		.args[0] = arg1,
		.args[1] = arg2,
		.arginfo = SCM_ARGS(2),
	};

	if (!scm_dload_supported)
		return 0;

	if (!is_scm_armv8())
		return scm_call_atomic2(SCM_SVC_BOOT, SCM_DLOAD_CMD, arg1,
					arg2);

	return scm_call2_atomic(SCM_SIP_FNID(SCM_SVC_BOOT, SCM_DLOAD_CMD),
				&desc);
}

static void set_dload_mode(int on)
{
	int ret;

	if (dload_mode_addr) {
#ifdef CONFIG_HS_PANIC_HANDLE
#ifdef CONFIG_MSM_RELEASE_VERSION
		if(restart_mode != RESTART_DLOAD)
		{
			if (1 == debug_flag)
			{
				__raw_writel(on ? 0xE47B337D : 0, dload_mode_addr);
			}
			else
			{
				__raw_writel(on ? 0xE47B337C : 0, dload_mode_addr);
			}
		}
		else
			__raw_writel(on ? 0xE47B337E : 0, dload_mode_addr);
#else	/*#ifdef CONFIG_MSM_RELEASE_VERSION*/
		if(restart_mode != RESTART_DLOAD)
			__raw_writel(on ? 0xE47B337D : 0, dload_mode_addr);
		else
			__raw_writel(on ? 0xE47B337E : 0, dload_mode_addr);
#endif	/*#ifdef CONFIG_MSM_RELEASE_VERSION*/

#else	/*#ifdef CONFIG_HS_PANIC_HANDLE*/
		__raw_writel(on ? 0xE47B337D : 0, dload_mode_addr);
#endif	/*#ifdef CONFIG_HS_PANIC_HANDLE*/

		__raw_writel(on ? 0xCE14091A : 0,
		       dload_mode_addr + sizeof(unsigned int));
		mb();
	}

	ret = scm_set_dload_mode(on ? SCM_DLOAD_MODE : 0, 0);
	if (ret)
		pr_err("Failed to set secure DLOAD mode: %d\n", ret);

	dload_mode_enabled = on;
}

static bool get_dload_mode(void)
{
	return dload_mode_enabled;
}

static void enable_emergency_dload_mode(void)
{
	int ret;

	if (emergency_dload_mode_addr) {
		__raw_writel(EMERGENCY_DLOAD_MAGIC1,
				emergency_dload_mode_addr);
		__raw_writel(EMERGENCY_DLOAD_MAGIC2,
				emergency_dload_mode_addr +
				sizeof(unsigned int));
		__raw_writel(EMERGENCY_DLOAD_MAGIC3,
				emergency_dload_mode_addr +
				(2 * sizeof(unsigned int)));

		/* Need disable the pmic wdt, then the emergency dload mode
		 * will not auto reset. */
		qpnp_pon_wd_config(0);
		mb();
	}

	ret = scm_set_dload_mode(SCM_EDLOAD_MODE, 0);
	if (ret)
		pr_err("Failed to set secure EDLOAD mode: %d\n", ret);
}

static int dload_set(const char *val, struct kernel_param *kp)
{
	int ret;
	int old_val = download_mode;

	ret = param_set_int(val, kp);

	if (ret)
		return ret;

	/* If download_mode is not zero or one, ignore. */
	if (download_mode >> 1) {
		download_mode = old_val;
		return -EINVAL;
	}

	set_dload_mode(download_mode);

	return 0;
}
#else
#define set_dload_mode(x) do {} while (0)

static void enable_emergency_dload_mode(void)
{
	pr_err("dload mode is not enabled on target\n");
}

static bool get_dload_mode(void)
{
	return false;
}
#endif

void msm_set_restart_mode(int mode)
{
	restart_mode = mode;
}
EXPORT_SYMBOL(msm_set_restart_mode);

/*
 * Force the SPMI PMIC arbiter to shutdown so that no more SPMI transactions
 * are sent from the MSM to the PMIC.  This is required in order to avoid an
 * SPMI lockup on certain PMIC chips if PS_HOLD is lowered in the middle of
 * an SPMI transaction.
 */
static void halt_spmi_pmic_arbiter(void)
{
	struct scm_desc desc = {
		.args[0] = 0,
		.arginfo = SCM_ARGS(1),
	};

	if (scm_pmic_arbiter_disable_supported) {
		pr_crit("Calling SCM to disable SPMI PMIC arbiter\n");
		if (!is_scm_armv8())
			scm_call_atomic1(SCM_SVC_PWR,
					 SCM_IO_DISABLE_PMIC_ARBITER, 0);
		else
			scm_call2_atomic(SCM_SIP_FNID(SCM_SVC_PWR,
				  SCM_IO_DISABLE_PMIC_ARBITER), &desc);
	}
}

static void msm_restart_prepare(const char *cmd)
{
#ifdef CONFIG_MSM_DLOAD_MODE

	/* Write download mode flags if we're panic'ing
	 * Write download mode flags if restart_mode says so
	 * Kill download mode if master-kill switch is set
	 */

	set_dload_mode(download_mode &&
			(in_panic || restart_mode == RESTART_DLOAD));
#endif

	/* Hard reset the PMIC unless memory contents must be maintained. */
	if (get_dload_mode() || (cmd != NULL && cmd[0] != '\0'))
		qpnp_pon_system_pwr_off(PON_POWER_OFF_WARM_RESET);
	else
		qpnp_pon_system_pwr_off(PON_POWER_OFF_HARD_RESET);

	if (cmd != NULL) {
		if (!strncmp(cmd, "bootloader", 10)) {
			__raw_writel(0x77665500, restart_reason);
		} else if (!strncmp(cmd, "recovery", 8)) {
			__raw_writel(0x77665502, restart_reason);
		} else if (!strcmp(cmd, "rtc")) {
			__raw_writel(0x77665503, restart_reason);
		} else if (!strncmp(cmd, "oem-", 4)) {
			unsigned long code;
			int ret;
			ret = kstrtoul(cmd + 4, 16, &code);
			if (!ret)
				__raw_writel(0x6f656d00 | (code & 0xff),
					     restart_reason);
		} else if (!strncmp(cmd, "edl", 3)) {
			enable_emergency_dload_mode();
		} else if (!strncmp(cmd, "forcedl", 7)) {
			__raw_writel(0x776655bb, restart_reason);
		} else if (!strncmp(cmd, "hs-pwroff-chg", 13)) {
			__raw_writel(0x77665512, restart_reason);
		} else if (!strncmp(cmd, "hs-cts-test", 11)) {
			__raw_writel(0x77665513, restart_reason);
		} else {
			qpnp_pon_system_pwr_off(PON_POWER_OFF_HARD_RESET);
		}
	} else
		__raw_writel(0x77665501, restart_reason); 

	flush_cache_all();

	/*outer_flush_all is not supported by 64bit kernel*/
#ifndef CONFIG_ARM64
	outer_flush_all();
#endif

}

static void do_msm_restart(enum reboot_mode reboot_mode, const char *cmd)
{
	int ret;
	struct scm_desc desc = {
		.args[0] = 1,
		.args[1] = 0,
		.arginfo = SCM_ARGS(2),
	};

	pr_notice("Going down for restart now\n");

	msm_restart_prepare(cmd);

#ifdef CONFIG_MSM_DLOAD_MODE
	/*
	 * Trigger a watchdog bite here and if this fails,
	 * device will take the usual restart path.
	 */

	if (WDOG_BITE_ON_PANIC && in_panic)
		msm_trigger_wdog_bite();
#endif

	/* Needed to bypass debug image on some chips */
	if (!is_scm_armv8())
		ret = scm_call_atomic2(SCM_SVC_BOOT,
			       SCM_WDOG_DEBUG_BOOT_PART, 1, 0);
	else
		ret = scm_call2_atomic(SCM_SIP_FNID(SCM_SVC_BOOT,
			  SCM_WDOG_DEBUG_BOOT_PART), &desc);
	if (ret)
		pr_err("Failed to disable secure wdog debug: %d\n", ret);

	halt_spmi_pmic_arbiter();
	__raw_writel(0, msm_ps_hold);

	mdelay(10000);
}

static void do_msm_poweroff(void)
{
	int ret;
	struct scm_desc desc = {
		.args[0] = 1,
		.args[1] = 0,
		.arginfo = SCM_ARGS(2),
	};

	pr_notice("Powering off the SoC\n");
#ifdef CONFIG_MSM_DLOAD_MODE
	set_dload_mode(0);
#endif
	qpnp_pon_system_pwr_off(PON_POWER_OFF_SHUTDOWN);
	/* Needed to bypass debug image on some chips */
	if (!is_scm_armv8())
		ret = scm_call_atomic2(SCM_SVC_BOOT,
			       SCM_WDOG_DEBUG_BOOT_PART, 1, 0);
	else
		ret = scm_call2_atomic(SCM_SIP_FNID(SCM_SVC_BOOT,
			  SCM_WDOG_DEBUG_BOOT_PART), &desc);
	if (ret)
		pr_err("Failed to disable wdog debug: %d\n", ret);

	halt_spmi_pmic_arbiter();
	/* MSM initiated power off, lower ps_hold */
	__raw_writel(0, msm_ps_hold);

	mdelay(10000);
	pr_err("Powering off has failed\n");
	return;
}

static int msm_restart_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *mem;
	struct device_node *np;
	int ret = 0;

#ifdef CONFIG_MSM_DLOAD_MODE
	if (scm_is_call_available(SCM_SVC_BOOT, SCM_DLOAD_CMD) > 0)
		scm_dload_supported = true;

	atomic_notifier_chain_register(&panic_notifier_list, &panic_blk);
	np = of_find_compatible_node(NULL, NULL, DL_MODE_PROP);
	if (!np) {
		pr_err("unable to find DT imem DLOAD mode node\n");
	} else {
		dload_mode_addr = of_iomap(np, 0);
		if (!dload_mode_addr)
			pr_err("unable to map imem DLOAD offset\n");
	}

	np = of_find_compatible_node(NULL, NULL, EDL_MODE_PROP);
	if (!np) {
		pr_err("unable to find DT imem EDLOAD mode node\n");
	} else {
		emergency_dload_mode_addr = of_iomap(np, 0);
		if (!emergency_dload_mode_addr)
			pr_err("unable to map imem EDLOAD mode offset\n");
	}

#ifdef CONFIG_HS_PANIC_HANDLE
	hs_check_lk_flag();
#endif	/*#ifdef CONFIG_HS_PANIC_HANDLE*/
	set_dload_mode(download_mode);
#endif
	np = of_find_compatible_node(NULL, NULL,
				"qcom,msm-imem-restart_reason");
	if (!np) {
		pr_err("unable to find DT imem restart reason node\n");
	} else {
		restart_reason = of_iomap(np, 0);
		if (!restart_reason) {
			pr_err("unable to map imem restart reason offset\n");
			ret = -ENOMEM;
			goto err_restart_reason;
		}
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	msm_ps_hold = devm_ioremap_resource(dev, mem);
	if (IS_ERR(msm_ps_hold))
		return PTR_ERR(msm_ps_hold);

	pm_power_off = do_msm_poweroff;
	arm_pm_restart = do_msm_restart;

	if (scm_is_call_available(SCM_SVC_PWR, SCM_IO_DISABLE_PMIC_ARBITER) > 0)
		scm_pmic_arbiter_disable_supported = true;

#ifdef CONFIG_HS_PANIC_HANDLE
	hs_debug_control_init();
#endif	/*#ifdef CONFIG_HS_PANIC_HANDLE*/

	return 0;

err_restart_reason:
#ifdef CONFIG_MSM_DLOAD_MODE
	iounmap(emergency_dload_mode_addr);
	iounmap(dload_mode_addr);
#endif
	return ret;
}

static const struct of_device_id of_msm_restart_match[] = {
	{ .compatible = "qcom,pshold", },
	{},
};
MODULE_DEVICE_TABLE(of, of_msm_restart_match);

static struct platform_driver msm_restart_driver = {
	.probe = msm_restart_probe,
	.driver = {
		.name = "msm-restart",
		.of_match_table = of_match_ptr(of_msm_restart_match),
	},
};

static int __init msm_restart_init(void)
{
	return platform_driver_register(&msm_restart_driver);
}
device_initcall(msm_restart_init);
