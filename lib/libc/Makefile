include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := c

LOCAL_SRCS = $(wildcard ../hw/*.c) \
             $(wildcard src/errno/*.c) \
             $(wildcard src/exit/*.c) \
             $(wildcard src/string/*.c) \
             $(wildcard src/stdio/*.c) \
             $(wildcard src/stdlib/*.c) \
             $(wildcard src/prng/*.c) \
             $(wildcard src/multibyte/*.c) \
             $(wildcard src/internal/*.c) \
             $(wildcard src/time/*.c) \
             $(wildcard src/env/*.c) \
             $(wildcard src/misc/*.c) \
             $(wildcard src/locale/*.c) \
             $(wildcard src/ctype/*.c) \
             $(wildcard src/temp/*.c) \
             $(wildcard src/linux/*.c) \
             $(wildcard src/fcntl/*.c) \
             $(wildcard src/process/*.c) \
             $(wildcard src/legacy/*.c) \
             $(wildcard src/thread/*.c) \
             $(wildcard src/signal/*.c) \
             $(wildcard src/network/*.c) \
             $(wildcard src/unistd/*.c) \
             $(wildcard src/termios/*.c)

LOCAL_INCLUDE := -I $(LITEOSTOPDIR)/lib/libc/arch/generic \
    -I $(LITEOSTOPDIR)/lib/libc/src/internal \
    -I $(LITEOSTOPDIR)/lib/libc/src/crypt \
    -I $(LITEOSTOPDIR)/lib/libc/src/ctype \
    -I $(LITEOSTOPDIR)/lib/libc/src/dirent \
    -I $(LITEOSTOPDIR)/lib/libc/src/errno \
    -I $(LITEOSTOPDIR)/lib/libc/src/ipc \
    -I $(LITEOSTOPDIR)/lib/libc/src/locale \
    -I $(LITEOSTOPDIR)/lib/libc/src/math \
    -I $(LITEOSTOPDIR)/lib/libc/src/multibyte \
    -I $(LITEOSTOPDIR)/lib/libc/src/networknetwork \
    -I $(LITEOSTOPDIR)/lib/libc/src/passwd \
    -I $(LITEOSTOPDIR)/lib/libc/src/prng \
    -I $(LITEOSTOPDIR)/lib/libc/src/process \
    -I $(LITEOSTOPDIR)/lib/libc/src/regex \
    -I $(LITEOSTOPDIR)/lib/libc/src/search \
    -I $(LITEOSTOPDIR)/lib/libc/src/time \
    -I $(LITEOSTOPDIR)/drivers/random/dev/random \
    -I $(LITEOSTOPDIR)/compat/linux/include \
    -I $(LITEOSTOPDIR)/compat/posix/src

ifeq ($(LOSCFG_LLTSER), y)
LOCAL_INCLUDE += -I $(LITEOSTOPDIR)/tools/gcov_ser
endif

LOCAL_FLAGS := $(LOCAL_INCLUDE)

include $(MODULE)
