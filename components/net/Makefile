include $(LITEOSTOPDIR)/config.mk

MODULE_NAME     := lwip

LWIP_DIR = $(LITEOSTOPDIR)/components/net/lwip
LWIP_INC_DIR = $(LITEOSTOPDIR)/components/net
LWIP_SRC_DIR = $(LWIP_DIR)/lwip-2.0.3/src

LWIP_SRCS = \
    $(wildcard $(LWIP_DIR)/ppp_port/ppppos/*.c) \
    $(wildcard $(LWIP_DIR)/ppp_port/ppppos/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/api/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/fs/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/makefsdata/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/lwiperf/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/mdns/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/mqtt/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/netbiosns/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/snmp/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/sntp/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/apps/tftp/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/core/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/core/ipv4/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/core/ipv6/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/netif/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/netif/ppp/*.c) \
    $(wildcard $(LWIP_DIR)/lwip-2.0.3/src/netif/ppp/polarssl/*.c) \
    $(wildcard $(LWIP_INC_DIR)/at_device/wifi_esp8266/*.c)

LWIP_INC := \
    -I $(LWIP_DIR)/lwip-2.0.3/src/include/ \
    -I $(LWIP_DIR)/lwip_port/ \
    -I $(LWIP_DIR)/lwip-2.0.3/test/fuzz/ \
    -I $(LWIP_DIR)/ppp_port/osport/ \
    -I $(LWIP_INC_DIR)/at_device/wifi_esp8266/ \
    -I $(LITEOSTOPDIR)/include/

LOCAL_SRCS := $(subst $(CURDIR)/,, $(LWIP_SRCS))

LOCAL_INCLUDE := $(LWIP_INC) $(LWIP_INC_DIR) $(LWIP_SRC_DIR)

LOCAL_FLAGS :=  $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)


include $(MODULE)
