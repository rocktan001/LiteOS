include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/utility/jsoncpp/jsoncpp.mk

MODULE_NAME := $(notdir $(CURDIR))

LOCAL_SRCS := $(wildcard $(JSONCPP_VERSION)/src/lib_json/*.cpp)

LOCAL_INCLUDE := $(COMPONENTS_JSONCPP_INCLUDE) \
    -I $(LITEOSTOPDIR)/components/utility/jsoncpp/$(JSONCPP_VERSION)/src/lib_json

LOCAL_CPPFLAGS := $(LOCAL_INCLUDE) -w

include $(MODULE)
