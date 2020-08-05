##########################################################################################################################
# STM32L431_BearPI GCC compiler Makefile
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
# ------------------------------------------------
include config.mk
######################################
# target
######################################
TARGET = Huawei_LiteOS
######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -O0 -g

#######################################
# binaries
#######################################
PREFIX    = arm-none-eabi-
CC        = $(PREFIX)gcc
AS        = $(PREFIX)gcc -x assembler-with-cpp
OBJCOPY   = $(PREFIX)objcopy
OBJDUMP   = $(PREFIX)objdump
AR        = $(PREFIX)ar
SZ        = $(PREFIX)size
LD        = $(PREFIX)ld
HEX       = $(OBJCOPY) -O ihex
BIN       = $(OBJCOPY) -O binary -S

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

GCC_DIR = $(CURDIR)
override GCC_DIR := $(abspath $(GCC_DIR))
GCC_DIR = $(abspath $(CURDIR))
TOP_DIR = $(GCC_DIR)/../../..


ARCH_DIR = $(TOP_DIR)/arch
COMPONENTS_DIR = $(TOP_DIR)/components
DEMOS_DIR = $(TOP_DIR)/demos
KERNEL_DIR = $(TOP_DIR)/kernel
OSDEPENDS_DIR = $(TOP_DIR)/osdepends
LIB_DIR = $(TOP_DIR)/lib
COMPAT_DIR = $(TOP_DIR)/compat
TARGETS_DIR = $(TOP_DIR)/targets
TEST_DIR = $(TOP_DIR)/test
TESTS_DIR = $(TOP_DIR)/tests
TARGET_DIR = $(TARGETS_DIR)/STM32L431_BearPi
SRC_DIR = $(TARGET_DIR)/Src

######################################
# source
######################################
# ASM sources
ASM_SOURCES_GCC= \
        $(GCC_DIR)/los_startup_gcc.S

