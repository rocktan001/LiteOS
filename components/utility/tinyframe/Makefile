include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/utility/tinyframe/tinyframe.mk

MODULE_NAME := $(notdir $(CURDIR))

LOCAL_DIRS_y += $(TINYFRAME_VERSION)
LOCAL_DIRS_y += $(TINYFRAME_VERSION)/utilities

LOCAL_INCLUDE := \
    -I $(LITEOSTOPDIR)/lib/libc/include \
    -I $(LITEOSTOPDIR)/components/utility/tinyframe/$(TINYFRAME_VERSION) \
    -I $(LITEOSTOPDIR)/components/utility/tinyframe/$(TINYFRAME_VERSION)/demo/simple \
    -I $(LITEOSTOPDIR)/components/utility/tinyframe/$(TINYFRAME_VERSION)/utilities

LOCAL_SRCS += $(foreach dir, $(LOCAL_DIRS_y), $(wildcard $(dir)/*.c))

LOCAL_EXT_FLAG := -Wno-error -fstack-protector-strong
LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LOCAL_EXT_FLAG)
include $(MODULE)
