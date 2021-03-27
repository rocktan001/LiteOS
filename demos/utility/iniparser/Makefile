include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/utility/iniparser/iniparser.mk

MODULE_NAME := iniparser_demo

LOCAL_SRCS_y := $(wildcard *.c)

LOCAL_INCLUDE += \
    -I $(LITEOSTOPDIR)/include \
    -I $(LITEOSTOPDIR)/lib/libc/include \
    -I $(LITEOSTOPDIR)/lib/libsec/include \
    -I $(LITEOSTOPDIR)/demos/iniparser

LOCAL_INCLUDE += $(COMPONENTS_INIPARSER_INCLUDE)
LOCAL_SRCS := $(LOCAL_SRCS_y)
LOCAL_FLAGS := $(LOCAL_INCLUDE)

include $(MODULE)
