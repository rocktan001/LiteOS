include $(LITEOSTOPDIR)/config.mk

MODULE_NAME     := $(notdir $(CURDIR))

LOCAL_SRCS_$(LOSCFG_ARM_GENERIC_TIMER) += arm_generic_timer.c
LOCAL_SRCS_$(LOSCFG_ARM_PRIVATE_TIMER) += arm_private_timer.c
LOCAL_SRCS_$(LOSCFG_CORTEX_M_SYSTICK) += cortex_m_systick.c
LOCAL_SRCS_$(LOSCFG_ARM_SP804_TIMER) += arm_sp804_timer.c
LOCAL_SRCS_$(LOSCFG_XTENSA_LX6_TIMER) += xtensa_lx6_timer.c
LOCAL_SRCS_$(LOSCFG_XTENSA_XEA2_TIMER) += xtensa_xea2_timer.c
LOCAL_SRCS_$(LOSCFG_XTENSA_XEA3_TIMER) += xtensa_xea3_timer.c
LOCAL_SRCS_$(LOSCFG_RISCV32_M_TIMER) += riscv32_mtimer.c
LOCAL_SRCS_$(LOSCFG_ARM_SP804_HRTIMER) += arm_sp804_hrtimer.c
LOCAL_SRCS_$(LOSCFG_CSKY_SYSTICK) += csky_systick.c

ifeq ($(LOSCFG_KERNEL_SMP), y)
LOCAL_SRCS_$(LOSCFG_RASPBERRY_PI_SYSTICK) += arm_generic_timer.c
else
LOCAL_SRCS_$(LOSCFG_RASPBERRY_PI_SYSTICK) += rasp_systick.c
endif

LOCAL_SRCS = $(LOCAL_SRCS_y)

LOCAL_FLAGS := $(PLATFORM_INCLUDE) $(PLATFORM_DEFS) $(LITEOS_GCOV_OPTS)

include $(MODULE)
