include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := $(notdir $(shell pwd))

LOCAL_SRCS :=  $(wildcard *.c)

LOCAL_INCLUDE := \
	-I $(LITEOSTOPDIR)/kernel/base/include \
	-I $(LITEOSTOPDIR)/compat/cmsis

LOCAL_FLAGS := $(LOCAL_INCLUDE)

include $(MODULE)
