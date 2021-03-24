include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/utility/iconv/iconv.mk

MODULE_NAME := $(notdir $(CURDIR))

$(shell sh build.sh $(ICONV_VERSION))

LOCAL_SRCS := $(wildcard $(ICONV_VERSION)/lib/*.c) \
    $(wildcard $(ICONV_VERSION)/libcharset/lib/*.c)

LOCAL_INCLUDE += \
    -I $(LITEOSTOPDIR)/components/utility/iconv \
    -I $(LITEOSTOPDIR)/components/utility/iconv/$(ICONV_VERSION) \
    -I $(LITEOSTOPDIR)/components/utility/iconv/$(ICONV_VERSION)/libcharset/include \
    -I $(LITEOSTOPDIR)/components/utility/iconv/$(ICONV_VERSION)/libcharset/lib \
    -I $(LITEOSTOPDIR)/components/utility/iconv/$(ICONV_VERSION)/lib \
    -I $(LITEOSTOPDIR)/components/utility/iconv/$(ICONV_VERSION)/include \

LOCAL_FLAGS := $(LOCAL_INCLUDE) -DLIBDIR -Wno-unused -Wno-int-conversion -Wno-strict-prototypes

include $(MODULE)