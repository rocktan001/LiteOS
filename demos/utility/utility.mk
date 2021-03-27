DEMOS_UTILITY_INCLUDE :=

ifeq ($(LOSCFG_DEMOS_ICONV), y)
include $(LITEOSTOPDIR)/demos/utility/iconv/iconv.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_ICONV_INCLUDE)
endif
ifeq ($(LOSCFG_DEMOS_INIPARSER), y)
include $(LITEOSTOPDIR)/demos/utility/iniparser/iniparser.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_INIPARSER_INCLUDE)
endif
ifeq ($(LOSCFG_DEMOS_BIDIREFERENCE), y)
include $(LITEOSTOPDIR)/demos/utility/bidireference/bidireference.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_BIDIREFERENCE_INCLUDE)
endif
