cmd_scripts/kconfig/zconf.tab.o := gcc -Wp,-MD,scripts/kconfig/.zconf.tab.o.d -Iscripts/kconfig -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -DCURSES_LOC="<curses.h>" -DLOCALE -DKBUILD_NO_NLS  -I/cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig -Iscripts/kconfig -c -o scripts/kconfig/zconf.tab.o scripts/kconfig/zconf.tab.c

source_scripts/kconfig/zconf.tab.o := scripts/kconfig/zconf.tab.c

deps_scripts/kconfig/zconf.tab.o := \
  /usr/include/ctype.h \
  /usr/include/_ansi.h \
  /usr/include/newlib.h \
  /usr/include/sys/config.h \
    $(wildcard include/config/h//.h) \
  /usr/include/machine/ieeefp.h \
  /usr/include/sys/features.h \
  /usr/include/cygwin/config.h \
    $(wildcard include/config/h.h) \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdarg.h \
  /usr/include/stdio.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stddef.h \
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
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdbool.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/lkc.h \
    $(wildcard include/config/.h) \
    $(wildcard include/config/prefix.h) \
    $(wildcard include/config/list.h) \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/expr.h \
  /usr/include/assert.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/list.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/lkc_proto.h \
  scripts/kconfig/zconf.hash.c \
  scripts/kconfig/zconf.lex.c \
  /usr/include/errno.h \
  /usr/include/sys/errno.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/limits.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/syslimits.h \
  /usr/include/limits.h \
  /usr/include/features.h \
  /usr/include/unistd.h \
  /usr/include/sys/unistd.h \
  /usr/include/getopt.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/util.c \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/lkc.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/confdata.c \
    $(wildcard include/config/config.h) \
    $(wildcard include/config/autoconfig.h) \
    $(wildcard include/config/overwriteconfig.h) \
    $(wildcard include/config/autoheader.h) \
    $(wildcard include/config/tristate.h) \
    $(wildcard include/config/probability.h) \
  /usr/include/sys/stat.h \
  /usr/include/time.h \
  /usr/include/machine/time.h \
  /usr/include/cygwin/time.h \
  /usr/include/signal.h \
  /usr/include/sys/signal.h \
  /usr/include/cygwin/signal.h \
  /usr/include/cygwin/stat.h \
  /usr/include/fcntl.h \
  /usr/include/sys/fcntl.h \
  /usr/include/sys/_default_fcntl.h \
  /usr/include/sys/time.h \
  /usr/include/cygwin/sys_time.h \
  /usr/include/sys/select.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/expr.c \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/symbol.c \
  /usr/include/regex.h \
  /usr/include/sys/utsname.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/kconfig/menu.c \

scripts/kconfig/zconf.tab.o: $(deps_scripts/kconfig/zconf.tab.o)

$(deps_scripts/kconfig/zconf.tab.o):
