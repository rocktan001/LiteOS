ifeq ($(LOSCFG_ARCH_ARM_AARCH32), y)
-include $(LITEOSTOPDIR)/arch/arm/cpu.mk
endif

ifeq ($(LOSCFG_ARCH_ARM_AARCH64), y)
-include $(LITEOSTOPDIR)/arch/arm64/cpu.mk
endif

