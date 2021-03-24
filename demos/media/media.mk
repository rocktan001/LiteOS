DEMOS_MEDIA_INCLUDE :=

ifeq ($(LOSCFG_DEMOS_OPUS), y)
include $(LITEOSTOPDIR)/demos/media/opus/opus.mk
DEMOS_MEDIA_INCLUDE += $(DEMOS_OPUS_INCLUDE)
endif
