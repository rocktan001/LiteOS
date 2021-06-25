include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/utility/harfbuzz/harfbuzz.mk

MODULE_NAME := harfbuzz_demo

HARFBUZZ_INC += $(COMPONENTS_HARFBUZZ_INCLUDE)

LOCAL_INCLUDE := $(HARFBUZZ_INC)

LOCAL_SRCS := $(wildcard *.cpp)

LOCAL_FLAGS := $(LOCAL_INCLUDE) -DHB_NO_MT -std=c++11 -D_GLIBCXX_HAS_GTHREADS \
    -Wno-error -Wno-deprecated-declarations

include $(MODULE)
