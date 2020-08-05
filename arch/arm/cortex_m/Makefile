include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := $(LOSCFG_ARCH_CPU)

LOCAL_SRCS += $(wildcard $(MODULE_NAME)/gcc/*.S) $(wildcard src/*.c) $(wildcard ../../common/*.c) $(wildcard $(MODULE_NAME)/*.c)

LOCAL_INCLUDE := \
    -I $(LITEOSTOPDIR)/kernel/extended/include \
    -I $(LITEOSTOPDIR)/kernel/base/include

LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

ifeq ($(LOSCFG_GDB), y)
LOCAL_FLAGS += $(AS_OBJS_LIBC_FLAGS)
endif
include $(MODULE)
