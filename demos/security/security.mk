DEMOS_SECURITY_INCLUDE :=

ifeq ($(LOSCFG_DEMOS_OPENSSL), y)
include $(LITEOSTOPDIR)/demos/security/openssl/openssl.mk
DEMOS_SECURITY_INCLUDE += $(DEMOS_OPENSSL_INCLUDE)
endif
