include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/net/lwip/lwip.mk

MODULE_NAME := httpc_demo

LOCAL_SRCS := $(wildcard *.c)

LOCAL_INCLUDE := $(COMPONENTS_HTTP_CLIENT_INCLUDE) $(LWIP_INCLUDE)

LOCAL_EXT_FLAG := -fstack-protector-strong

LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LOCAL_EXT_FLAG)

include $(MODULE)
