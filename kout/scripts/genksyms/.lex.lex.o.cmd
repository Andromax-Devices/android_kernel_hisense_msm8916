cmd_scripts/genksyms/lex.lex.o := gcc -Wp,-MD,scripts/genksyms/.lex.lex.o.d -Iscripts/genksyms -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer  -I/cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/genksyms -Iscripts/genksyms -c -o scripts/genksyms/lex.lex.o scripts/genksyms/lex.lex.c

source_scripts/genksyms/lex.lex.o := scripts/genksyms/lex.lex.c

deps_scripts/genksyms/lex.lex.o := \
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
  /usr/include/errno.h \
  /usr/include/sys/errno.h \
  /usr/include/stdlib.h \
  /usr/include/machine/stdlib.h \
  /usr/include/alloca.h \
  /usr/include/cygwin/stdlib.h \
  /usr/include/cygwin/wait.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/limits.h \
  /usr/lib/gcc/i686-pc-cygwin/3.4.4/include/syslimits.h \
  /usr/include/limits.h \
  /usr/include/features.h \
  /usr/include/ctype.h \
  /cygdrive/d/BaiduYunDownload/Hisense_kernel/scripts/genksyms/genksyms.h \
  scripts/genksyms/parse.tab.h \
  /usr/include/unistd.h \
  /usr/include/sys/unistd.h \
  /usr/include/getopt.h \
  scripts/genksyms/keywords.hash.c \

scripts/genksyms/lex.lex.o: $(deps_scripts/genksyms/lex.lex.o)

$(deps_scripts/genksyms/lex.lex.o):
