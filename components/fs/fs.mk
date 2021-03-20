LITTLEFD_VERSION = littlefs-2.3.0

ifeq ($(LOSCFG_COMPONENTS_FS_FATFS), y)
COMPONENTS_FS_INCLUDE := \
    -I $(LITEOSTOPDIR)/components/fs/fatfs/ff13b/source \
    -I $(LITEOSTOPDIR)/components/fs/fatfs/ff13b/source/default
endif

ifeq ($(LOSCFG_COMPONENTS_FS_SPIFFS), y)
COMPONENTS_FS_INCLUDE += \
    -I $(LITEOSTOPDIR)/components/fs/spiffs/spiffs_git/src \
    -I $(LITEOSTOPDIR)/components/fs/spiffs/spiffs_git/src/default
endif

ifeq ($(LOSCFG_COMPONENTS_FS_LITTLEFS), y)
COMPONENTS_FS_INCLUDE += \
    -I $(LITEOSTOPDIR)/components/fs/littlefs/$(LITTLEFD_VERSION)
endif
