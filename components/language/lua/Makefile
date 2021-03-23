include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/language/lua/lua.mk

MODULE_NAME := $(notdir $(CURDIR))

LOCAL_INCLUDE := -I $(LITEOSTOPDIR)/components/language/lua/$(LUA_VERSION)

LOCAL_SRCS := \
    $(wildcard $(LUA_VERSION)/onelua.c)

LOCAL_FLAGS := $(LOCAL_INCLUDE) -DEXIT_FAILURE=1 -DEXIT_SUCCESS=0 -Wno-unused

include $(MODULE)
