DEMOS_MEDIA_INCLUDE :=

ifeq ($(LOSCFG_DEMOS_LIBPNG), y)
include $(LITEOSTOPDIR)/demos/media/libpng/libpng.mk
DEMOS_MEDIA_INCLUDE += $(DEMOS_LIBPNG_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_OPUS), y)
include $(LITEOSTOPDIR)/demos/media/opus/opus.mk
DEMOS_MEDIA_INCLUDE += $(DEMOS_OPUS_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_OPENEXIF), y)
include $(LITEOSTOPDIR)/demos/media/openexif/openexif.mk
DEMOS_MEDIA_INCLUDE += $(DEMOS_OPENEXIF_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_UPNP), y)
include $(LITEOSTOPDIR)/demos/media/upnp/upnp.mk
DEMOS_INCLUDE += $(DEMOS_UPNP_INCLUDE)
endif