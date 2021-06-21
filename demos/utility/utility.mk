DEMOS_UTILITY_INCLUDE :=

ifeq ($(LOSCFG_DEMOS_ICONV), y)
include $(LITEOSTOPDIR)/demos/utility/iconv/iconv.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_ICONV_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_INIPARSER), y)
include $(LITEOSTOPDIR)/demos/utility/iniparser/iniparser.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_INIPARSER_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_JSON_C), y)
include $(LITEOSTOPDIR)/demos/utility/json-c/json-c.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_JSON_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_BIDIREFERENCE), y)
include $(LITEOSTOPDIR)/demos/utility/bidireference/bidireference.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_BIDIREFERENCE_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_FREETYPE), y)
include $(LITEOSTOPDIR)/demos/utility/freetype/freetype.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_FREETYPE_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_LIBXML2), y)
include $(LITEOSTOPDIR)/demos/utility/libxml2/libxml2.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_LIBXML2_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_SQLITE), y)
include $(LITEOSTOPDIR)/demos/utility/sqlite/sqlite.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_SQLITE_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_JSONCPP), y)
include $(LITEOSTOPDIR)/demos/utility/jsoncpp/jsoncpp.mk
DEMOS_UTILITY_INCLUDE += $(DEMOS_JSONCPP_INCLUDE)
endif
