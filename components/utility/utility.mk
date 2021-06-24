COMPONENTS_UTILITY_INCLUDE :=

ifeq ($(LOSCFG_COMPONENTS_ICONV), y)
include $(LITEOSTOPDIR)/components/utility/iconv/iconv.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_ICONV_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_INIPARSER), y)
include $(LITEOSTOPDIR)/components/utility/iniparser/iniparser.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_INIPARSER_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_JSON_C), y)
include $(LITEOSTOPDIR)/components/utility/json-c/json-c.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_JSON_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_BIDIREFERENCE), y)
include $(LITEOSTOPDIR)/components/utility/bidireference/bidireference.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_BIDIREFERENCE_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_FREETYPE), y)
include $(LITEOSTOPDIR)/components/utility/freetype/freetype.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_FREETYPE_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_LIBXML2), y)
include $(LITEOSTOPDIR)/components/utility/libxml2/libxml2.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_LIBXML2_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_SQLITE), y)
include $(LITEOSTOPDIR)/components/utility/sqlite/sqlite.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_SQLITE_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_JSONCPP), y)
include $(LITEOSTOPDIR)/components/utility/jsoncpp/jsoncpp.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_JSONCPP_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_FASTLZ), y)
include $(LITEOSTOPDIR)/components/utility/fastlz/fastlz.mk
COMPONENTS_UTILITY_INCLUDE += $(COMPONENTS_FASTLZ_INCLUDE)
endif
