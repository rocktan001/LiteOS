include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/net/librws/librws.mk

MODULE_NAME := $(notdir $(CURDIR))

LOCAL_SRCS := $(wildcard $(LIBRWS_VERSION)/src/*.c)

LOCAL_INCLUDE := -I $(LITEOSTOPDIR)/components/net/librws/$(LIBRWS_VERSION)/src

LOCAL_FLAGS := $(LOCAL_INCLUDE) -Wno-unused-variable

include $(MODULE)
