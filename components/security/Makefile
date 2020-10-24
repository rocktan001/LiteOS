include $(LITEOSTOPDIR)/config.mk

MODULE_NAME     := $(notdir $(CURDIR))
LOCAL_SRCS_y    :=
LOCAL_DIRS_y    :=

# mbedtls_port
LOCAL_DIRS_$(LOSCFG_COMPONENTS_SECURITY_PORT) += mbedtls/mbedtls_port
LOCAL_INCLUDE := \
            -I $(LITEOSTOPDIR)/include \
            -I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls_port

ifeq ($(LOSCFG_COMPONENTS_SECURITY_VERSION_2_6_0), y)
# mbedtls-2.6.0 src
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/library
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs/aes
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs/hash
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs/pkey
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs/random
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs/ssl
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs/test
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs/util
LOCAL_DIRS_y += mbedtls/mbedtls-2.6.0/programs/x509

LOCAL_INCLUDE += \
            -I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls-2.6.0/configs \
			-I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls-2.6.0/include \
            -I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls-2.6.0/doxygen/input \
			-I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls-2.6.0/include/mbedtls \
            -I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls-2.6.0/yotta/data

LOCAL_CFLAGS += -fomit-frame-pointer
endif


LOCAL_SRCS_y += $(foreach dir, $(LOCAL_DIRS_y), $(wildcard $(dir)/*.c))
LOCAL_SRCS    = $(LOCAL_SRCS_y)

LOCAL_FLAGS := $(LOCAL_INCLUDE)

include $(MODULE)
