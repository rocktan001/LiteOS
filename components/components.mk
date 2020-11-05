COMPONENTS_INCLUDE :=

ifeq ($(LOSCFG_COMPONENTS_CONNECTIVITY), y)
include $(LITEOSTOPDIR)/components/connectivity/connectivity.mk
COMPONENTS_INCLUDE += $(COMPONENTS_CONNECTIVITY_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_FS), y)
include $(LITEOSTOPDIR)/components/fs/fs.mk
COMPONENTS_INCLUDE += $(COMPONENTS_FS_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_GUI), y)
include $(LITEOSTOPDIR)/components/gui/gui.mk
COMPONENTS_INCLUDE += $(COMPONENTS_GUI_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_SENSORHUB), y)
include $(LITEOSTOPDIR)/components/sensorhub/sensorhub.mk
COMPONENTS_INCLUDE += $(COMPONENTS_SENSORHUB_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_NETWORK), y)
include $(LITEOSTOPDIR)/components/net/net.mk
COMPONENTS_INCLUDE += $(COMPONENTS_NET_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_SECURITY), y)
include $(LITEOSTOPDIR)/components/security/security.mk
COMPONENTS_INCLUDE += $(COMPONENTS_SECURITY_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_LIB), y)
include $(LITEOSTOPDIR)/components/lib/lib.mk
COMPONENTS_INCLUDE += $(COMPONENTS_LIB_INCLUDE)
endif

ifeq ($(LOSCFG_COMPONENTS_ATINY_LOG), y)
include $(LITEOSTOPDIR)/components/log/atiny_log.mk
COMPONENTS_INCLUDE += $(COMPONENTS_ATINY_LOG_INCLUDE)
endif