cmd_scripts/dtc/fstree.o := gcc -Wp,-MD,scripts/dtc/.fstree.o.d -Iscripts/dtc -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer  -I/cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/dtc -Iscripts/dtc  -I/cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/dtc/libfdt -Iscripts/dtc/libfdt -c -o scripts/dtc/fstree.o /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/dtc/fstree.c

source_scripts/dtc/fstree.o := /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/dtc/fstree.c

deps_scripts/dtc/fstree.o := \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/dtc/dtc.h \
  /usr/include/stdio.h \
  /usr/include/_ansi.h \
  /usr/include/newlib.h \
  /usr/include/sys/config.h \
    $(wildcard include/config/h//.h) \
  /usr/include/machine/ieeefp.h \
  /usr/include/sys/features.h \
  /usr/include/cygwin/config.h \
    $(wildcard include/config/h.h) \
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
  /usr/include/string.h \
  /usr/include/sys/string.h \
  /usr/include/stdlib.h \
  /usr/include/machine/stdlib.h \
  /usr/include/alloca.h \
  /usr/include/cygwin/stdlib.h \
  /usr/include/cygwin/wait.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/stdbool.h \
  /usr/include/assert.h \
  /usr/include/ctype.h \
  /usr/include/errno.h \
  /usr/include/sys/errno.h \
  /usr/include/unistd.h \
  /usr/include/sys/unistd.h \
  /usr/include/getopt.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/dtc/libfdt/libfdt_env.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/dtc/libfdt/fdt.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/dtc/util.h \
  /usr/include/dirent.h \
  /usr/include/sys/dirent.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/limits.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/syslimits.h \
  /usr/include/limits.h \
  /usr/include/features.h \
  /usr/include/sys/stat.h \
  /usr/include/time.h \
  /usr/include/machine/time.h \
  /usr/include/cygwin/time.h \
  /usr/include/signal.h \
  /usr/include/sys/signal.h \
  /usr/include/cygwin/signal.h \
  /usr/include/cygwin/stat.h \

scripts/dtc/fstree.o: $(deps_scripts/dtc/fstree.o)

$(deps_scripts/dtc/fstree.o):
