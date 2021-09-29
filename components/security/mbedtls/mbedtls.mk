COMPONENTS_MBEDTLS_INCLUDE :=

MBEDTLS_VERSION = mbedtls-2.16.8

COMPONENTS_MBEDTLS_INCLUDE += \
    -I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls_port \
    -I $(LITEOSTOPDIR)/components/security/mbedtls/$(MBEDTLS_VERSION)/include
