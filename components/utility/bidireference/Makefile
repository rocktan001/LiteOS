include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/utility/bidireference/bidireference.mk

MODULE_NAME := $(notdir $(CURDIR))

LOCAL_INCLUDE := \
    -I $(LITEOSTOPDIR)/components/utility/bidireference/$(BIDIREFERENCE_VERSION)/include

LOCAL_SRCS = $(wildcard $(BIDIREFERENCE_VERSION)/source/*.c)

LOCAL_EXT_FLAG := -Wno-error -Wno-restrict -Wno-unused-variable \
    -Wno-switch -Wno-unused-but-set-variable -Wno-parentheses \
    -Wno-unused-function -Wno-maybe-uninitialized
LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LOCAL_EXT_FLAG)

include $(MODULE)
