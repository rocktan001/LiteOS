include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := $(LOSCFG_ARCH_CPU)

LOCAL_SRCS := src/los_hw.c \
              src/los_hw_tick.c \
              src/los_exc.c
LOCAL_INCLUDE := -I $(LITEOSTOPDIR)/kernel/extended/include

ASSRCS = $(wildcard src/*.S)
LOCAL_SRCS += $(ASSRCS)

LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

include $(MODULE)
