include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/media/openexif/openexif.mk

MODULE_NAME := openexif_demo

LOCAL_SRCS := $(wildcard *.cpp)

LOCAL_INCLUDE := \
    -I $(LITEOSTOPDIR)/include \
    $(COMPONENTS_INCLUDE)

LOCAL_CPPFLAGS := $(LOCAL_INCLUDE) -Wno-error -w

include $(MODULE)
