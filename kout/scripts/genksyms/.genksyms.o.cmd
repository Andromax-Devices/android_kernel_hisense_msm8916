cmd_scripts/genksyms/genksyms.o := gcc -Wp,-MD,scripts/genksyms/.genksyms.o.d -Iscripts/genksyms -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -c -o scripts/genksyms/genksyms.o /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/genksyms/genksyms.c

source_scripts/genksyms/genksyms.o := /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/genksyms/genksyms.c

deps_scripts/genksyms/genksyms.o := \
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
  /usr/include/unistd.h \
  /usr/include/sys/unistd.h \
  /usr/include/getopt.h \
  /usr/include/assert.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/genksyms/genksyms.h \

scripts/genksyms/genksyms.o: $(deps_scripts/genksyms/genksyms.o)

$(deps_scripts/genksyms/genksyms.o):
