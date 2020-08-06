# C sources
HAL_DRIVER_SRC =  \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_iwdg.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.c
        C_SOURCES += $(HAL_DRIVER_SRC)

HARDWARE_SRC =  \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/Src/*.c} \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/LCD/*.c}
        C_SOURCES += $(HARDWARE_SRC)

HAL_DRIVER_SRC_NO_BOOTLOADER =  \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng.c
        C_SOURCES += $(HAL_DRIVER_SRC_NO_BOOTLOADER)

BSP_HWI_SRC = \
        ${wildcard  $(LITEOSTOPDIR)/targets/bsp/common/hwi/*.c}
        C_SOURCES += $(BSP_HWI_SRC)

BSP_SRC = \
        ${wildcard $(LITEOSTOPDIR)/targets/bsp/common/*.c}
BSP_SRC_EXCLUDE = \
        $(LITEOSTOPDIR)/targets/bsp/common/console.c \
        $(LITEOSTOPDIR)/targets/bsp/common/virtual_serial.c
BSP_SRC := $(filter-out $(BSP_SRC_EXCLUDE), $(BSP_SRC))
        C_SOURCES += $(BSP_SRC)


#just a stub interface
BSP_TIMER_SRC = \
        ${wildcard  $(LITEOSTOPDIR)/targets/bsp/hw/arm/timer/arm_private/*.c}
        C_SOURCES += $(BSP_TIMER_SRC)

OS_DEPENDS_SRC = \
        ${wildcard $(LITEOSTOPDIR)/osdepends/liteos/*.c}
        C_SOURCES += $(OS_DEPENDS_SRC)

USER_SRC =  \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/os_adapt/os_adapt.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/dwt.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/gpio.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/Huawei_IoT_QR_Code.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/i2c.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/loader_main.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/main.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/spi.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/stm32l4xx_it.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/sys_init.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/system_stm32l4xx.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/usart.c \
        $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/uart_debug.c
        C_SOURCES += $(USER_SRC)

ifeq ($(WITH_LWIP), yes)
LWIP_SRC =  \
        ${wildcard $(LITEOSTOPDIR)/components/net/lwip/lwip-2.0.3/src/api/*.c} \
        ${wildcard $(LITEOSTOPDIR)/components/net/lwip/lwip-2.0.3/src/core/ipv4/*.c} \
        ${wildcard $(LITEOSTOPDIR)/components/net/lwip/lwip-2.0.3/src/core/ipv6/*.c} \
        ${wildcard $(LITEOSTOPDIR)/components/net/lwip/lwip-2.0.3/src/core/*.c} \
        ${wildcard $(LITEOSTOPDIR)/components/net/lwip/lwip-2.0.3/src/netif/ethernet.c}
        C_SOURCES += $(LWIP_SRC)

LWIP_PORT_SRC = \
        ${wildcard $(LITEOSTOPDIR)/components/net/lwip/lwip_port/OS/*.c}
        C_SOURCES += $(LWIP_PORT_SRC)
endif


ifeq ($(WITH_LWM2M), yes)
ER_COAP_SRC = \
        ${wildcard $(LITEOSTOPDIR)/components/connectivity/lwm2m/core/er-coap-13/er-coap-13.c}
        C_SOURCES += $(ER_COAP_SRC)

LWM2M_SRC = \
        ${wildcard $(LITEOSTOPDIR)/components/connectivity/lwm2m/core/*.c} \
        ${wildcard $(LITEOSTOPDIR)/components/connectivity/lwm2m/examples/shared/*.c}
        C_SOURCES += $(LWM2M_SRC)

ATINY_TINY_SRC = \
        ${wildcard $(LITEOSTOPDIR)/components/connectivity/agent_tiny/atiny_lwm2m/*.c}

AGENT_DEMO_SRC = \
        ${wildcard $(LITEOSTOPDIR)/demos/agenttiny_lwm2m/*.c}
        C_SOURCES += $(AGENT_DEMO_SRC)
endif

SOCKET_ADAPTER_SRC = \
        ${wildcard $(LITEOSTOPDIR)/components/net/sal/*.c}
        C_SOURCES += $(SOCKET_ADAPTER_SRC)

ATINY_LOG = \
        ${wildcard $(LITEOSTOPDIR)/components/log/*.c}
        C_SOURCES += $(ATINY_LOG)


ifeq ($(WITH_MQTT), yes)
MQTT_SRC = \
        ${wildcard $(LITEOSTOPDIR)/components/connectivity/mqtt/MQTTPacket/src/*.c} \
        $(LITEOSTOPDIR)/components/connectivity/mqtt/MQTTClient-C/src/MQTTClient.c \
        $(LITEOSTOPDIR)/components/connectivity/mqtt/MQTTClient-C/src/liteOS/MQTTliteos.c
        C_SOURCES += $(MQTT_SRC)
ATINY_TINY_MQTT_SRC = \
        ${wildcard $(LITEOSTOPDIR)/components/connectivity/agent_tiny/atiny_mqtt/*.c}
        C_SOURCES += $(ATINY_TINY_MQTT_SRC)
AGENT_DEMO_MQTT_SRC = \
        ${wildcard $(LITEOSTOPDIR)/demos/agenttiny_mqtt/*.c}
        C_SOURCES += $(AGENT_DEMO_MQTT_SRC)
CJSON_SRC = \
        ${wildcard $(LITEOSTOPDIR)/components/lib/cJSON/cJSON.c}
        C_SOURCES += $(CJSON_SRC)
        C_SOURCES += $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Src/flash_adaptor.c
endif

ifeq ($(WITH_FILESYSTEM), yes)
        FS_SRC = \
                ${wildcard $(LITEOSTOPDIR)/components/fs/vfs/*.c}
                C_SOURCES += $(FS_SRC)

        FS_DEMO_COMMON_SRC = \
                ${wildcard $(LITEOSTOPDIR)/demos/fs/fs_common.c}
                C_SOURCES += $(FS_DEMO_COMMON_SRC)

        FS_SPIFFS_SRC = \
                ${wildcard $(LITEOSTOPDIR)/components/fs/spiffs/*.c} \
                ${wildcard $(LITEOSTOPDIR)/components/fs/spiffs/spiffs_git/src/*.c}

        FS_FATFS_SRC = \
                ${wildcard $(LITEOSTOPDIR)/components/fs/fatfs/*.c} \
                ${wildcard $(LITEOSTOPDIR)/components/fs/fatfs/ff13b/source/*.c}

        ifeq ($(IS_COMPILE_ALLFS), ALL)
                C_SOURCES += $(FS_SPIFFS_SRC)
                C_SOURCES += $(FS_FATFS_SRC)
                        C_SOURCES += $(LITEOSTOPDIR)/demos/fs/fatfs_demo.c
                        C_SOURCES += $(LITEOSTOPDIR)/demos/fs/spiffs_demo.c
        else ifeq ($(FILESYSTEM_TYPE), SPIFFS)
                C_SOURCES += $(FS_SPIFFS_SRC)
                        C_SOURCES += $(LITEOSTOPDIR)/demos/fs/spiffs_demo.c
        else ifeq ($(FILESYSTEM_TYPE), FATFS)
                C_SOURCES += $(FS_FATFS_SRC)
                        C_SOURCES += $(LITEOSTOPDIR)/demos/fs/fatfs_demo.c
        endif
endif

# C includes
HAL_DRIVER_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Inc \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy
        BOARD_INCLUDES += $(HAL_DRIVER_INC)

HARDWARE_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/Inc} \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/LCD} \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Inc
        BOARD_INCLUDES += $(HARDWARE_INC)

INCLUDE_INC = \
        -I $(LITEOSTOPDIR)/include
        BOARD_INCLUDES += $(INCLUDE_INC)

BSP_INC = \
        -I $(LITEOSTOPDIR)/targets/bsp/common \
        -I $(LITEOSTOPDIR)/targets/bsp/include \
        -I $(LITEOSTOPDIR)/targets/bsp/hw/include \
        -I $(LITEOSTOPDIR)/compat/posix/src \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/include \
        -I $(LITEOSTOPDIR)/kernel/extended/include
        BOARD_INCLUDES += $(BSP_INC)
BSP_HWI_INC = \
        -I $(LITEOSTOPDIR)/targets/bsp/common/hwi
        BOARD_INCLUDES += $(BSP_HWI_INC)

HARDWARE_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/Inc
        BOARD_INCLUDES += $(HARDWARE_INC)

USER_INC = \
        -I $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Inc
        BOARD_INCLUDES += $(USER_INC)

LWM2M_ATINY_INC = \
        -I $(LITEOSTOPDIR)/components/connectivity/agent_tiny/atiny_lwm2m
        BOARD_INCLUDES += $(LWM2M_ATINY_INC)

ifneq ($(USE_OTA)_$(USE_BOOTLOADER), no_no)
OTA_INC = \
        -I $(LITEOSTOPDIR)/components/ota/flag_operate \
        -I $(LITEOSTOPDIR)/components/ota/utility \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Inc
        BOARD_INCLUDES += $(OTA_INC)
endif

CMSIS_INC = \
        -I $(LITEOSTOPDIR)/arch/arm/common/cmsis
        BOARD_INCLUDES += $(CMSIS_INC)

LITEOS_CMSIS_INC = \
        -I $(LITEOSTOPDIR)/osdepends/liteos/cmsis
        BOARD_INCLUDES += $(LITEOS_CMSIS_INC)


ifeq ($(WITH_LWIP), yes)
LWIP_INC = \
        -I $(LITEOSTOPDIR)/components/net/lwip/lwip-2.0.3/src/include
        BOARD_INCLUDES += $(LWIP_INC)

LWIP_PORT_INC = \
        -I $(LITEOSTOPDIR)/components/net/lwip/lwip_port \
        -I $(LITEOSTOPDIR)/components/net/lwip/lwip_port/OS
        BOARD_INCLUDES += $(LWIP_PORT_INC)
endif

ifneq ($(OTA_IS_NEED_DTLS)_$(WITH_DTLS), no_no)
MBEDTLS_INC = \
        -I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls-2.6.0/include
        BOARD_INCLUDES += $(MBEDTLS_INC)

MBEDTLS_PORT_INC = \
        -I $(LITEOSTOPDIR)/components/security/mbedtls/mbedtls_port
        BOARD_INCLUDES += $(MBEDTLS_PORT_INC)
endif

ifeq ($(WITH_LWM2M), yes)
ER_COAP_INC = \
        -I $(LITEOSTOPDIR)/components/connectivity/lwm2m/core/er-coap-13
        BOARD_INCLUDES += $(ER_COAP_INC)
LWM2M_INC = \
        -I $(LITEOSTOPDIR)/components/connectivity/lwm2m/core \
        -I $(LITEOSTOPDIR)/components/connectivity/lwm2m/examples/shared
        BOARD_INCLUDES += $(LWM2M_INC)
endif

ifeq ($(WITH_MQTT), yes)
MQTT_INC = \
        -I $(LITEOSTOPDIR)/components/connectivity/mqtt/MQTTClient-C/src \
        -I $(LITEOSTOPDIR)/components/connectivity/mqtt/MQTTClient-C/src/liteOS \
        -I $(LITEOSTOPDIR)/components/connectivity/mqtt/MQTTPacket/src \
        -I $(LITEOSTOPDIR)/components/lib/cJSON
        BOARD_INCLUDES += $(MQTT_INC)
endif

ifeq ($(WITH_FILESYSTEM), yes)
FS_SPIFFS_INC = \
        -I $(LITEOSTOPDIR)/components/fs/spiffs/spiffs_git/src \
        -I $(LITEOSTOPDIR)/components/fs/spiffs/spiffs_git/src/default

FS_FATFS_INC = \
        -I $(LITEOSTOPDIR)/components/fs/fatfs/ff13b/source \
        -I $(LITEOSTOPDIR)/components/fs/fatfs/ff13b/source/default

ifeq ($(IS_COMPILE_ALLFS), ALL)
        BOARD_INCLUDES += $(FS_SPIFFS_INC)
        BOARD_INCLUDES += $(FS_FATFS_INC)
else ifeq ($(FILESYSTEM_TYPE), SPIFFS)
        BOARD_INCLUDES += $(FS_SPIFFS_INC)
else ifeq ($(FILESYSTEM_TYPE), FATFS)
        BOARD_INCLUDES += $(FS_FATFS_INC)
endif
endif

USER_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Inc \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/include \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/Inc \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/LCD
        BOARD_INCLUDES += $(USER_INC)

# C defines
C_DEFS =  \
     -D USE_HAL_DRIVER \
     -D STM32L431xx \
     -D NDEBUG \
     -D __LITEOS__ \
     -D _ALL_SOURCE


ifeq ($(WITH_LWM2M), yes)
        C_DEFS += \
            -D LWM2M_LITTLE_ENDIAN \
            -D LWM2M_CLIENT_MODE
endif
ifneq ($(OTA_IS_NEED_DTLS)_$(WITH_DTLS), no_no)
        ifeq ($(WITH_MQTT), yes)
            C_DEFS += -D MBEDTLS_CONFIG_FILE=\"los_mbedtls_config_cert.h\"
        else
            C_DEFS += -D MBEDTLS_CONFIG_FILE=\"los_mbedtls_config.h\"
        endif

        ifeq ($(USE_MBEDTLS_DEBUG_C), yes)
            C_DEFS += -DMBEDTLS_DEBUG_C
        endif

        ifeq ($(USE_MBEDTLS_AES_ROM_TABLES), yes)
            C_DEFS += -DMBEDTLS_AES_ROM_TABLES
        endif
endif

ifeq ($(WITH_DTLS), yes)
        C_DEFS += -DWITH_DTLS
endif

ifeq ($(WITH_LWIP), yes)
        C_DEFS += \
            -DWITH_LWIP \
            -D LWIP_TIMEVAL_PRIVATE=0

        ifeq ($(USE_LWIP_TCP), yes)
            C_DEFS += -DLWIP_TCP=1
        else
            C_DEFS += -DLWIP_TCP=0
        endif
endif

ifeq ($(WITH_AT_FRAMEWORK), yes)
        C_DEFS += -DWITH_AT_FRAMEWORK
        C_DEFS += -DUSE_$(NETWORK_TYPE)
endif


ifeq ($(OTA_PACK_CHECKSUM), NO_CHECKSUM)
        C_DEFS += -DPACK_CHECKSUM=2
else ifeq ($(OTA_PACK_CHECKSUM), SHA256)
        C_DEFS += -DPACK_CHECKSUM=1
else ifeq ($(OTA_PACK_CHECKSUM), SHA256_RSA2048)
        C_DEFS += -DPACK_CHECKSUM=0
else
endif

ifeq ($(USE_FOTA), yes)
        C_DEFS += -DCONFIG_FEATURE_FOTA
endif

ifeq ($(USE_SOTA), yes)
        C_DEFS += -DWITH_SOTA
endif

ifeq ($(LWM2M_BOOTSTRAP), yes)
        C_DEFS += -DLWM2M_BOOTSTRAP
endif

ifeq ($(SUPPORT_DTLS_SRV), yes)
        C_DEFS += -DSUPPORT_DTLS_SRV
endif

ifeq ($(LWM2M_WITH_LOGS), yes)
        C_DEFS += -DLWM2M_WITH_LOGS
endif

ifeq ($(ATINY_DEBUG), yes)
        C_DEFS += -DATINY_DEBUG
endif

ifeq ($(WITH_FILESYSTEM), yes)
        C_DEFS += -DFS_$(FILESYSTEM_TYPE)
endif

ifeq ($(WITH_MQTT), yes)
        C_DEFS += -DWITH_MQTT
endif

ifeq ($(WITH_IPV4), no)
        C_DEFS += -DLWIP_IPV4=0
else
        C_DEFS += -DLWIP_IPV4=1
endif

ifeq ($(WITH_IPV6), yes)
        C_DEFS += -DLWIP_IPV6=1
else
        C_DEFS += -DLWIP_IPV6=0
endif

ifeq ($(WITH_SENSORHUB), yes)
        C_DEFS += -DWITH_SENSORHUB
endif

ifeq ($(WITH_LITEOS_TEST), yes)
        include test_liteos.mk
else
        C_DEFS += \
            -DLOSCFG_PLATFORM_OSAPPINIT
endif

ASM_SOURCES =  \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32L431_BearPi/los_startup_gcc.S}

LOCAL_SRCS += $(ASM_SOURCES)
LOCAL_SRCS         += $(C_SOURCES)
LITEOS_CMACRO_TEST += $(C_DEFS)
PLATFORM_INCLUDE   += $(BOARD_INCLUDES)
