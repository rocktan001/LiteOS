include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/media/libpng/libpng.mk

MODULE_NAME := png_demo

PNG_DEMO_INCLUDE := $(COMPONENTS_LIBPNG_INCLUDE)

LOCAL_SRCS := $(wildcard *.c)

LOCAL_INCLUDE := $(PNG_DEMO_INCLUDE)

LOCAL_FLAGS :=  $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS) -Wno-implicit-function-declaration

include $(MODULE)
