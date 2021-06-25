include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/components/security/openssl/openssl.mk

MODULE_NAME := openssl

LOCAL_INCLUDE := \
    -I $(OPENSSL_VERSION) \
    -I $(OPENSSL_VERSION)/include \
    -I $(OPENSSL_VERSION)/crypto/include \
    -I $(OPENSSL_VERSION)/crypto/modes

LOCAL_DIRS_y := \
    aes asn1 async bf bio blake2 bn buffer camellia cast chacha cmac \
    cms comp ct conf des dh dsa dso ec engine err evp hmac idea \
    kdf lhash md4 md5 mdc2 modes objects ocsp pem \
    pkcs12 rand rc2 rc4  ripemd rsa ecdsa  ecdh krb5 pqueue \
    seed sha srp stack ts txt_db ui whrlpool x509 x509v3 poly1305

SSL_SRCS := \
    $(wildcard $(OPENSSL_VERSION)/ssl/*.c) \
    $(wildcard $(OPENSSL_VERSION)/ssl/statem/*.c) \
    $(wildcard $(OPENSSL_VERSION)/ssl/record/*.c)

CRYPTO_SRCS := \
    $(wildcard $(OPENSSL_VERSION)/crypto/*.c) \
    $(foreach dir,$(LOCAL_DIRS_y), $(wildcard $(OPENSSL_VERSION)/crypto/$(dir)/*.c))

LOCAL_SRCS := $(SSL_SRCS)
LOCAL_SRCS += $(CRYPTO_SRCS)

DEFS := -DOPENSSLDIR="\"$(OPENSSLDIR)\"" -DENGINESDIR="\"$(ENGINESDIR)\""

LOCAL_EXT_FLAG := \
    -Wno-error -Wno-implicit-int -Wno-strict-prototypes -Wno-format-nonliteral \
    -Wno-unused-but-set-variable -Wno-unused-variable -Wno-float-equal

LOCAL_FLAGS := $(DEFS) $(LOCAL_EXT_FLAG) $(LOCAL_INCLUDE)

include $(MODULE)
