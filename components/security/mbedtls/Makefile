include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls.mk
include $(LITEOSTOPDIR)/components/net/net.mk

MODULE_NAME := mbedtls
LOCAL_DIRS_y :=
LOCAL_CDEFS :=

LOCAL_DIRS_y += mbedtls_port
LOCAL_DIRS_y += $(MBEDTLS_VERSION)/library

LOCAL_INCLUDE += \
    -I $(LITEOSTOPDIR)/include \
    -I mbedtls_port \
    -I $(MBEDTLS_VERSION)/include \
    -I $(MBEDTLS_VERSION)/include/mbedtls

LOCAL_INCLUDE += $(COMPONENTS_NET_INCLUDE)

ifeq ($(LOSCFG_DTLS_PSK_ENCRYPT), y)
LOCAL_CDEFS += -DMBEDTLS_CONFIG_FILE=\"los_mbedtls_config_psk.h\"
else ifeq ($(LOSCFG_DTLS_CERT_ENCRYPT), y)
LOCAL_CDEFS += -DMBEDTLS_CONFIG_FILE=\"los_mbedtls_config_cert.h\"
else
LOCAL_CDEFS += -DMBEDTLS_CONFIG_FILE=\"los_mbedtls_config.h\"
endif

LOCAL_SRCS += $(foreach dir, $(LOCAL_DIRS_y), $(wildcard $(dir)/*.c))

LOCAL_FLAGS := $(LOCAL_CDEFS) $(LOCAL_INCLUDE)

include $(MODULE)