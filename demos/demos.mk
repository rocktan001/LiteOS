DEMOS_INCLUDE :=

ifeq ($(LOSCFG_DEMOS_FS), y)
include $(LITEOSTOPDIR)/demos/fs/fs.mk
DEMOS_INCLUDE += $(DEMOS_FS_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_GUI), y)
include $(LITEOSTOPDIR)/demos/gui/gui.mk
DEMOS_INCLUDE += $(DEMOS_GUI_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_SENSORHUB), y)
include $(LITEOSTOPDIR)/demos/sensorhub/sensorhub.mk
DEMOS_INCLUDE += $(DEMOS_SENSORHUB_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_KERNEL), y)
include $(LITEOSTOPDIR)/demos/kernel/kernel.mk
DEMOS_INCLUDE += $(DEMOS_KERNEL_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_AGENT_TINY_MQTT), y)
include $(LITEOSTOPDIR)/demos/agenttiny_mqtt/agenttiny_mqtt.mk
DEMOS_INCLUDE += $(DEMOS_AGENTTINY_MQTT_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_AGENT_TINY_LWM2M), y)
include $(LITEOSTOPDIR)/demos/agenttiny_lwm2m/agenttiny_lwm2m.mk
DEMOS_INCLUDE += $(DEMOS_AGENTTINY_LWM2M_INCLUDE)
endif

ifeq ($(LOSCFG_DEMOS_DTLS_SERVER), y)
include $(LITEOSTOPDIR)/demos/dtls_server/dtls_server.mk
DEMOS_INCLUDE += $(DEMOS_DTLS_SERVER_INCLUDE)
endif

