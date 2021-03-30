include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/utility/json-c/json-c.mk

MODULE_NAME := json-c

$(shell sh build.sh $(JSON_VERSION))

LOCAL_INCLUDE := \
    -I $(LITEOSTOPDIR)/components/utility/json-c/$(JSON_VERSION) \
    -I $(LITEOSTOPDIR)/lib/libc/include \
    -I $(LITEOSTOPDIR)/include \
    -I $(LITEOSTOPDIR)/include/fs

LOCAL_SRCS = $(wildcard $(JSON_VERSION)/*.c)

LOCAL_EXT_FLAG := -Wno-error -DSQLITE_DEBUG=1 \
    -Wno-strict-prototypes -Wno-unused-variable

LOCAL_FLAGS := $(LOCAL_EXT_FLAG) $(LOCAL_INCLUDE)

include $(MODULE)
