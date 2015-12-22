cmd_scripts/kconfig/conf.o := gcc -Wp,-MD,scripts/kconfig/.conf.o.d -Iscripts/kconfig -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -DCURSES_LOC="<curses.h>" -DLOCALE -DKBUILD_NO_NLS -c -o scripts/kconfig/conf.o /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/conf.c

source_scripts/kconfig/conf.o := /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/conf.c

deps_scripts/kconfig/conf.o := \
    $(wildcard include/config/.h) \
    $(wildcard include/config/seed.h) \
    $(wildcard include/config/allconfig.h) \
    $(wildcard include/config/nosilentupdate.h) \
  /usr/include/locale.h \
  /usr/include/_ansi.h \
  /usr/include/newlib.h \
  /usr/include/sys/config.h \
    $(wildcard include/config/h//.h) \
  /usr/include/machine/ieeefp.h \
  /usr/include/sys/features.h \
  /usr/include/cygwin/config.h \
    $(wildcard include/config/h.h) \
  /usr/include/ctype.h \
  /usr/include/stdio.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stddef.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdarg.h \
  /usr/include/sys/reent.h \
  /usr/include/_ansi.h \
  /usr/include/sys/_types.h \
  /usr/include/machine/_types.h \
  /usr/include/machine/_default_types.h \
  /usr/include/sys/lock.h \
  /usr/include/sys/types.h \
  /usr/include/machine/types.h \
  /usr/include/cygwin/types.h \
  /usr/include/sys/sysmacros.h \
  /usr/include/stdint.h \
  /usr/include/endian.h \
  /usr/include/bits/endian.h \
  /usr/include/byteswap.h \
  /usr/include/sys/stdio.h \
  /usr/include/sys/cdefs.h \
  /usr/include/stdlib.h \
  /usr/include/machine/stdlib.h \
  /usr/include/alloca.h \
  /usr/include/cygwin/stdlib.h \
  /usr/include/cygwin/wait.h \
  /usr/include/string.h \
  /usr/include/sys/string.h \
  /usr/include/time.h \
  /usr/include/machine/time.h \
  /usr/include/cygwin/time.h \
  /usr/include/signal.h \
  /usr/include/sys/signal.h \
  /usr/include/cygwin/signal.h \
  /usr/include/unistd.h \
  /usr/include/sys/unistd.h \
  /usr/include/getopt.h \
  /usr/include/sys/stat.h \
  /usr/include/cygwin/stat.h \
  /usr/include/sys/time.h \
  /usr/include/cygwin/sys_time.h \
  /usr/include/sys/select.h \
  /usr/include/errno.h \
  /usr/include/sys/errno.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/lkc.h \
    $(wildcard include/config/prefix.h) \
    $(wildcard include/config/list.h) \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/expr.h \
  /usr/include/assert.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/list.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdbool.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/lkc_proto.h \

scripts/kconfig/conf.o: $(deps_scripts/kconfig/conf.o)

$(deps_scripts/kconfig/conf.o):
