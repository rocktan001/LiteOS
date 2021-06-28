include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/utility/tinyxml2/tinyxml2.mk

MODULE_NAME := tinyxml2_demo

LOCAL_SRCS := $(wildcard *.cpp)

LOCAL_INCLUDE := \
    -I $(LITEOSTOPDIR)/lib/libc/include \
    -I $(LITEOSTOPDIR)/include

LOCAL_INCLUDE += $(COMPONENTS_TINYXML2_INCLUDE)

LOCAL_CPPFLAGS :=  $(LOCAL_INCLUDE) -w -std=c++11 -D_GLIBCXX_HAS_GTHREADS

include $(MODULE)