ASM_SOURCES_ARCH =  \
         ${wildcard $(ARCH_DIR)/arm/cortex-m/cortex-m4/gcc/*.S}

# C sources
LIBSEC_SRC = \
        ${wildcard $(LIB_DIR)/libsec/src/*.c}
        C_SOURCES += $(LIBSEC_SRC)

KERNEL_SRC =  \
        ${wildcard $(KERNEL_DIR)/*.c} \
        ${wildcard $(KERNEL_DIR)/base/core/*.c} \
        ${wildcard $(KERNEL_DIR)/base/ipc/*.c} \
        ${wildcard $(KERNEL_DIR)/base/mem/bestfit_little/*.c} \
        ${wildcard $(KERNEL_DIR)/base/mem/membox/*.c} \
        ${wildcard $(KERNEL_DIR)/base/mem/common/*.c} \
        ${wildcard $(KERNEL_DIR)/base/misc/*.c} \
        ${wildcard $(KERNEL_DIR)/base/mp/*.c} \
        ${wildcard $(KERNEL_DIR)/base/om/*.c} \
        ${wildcard $(KERNEL_DIR)/base/sched/sched_sq/*.c} \
        ${wildcard $(KERNEL_DIR)/extended/tickless/*.c}
        C_SOURCES += $(KERNEL_SRC)

POSIX_SRC = \
        ${wildcard $(COMPAT_DIR)/posix/src/*.c}
        C_SOURCES += $(POSIX_SRC)

ZLIB_SRC = \
        ${wildcard $(LIB_DIR)/zlib/src/*.c}
        C_SOURCES += $(ZLIB_SRC)

LIBC_SRCS = \
        ${wildcard $(LIB_DIR)/hw/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/errno/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/stdio/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/string/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/stdlib/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/prng/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/multibyte/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/internal/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/env/*.c)} \
        ${wildcard $(LIB_DIR)/libc/src/locale/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/ctype/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/temp/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/linux/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/fcntl/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/process/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/legacy/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/thread/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/signal/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/network/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/unistd/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/termios/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/time/*.c} \
        ${wildcard $(LIB_DIR)/libc/src/misc/*.c)}
        C_SOURCES += $(LIBC_SRCS)

#    ${wildcard $(LIB_DIR)/libc/src/exit/*.c} \

HAL_DRIVER_SRC =  \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_iwdg.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.c
        C_SOURCES += $(HAL_DRIVER_SRC)

HARDWARE_SRC =  \
        ${wildcard $(TARGET_DIR)/Hardware/Src/*.c} \
        ${wildcard $(TARGET_DIR)/Hardware/LCD/*.c}
        C_SOURCES += $(HARDWARE_SRC)

HAL_DRIVER_SRC_NO_BOOTLOADER =  \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c \
        $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng.c
        C_SOURCES += $(HAL_DRIVER_SRC_NO_BOOTLOADER)

CMSIS_SRC =  \
        ${wildcard $(OSDEPENDS_DIR)/liteos/cmsis/*.c}
        C_SOURCES += $(CMSIS_SRC)

OS_DEPENDS_SRC = \
        ${wildcard $(OSDEPENDS_DIR)/liteos/*.c}
        C_SOURCES += $(OS_DEPENDS_SRC)

BSP_SRC = \
        ${wildcard $(TARGETS_DIR)/bsp/common/*.c}
BSP_SRC_EXCLUDE = \
        $(TARGETS_DIR)/bsp/common/console.c \
        $(TARGETS_DIR)/bsp/common/virtual_serial.c
BSP_SRC := $(filter-out $(BSP_SRC_EXCLUDE), $(BSP_SRC))
        C_SOURCES += $(BSP_SRC)

ARCH_SRC =  \
        ${wildcard $(ARCH_DIR)/common/*.c} \
        ${wildcard $(ARCH_DIR)/arm/cortex-m/src/*.c} \
        ${wildcard $(ARCH_DIR)/arm/cortex-m/cortex-m4/*.c}
        C_SOURCES += $(ARCH_SRC)

USER_SRC =  \
        $(TARGET_DIR)/os_adapt/os_adapt.c \
        $(TARGET_DIR)/Src/dwt.c \
        $(TARGET_DIR)/Src/gpio.c \
        $(TARGET_DIR)/Src/Huawei_IoT_QR_Code.c \
        $(TARGET_DIR)/Src/i2c.c \
        $(TARGET_DIR)/Src/loader_main.c \
        $(TARGET_DIR)/Src/main.c \
        $(TARGET_DIR)/Src/spi.c \
        $(TARGET_DIR)/Src/stm32l4xx_it.c \
        $(TARGET_DIR)/Src/sys_init.c \
        $(TARGET_DIR)/Src/system_stm32l4xx.c \
        $(TARGET_DIR)/Src/usart.c \
        $(TARGET_DIR)/Src/uart_debug.c
        C_SOURCES += $(USER_SRC)

ifeq ($(WITH_LWIP), yes)
LWIP_SRC =  \
        ${wildcard $(COMPONENTS_DIR)net/lwip/lwip-2.0.3/src/api/*.c} \
        ${wildcard $(COMPONENTS_DIR)net/lwip/lwip-2.0.3/src/core/ipv4/*.c} \
        ${wildcard $(COMPONENTS_DIR)net/lwip/lwip-2.0.3/src/core/ipv6/*.c} \
        ${wildcard $(COMPONENTS_DIR)net/lwip/lwip-2.0.3/src/core/*.c} \
        ${wildcard $(COMPONENTS_DIR)net/lwip/lwip-2.0.3/src/netif/ethernet.c}
        C_SOURCES += $(LWIP_SRC)

LWIP_PORT_SRC = \
        ${wildcard $(COMPONENTS_DIR)net/lwip/lwip_port/OS/*.c}
        C_SOURCES += $(LWIP_PORT_SRC)
endif


ifeq ($(WITH_LWM2M), yes)
ER_COAP_SRC = \
        ${wildcard $(COMPONENTS_DIR)connectivity/lwm2m/core/er-coap-13/er-coap-13.c}
        C_SOURCES += $(ER_COAP_SRC)

LWM2M_SRC = \
        ${wildcard $(COMPONENTS_DIR)connectivity/lwm2m/core/*.c} \
        ${wildcard $(COMPONENTS_DIR)connectivity/lwm2m/examples/shared/*.c}
        C_SOURCES += $(LWM2M_SRC)

ATINY_TINY_SRC = \
        ${wildcard $(COMPONENTS_DIR)connectivity/agent_tiny/atiny_lwm2m/*.c}

AGENT_DEMO_SRC = \
        ${wildcard $(DEMOS_DIR)/agenttiny_lwm2m/*.c}
        C_SOURCES += $(AGENT_DEMO_SRC)
endif

SOCKET_ADAPTER_SRC = \
        ${wildcard $(COMPONENTS_DIR)net/sal/*.c}
        C_SOURCES += $(SOCKET_ADAPTER_SRC)

ATINY_LOG = \
        ${wildcard $(COMPONENTS_DIR)log/*.c}
        C_SOURCES += $(ATINY_LOG)


ifeq ($(WITH_MQTT), yes)
MQTT_SRC = \
        ${wildcard $(COMPONENTS_DIR)connectivity/mqtt/MQTTPacket/src/*.c} \
        $(COMPONENTS_DIR)/connectivity/mqtt/MQTTClient-C/src/MQTTClient.c \
        $(COMPONENTS_DIR)/connectivity/mqtt/MQTTClient-C/src/liteOS/MQTTliteos.c
        C_SOURCES += $(MQTT_SRC)
ATINY_TINY_MQTT_SRC = \
        ${wildcard $(COMPONENTS_DIR)connectivity/agent_tiny/atiny_mqtt/*.c}
        C_SOURCES += $(ATINY_TINY_MQTT_SRC)
AGENT_DEMO_MQTT_SRC = \
        ${wildcard $(DEMOS_DIR)/agenttiny_mqtt/*.c}
        C_SOURCES += $(AGENT_DEMO_MQTT_SRC)
CJSON_SRC = \
        $(COMPONENTS)lib/cJSON/cJSON.c}
        C_SOURCES += $(CJSON_SRC)
        C_SOURCES += $(TARGET_DIR)/Src/flash_adaptor.c
endif

ifeq ($(WITH_FILESYSTEM), yes)
FS_SRC = \
        ${wildcard $(COMPONENTS_DIR)fs/vfs/*.c}
        C_SOURCES += $(FS_SRC)

FS_DEMO_COMMON_SRC = \
        $(DEMOS_DIR)/fs/fs_common.c}
        C_SOURCES += $(FS_DEMO_COMMON_SRC)

FS_SPIFFS_SRC = \
        $(TARGET_DIR)/Src/spiffs_hal.c \
        $(DEMOS_DIR)fs/spiffs/*.c} \
        $(DEMOS_DIR)fs/spiffs/spiffs_git/src/*.c}

FS_FATFS_SRC = \
        $(TARGET_DIR)/Src/fatfs_hal.c \
        $(COMPONENTS)fs/fatfs/*.c} \
        $(COMPONENTS)fs/fatfs/ff13b/source/*.c}

ifeq ($(IS_COMPILE_ALLFS), ALL)
        C_SOURCES += $(FS_SPIFFS_SRC)
        C_SOURCES += $(FS_FATFS_SRC)
        C_SOURCES += $(DEMOS_DIR)/fs/fatfs_demo.c
        C_SOURCES += $(DEMOS_DIR)/fs/spiffs_demo.c
else ifeq ($(FILESYSTEM_TYPE), SPIFFS)
        C_SOURCES += $(FS_SPIFFS_SRC)
        C_SOURCES += $(DEMOS_DIR)/fs/spiffs_demo.c
else ifeq ($(FILESYSTEM_TYPE), FATFS)
        C_SOURCES += $(FS_FATFS_SRC)
        C_SOURCES += $(DEMOS_DIR)/fs/fatfs_demo.c
endif
endif

######################################
# firmware library
######################################
PERIFLIB_SOURCES =


#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4
# fpu
FPU = -mfpu=fpv4-sp-d16
# float-abi
FLOAT-ABI = -mfloat-abi=hard
# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS =  \
     -D USE_HAL_DRIVER \
     -D STM32L431xx \
     -D NDEBUG \
     -D __LITEOS__ \
     -D _ALL_SOURCE \
     -DLOSCFG_PLATFORM_UART_WITHOUT_VFS

ifeq ($(WITH_LWM2M), yes)
        C_DEFS += \
            -D LWM2M_LITTLE_ENDIAN \
            -D LWM2M_CLIENT_MODE
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

# AS includes
AS_INCLUDES =

# C includes
LITEOS_LIBSEC_INCLUDE :=  $(LIB_DIR)/libsec/include
        C_INCLUDES += $(LITEOS_LIBSEC_INCLUDE)

LITEOS_LIBC_INCLUDE = \
        -I $(LIB_DIR)/libc/arch/arm \
        -I $(LIB_DIR)/libc/arch/generic \
        -I $(LIB_DIR)/libc/src/include \
        -I $(LIB_DIR)/libc/src/internal \
        -I $(LIB_DIR)/libc/include \
        -I $(LIB_DIR)/hw/include \
        -I $(LIB_DIR)/hw/include/bits
        C_INCLUDES += $(LITEOS_LIBC_INCLUDE)

LIBS_INCLUDE := -I $(LIB_DIR)/libc/arch/generic \
        -I $(LIB_DIR)/libc/src/internal \
        -I $(LIB_DIR)/libc/src/crypt \
        -I $(LIB_DIR)/libc/src/ctype \
        -I $(LIB_DIR)/libc/src/dirent \
        -I $(LIB_DIR)/libc/src/errno \
        -I $(LIB_DIR)/libc/src/ipc \
        -I $(LIB_DIR)/libc/src/locale \
        -I $(LIB_DIR)/libc/src/math \
        -I $(LIB_DIR)/libc/src/multibyte \
        -I $(LIB_DIR)/libc/src/networknetwork \
        -I $(LIB_DIR)/libc/src/passwd \
        -I $(LIB_DIR)/libc/src/prng \
        -I $(LIB_DIR)/libc/src/process \
        -I $(LIB_DIR)/libc/src/regex \
        -I $(LIB_DIR)/libc/src/search \
        -I $(LIB_DIR)/libc/src/time \
        -I $(COMPAT_DIR)/posix/src \
        -I $(LIB_DIR)/linux/include \
        -I $(LIB_DIR)/zlib/include
        C_INCLUDES += $(LIBS_INCLUDE)

INCLUDE_INC = \
        -I $(TOP_DIR)/include
        C_INCLUDES += $(INCLUDE_INC)

HAL_DRIVER_INC = \
        -I $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Inc \
        -I $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy
        C_INCLUDES += $(HAL_DRIVER_INC)

HARDWARE_INC = \
        -I $(TARGET_DIR)/Hardware/Inc} \
        -I $(TARGET_DIR)/Hardware/LCD} \
        -I $(TARGET_DIR)/Inc
        C_INCLUDES += $(HARDWARE_INC)

CMSIS_INC = \
        -I $(ARCH_DIR)/arm/common/cmsis
        C_INCLUDES += $(CMSIS_INC)

LITEOS_CMSIS = \
        -I $(OSDEPENDS_DIR)/liteos/cmsis
        C_INCLUDES += $(LITEOS_CMSIS)

BSP_INC = \
        -I $(TARGETS_DIR)/bsp/common \
        -I $(TARGETS_DIR)/bsp/include \
        -I $(TARGETS_DIR)/bsp/hw/include \
        -I $(TARGET_DIR)/include \
        -I $(TARGET_DIR)/Drivers/STM32L4xx_HAL_Driver/Inc
        C_INCLUDES += $(BSP_INC)

USER_INC = \
        -I $(TARGET_DIR)/Hardware/Inc \
        -I $(TARGET_DIR)/Hardware/LCD \
        -I $(TARGET_DIR)/include
        C_INCLUDES += $(USER_INC)

KERNEL_INC = \
        -I $(KERNEL_DIR)/base/include \
        -I $(KERNEL_DIR)/extended/include \
        -I $(KERNEL_DIR)/include \
        -I $(LIB_DIR)/libsec/include
        C_INCLUDES += $(KERNEL_INC)

ARCH_INC = \
        -I $(ARCH_DIR)/common \
        -I $(ARCH_DIR)/arm/include \
        -I $(ARCH_DIR)/arm/cortex-m/include \
        -I $(ARCH_DIR)/arm/cortex-m/src/include \
        -I $(ARCH_DIR)/arm/cortex-m/cortex-m4/include
        C_INCLUDES += $(ARCH_INC)

ifeq ($(WITH_LWIP), yes)
LWIP_INC = \
        -I $(COMPONENTS_DIR)/net/lwip/lwip-2.0.3/src/include
        C_INCLUDES += $(LWIP_INC)

LWIP_PORT_INC = \
        -I $(COMPONENTS_DIR)/net/lwip/lwip_port \
        -I $(COMPONENTS_DIR)/net/lwip/lwip_port/OS
        C_INCLUDES += $(LWIP_PORT_INC)
endif

ifeq ($(WITH_LWM2M), yes)
ER_COAP_INC = \
        -I $(COMPONENTS_DIR)/connectivity/lwm2m/core/er-coap-13
        C_INCLUDES += $(ER_COAP_INC)
LWM2M_INC = \
        -I $(COMPONENTS_DIR)/connectivity/lwm2m/core \
        -I $(COMPONENTS_DIR)/connectivity/lwm2m/examples/shared
        C_INCLUDES += $(LWM2M_INC)
endif

ifeq ($(WITH_MQTT), yes)
MQTT_INC = \
        -I $(COMPONENTS_DIR)/connectivity/mqtt/MQTTClient-C/src \
        -I $(COMPONENTS_DIR)/connectivity/mqtt/MQTTClient-C/src/liteOS \
        -I $(COMPONENTS_DIR)/connectivity/mqtt/MQTTPacket/src \
        -I $(COMPONENTS_DIR)/lib/cJSON
        C_INCLUDES += $(MQTT_INC)
endif

DEMO_INC = \
        -I $(TOP_DIR)/demos
        C_INCLUDES += $(DEMO_INC)

ifeq ($(WITH_FILESYSTEM), yes)
FS_SPIFFS_INC = \
        -I $(COMPONENTS_DIR)/fs/spiffs/spiffs_git/src \
        -I $(COMPONENTS_DIR)/fs/spiffs/spiffs_git/src/default

FS_FATFS_INC = \
        -I $(COMPONENTS_DIR)/fs/fatfs/ff13b/source \
        -I $(COMPONENTS_DIR)/fs/fatfs/ff13b/source/default

ifeq ($(IS_COMPILE_ALLFS), ALL)
        C_INCLUDES += $(FS_SPIFFS_INC)
        C_INCLUDES += $(FS_FATFS_INC)
else ifeq ($(FILESYSTEM_TYPE), SPIFFS)
        C_INCLUDES += $(FS_SPIFFS_INC)
else ifeq ($(FILESYSTEM_TYPE), FATFS)
        C_INCLUDES += $(FS_FATFS_INC)
endif
endif

ifeq ($(WITH_LITEOS_TEST), yes)
    include test_liteos.mk
else
C_DEFS += \
        -DLOSCFG_PLATFORM_OSAPPINIT
endif

############################# Security Option Begin #############################
LITEOS_SSP = -fno-stack-protector
ifeq ($(LOSCFG_CC_STACKPROTECTOR), y)
     LITEOS_SSP = -fstack-protector --param ssp-buffer-size=4
endif

ifeq ($(LOSCFG_CC_STACKPROTECTOR_STRONG), y)
    LITEOS_SSP = -fstack-protector-strong
endif

ifeq ($(LOSCFG_CC_STACKPROTECTOR_ALL), y)
    LITEOS_SSP = -fstack-protector-all
endif
############################# Security Option End ##############################
# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) $(LITEOS_SSP) -Wall -fdata-sections -ffunction-sections -nostdlib -nostdinc

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$@"

#######################################
# LDFLAGS
#######################################
# link script
LD_FILE = os.ld

LDSCRIPT = $(GCC_DIR)/$(LD_FILE)

# libraries
LIBS = -lc -lm -lnosys

LIBDIR = -L$(TARGETS_DIR)/Lib
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

#######################################
# set obj and build
#######################################
C_OBJ :=

C_OBJ += $(patsubst $(LIB_DIR)/%.c,$(BUILD_DIR)/lib/%.o,$(filter $(LIB_DIR)/%.c,$(C_SOURCES)))
C_OBJ += $(patsubst $(COMPAT_DIR)/%.c,$(BUILD_DIR)/compat/%.o,$(filter $(COMPAT_DIR)/%.c,$(C_SOURCES)))
C_OBJ += $(patsubst $(ARCH_DIR)/%.c,$(BUILD_DIR)/arch/%.o,$(filter $(ARCH_DIR)/%.c,$(C_SOURCES)))
C_OBJ += $(patsubst $(COMPONENTS_DIR)/%.c,$(BUILD_DIR)/components/%.o,$(filter $(COMPONENTS_DIR)/%.c,$(C_SOURCES)))
C_OBJ += $(patsubst $(DEMOS_DIR)/%.c,$(BUILD_DIR)/demos/%.o,$(filter $(DEMOS_DIR)/%.c,$(C_SOURCES)))
C_OBJ += $(patsubst $(KERNEL_DIR)/%.c,$(BUILD_DIR)/kernel/%.o,$(filter $(KERNEL_DIR)/%.c,$(C_SOURCES)))
C_OBJ += $(patsubst $(OSDEPENDS_DIR)/%.c,$(BUILD_DIR)/osdepends/%.o,$(filter $(OSDEPENDS_DIR)/%.c,$(C_SOURCES)))
C_OBJ += $(patsubst $(TARGETS_DIR)/%.c,$(BUILD_DIR)/targets/%.o,$(filter $(TARGETS_DIR)/%.c,$(C_SOURCES)))
C_OBJ += $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test/%.o,$(filter $(TEST_DIR)/%.c,$(C_SOURCES)))

S_OBJ :=
S_OBJ += $(patsubst $(ARCH_DIR)/%.S,$(BUILD_DIR)/arch/%.o,$(filter $(ARCH_DIR)/%.S,$(ASM_SOURCES_ARCH)))
S_OBJ += $(patsubst $(GCC_DIR)/%.S,$(BUILD_DIR)/targets/STM32L431_BearPi/GCC/%.o,$(filter $(GCC_DIR)/%.S,$(ASM_SOURCES_GCC)))

OBJ_DIRS :=
OBJ_DIRS +=  $(dir $(C_OBJ))
OBJ_DIRS +=  $(dir $(S_OBJ))
OBJ_DIRS := $(sort $(OBJ_DIRS))

vpath %.c $(TOP_DIR)
vpath %.S $(TOP_DIR)

all:$(BUILD_DIR)/$(TARGET).elf
	-$(HEX) $< $(BUILD_DIR)/$(TARGET).hex
	-$(BIN) $< $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/$(TARGET).elf:$(OBJ_DIRS) $(C_OBJ) $(S_OBJ)
	$(CC) $(C_OBJ) $(S_OBJ) $(LDFLAGS) -o $@
	$(SZ) $@

$(OBJ_DIRS):
	-mkdir -p $@

$(C_OBJ):$(BUILD_DIR)/%.o:%.c
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(@:%.o=%.lst) $<  -o $@

$(S_OBJ):$(BUILD_DIR)/%.o:%.S
	$(AS) -c $(ASFLAGS) $< -o $@

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

# *** EOF ***
