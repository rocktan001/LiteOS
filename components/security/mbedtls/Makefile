include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := $(notdir $(CURDIR))
LOCAL_SRCS_y :=
LOCAL_DIRS_y :=
LOCAL_CDEFS :=

MBEDTLS_VERSION = mbedtls-2.16.8
ifeq ($(LOSCFG_COMPONENTS_SECURITY_MBEDTLS), y)
LOCAL_DIRS_y += mbedtls_port
LOCAL_DIRS_y += $(MBEDTLS_VERSION)/library

LOCAL_INCLUDE += \
    -I $(LITEOSTOPDIR)/include \
    -I mbedtls_port \
    -I $(MBEDTLS_VERSION)/include \
    -I $(MBEDTLS_VERSION)/include/mbedtls

ifeq ($(LOSCFG_DTLS_PSK_ENCRYPT), y)
LOCAL_CDEFS += -DMBEDTLS_CONFIG_FILE=\"los_mbedtls_config_psk.h\"
else ifeq ($(LOSCFG_DTLS_CRET_ENCRYPT), y)
LOCAL_CDEFS += -DMBEDTLS_CONFIG_FILE=\"los_mbedtls_config_cert.h\"
else
LOCAL_CDEFS += -DMBEDTLS_CONFIG_FILE=\"los_mbedtls_config.h\"
endif

LOCAL_SRCS_y += $(foreach dir, $(LOCAL_DIRS_y), $(wildcard $(dir)/*.c))
LOCAL_SRCS    = $(LOCAL_SRCS_y)
endif

LOCAL_FLAGS := $(LOCAL_CDEFS) $(LOCAL_INCLUDE)

include $(MODULE)