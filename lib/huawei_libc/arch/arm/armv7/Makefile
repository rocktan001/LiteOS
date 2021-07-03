include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := csysdeps

LOCAL_INCLUDE :=

LOCAL_SRCS := memcmp.S strcmp.S
ifeq ($(LOSCFG_ARCH_FPU_VFP_NEON), y)
ifeq ($(LOSCFG_PLATFORM_Raspberry_Pi2B), y)
	LOCAL_SRCS += memset.c
else
	LOCAL_SRCS += memset.S
endif
	
endif

LOCAL_ASFLAGS := $(AS_OBJS_LIBC_FLAGS)

LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

include $(MODULE_LIBC)
