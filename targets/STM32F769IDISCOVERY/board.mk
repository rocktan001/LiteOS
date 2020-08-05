# C sources
HAL_DRIVER_SRC =  \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/ft5336/ft5336.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/ft6x06/ft6x06.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/otm8009a/otm8009a.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/wm8994/wm8994.c \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/*.c} \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/STM32F769I-Discovery/*.c}

HAL_DRIVER_EXCLUDE = \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.c
HAL_DRIVER_SRC := $(filter-out $(HAL_DRIVER_EXCLUDE), $(HAL_DRIVER_SRC))

HAL_DRIVER_SRC_FILTERS = \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mmc.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smbus.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_rtc_alarm_template.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_rtc_wakeup_template.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_tim_template.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dac.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma2d.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_i2c.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_lptim.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_pwr.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rng.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rtc.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_spi.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_tim.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.c
        C_SOURCES += $(filter-out $(HAL_DRIVER_SRC_FILTERS), $(HAL_DRIVER_SRC))

BSP_SRC = \
        ${wildcard $(LITEOSTOPDIR)/targets/bsp/common/*.c}
BSP_SRC_EXCLUDE = \
        $(LITEOSTOPDIR)/targets/bsp/common/console.c \
        $(LITEOSTOPDIR)/targets/bsp/common/virtual_serial.c
BSP_SRC := $(filter-out $(BSP_SRC_EXCLUDE), $(BSP_SRC))
        C_SOURCES += $(BSP_SRC)

BSP_HWI_SRC = \
        ${wildcard  $(LITEOSTOPDIR)/targets/bsp/common/hwi/*.c}
        C_SOURCES += $(BSP_HWI_SRC)

#just a stub interface
BSP_TIMER_SRC = \
        ${wildcard  $(LITEOSTOPDIR)/targets/bsp/hw/arm/timer/arm_private/*.c}
        C_SOURCES += $(BSP_TIMER_SRC)

OS_DEPENDS_SRC = \
        ${wildcard $(LITEOSTOPDIR)/osdepends/liteos/*.c}
        C_SOURCES += $(OS_DEPENDS_SRC)

USER_SRC =  \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/os_adapt/os_adapt.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Src/main.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Src/platform_init.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Src/stm32f7xx_it.c \
        $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Src/system_stm32f7xx.c
        C_SOURCES += $(USER_SRC)


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
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/STM32F769I-Discovery \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Inc \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/STM32F769I-Discovery/Utilities/Fonts \
        -I $(LITEOSTOPDIR)/compat/cmsis
        BOARD_INCLUDES += $(HAL_DRIVER_INC)

INCLUDE_INC = \
        -I $(LITEOSTOPDIR)/include
        BOARD_INCLUDES += $(INCLUDE_INC)

BSP_HWI_INC = \
        -I $(LITEOSTOPDIR)/targets/bsp/common/hwi
        BOARD_INCLUDES += $(BSP_HWI_INC)

BSP_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Inc \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/include\asm \
        -I $(LITEOSTOPDIR)/arch/arm/common/cmsis \
        -I $(LITEOSTOPDIR)/arch/arm/include \
        -I $(LITEOSTOPDIR)/arch/arm/cortex_m/include \
        -I $(LITEOSTOPDIR)/arch/arm/cortex_m/cortex-m7 \
        -I $(LITEOSTOPDIR)/compat/posix/src \
        -I $(LITEOSTOPDIR)/kernel/extended/include
        BOARD_INCLUDES += $(BSP_INC)

HARDWARE_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Hardware/Inc
        BOARD_INCLUDES += $(HARDWARE_INC)

LITEOS_CMSIS_INC = \
        -I $(LITEOSTOPDIR)/osdepends/liteos/cmsis
        BOARD_INCLUDES += $(LITEOS_CMSIS_INC)

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
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Inc \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/include \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/wm8994 \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Inc \
        -I $(LITEOSTOPDIR)/osdepends/liteos/cmsis/1.0 \
        -I $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/OS_CONFIG
        BOARD_INCLUDES += $(USER_INC)

# C defines
C_DEFS =  \
        -D STM32F7 \
        -D STM32F769xx \
        -D USE_HAL_DRIVER \
        -D USE_STM32F769I_DISCO \
        -D USE_STM32769I_DISCOVERY \
        -D MBEDTLS_CONFIG_FILE=\"mbedtls_config.h\" \
        -D HAVE_STDINT_H

ifeq ($(WITH_FILESYSTEM), yes)
        C_DEFS += -DFS_$(FILESYSTEM_TYPE)
endif

ifeq ($(WITH_LITEOS_TEST), yes)
        include test_liteos.mk
else
        C_DEFS += -DLOSCFG_PLATFORM_OSAPPINIT
endif

###########################################add support for lvgl########################################################
ifeq ($(WITH_LVGL), yes)
#LiteGL Build Options
LVGL_DIR = $(LITEOSTOPDIR)/components/gui/lvgl
LVGL_DEMO_DIR = $(LITEOSTOPDIR)/demos/gui
LVGL_SRC_DIR = $(LVGL_DIR)/src
LVGL_DRIVER_DIR = $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers

LVGL_DRIVER_SRC =  \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/tft/*.c} \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/Drivers/touchpad/*.c}

LVGL_SRC = \
    $(wildcard $(LVGL_SRC_DIR)/lv_core/*.c) \
    $(wildcard $(LVGL_SRC_DIR)/lv_draw/*.c) \
    $(wildcard $(LVGL_SRC_DIR)/lv_font/*.c) \
    $(wildcard $(LVGL_SRC_DIR)/lv_gpu/*.c) \
    $(wildcard $(LVGL_SRC_DIR)/lv_hal/*.c) \
    $(wildcard $(LVGL_SRC_DIR)/lv_misc/*.c) \
    $(wildcard $(LVGL_SRC_DIR)/lv_themes/*.c) \
    $(wildcard $(LVGL_SRC_DIR)/lv_widgets/*.c)

LVGL_DEMO_SRC = \
    $(wildcard $(LVGL_DEMO_DIR)/*.c) \
    $(wildcard $(LVGL_DEMO_DIR)/widgets/*.c)
LITEGL_INCLUDE = -I$(LVGL_DIR) -I$(LVGL_SRC_DIR) -I$(LVGL_DEMO_DIR) -I$(LVGL_DRIVER_DIR)
LITEGL_LIB = -Xlinker -no-enum-size-warning

C_SOURCES += $(LVGL_SRC) $(LVGL_DEMO_SRC) $(LVGL_DRIVER_SRC)
BOARD_INCLUDES += $(LITEGL_INCLUDE) $(LIBSEC_INCLUDE) $(HAL_DRIVER_INC) $(USER_INC) $(CMSIS_INC) $(KERNEL_INC) $(ARCH_INC)
C_DEFS += -DLV_CONF_INCLUDE_SIMPLE
endif
#######################################################################################################################

ASM_SOURCES =  \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32F769IDISCOVERY/los_startup_gcc.S}

LOCAL_SRCS += $(ASM_SOURCES)
LOCAL_SRCS         += $(C_SOURCES)
LITEOS_CMACRO_TEST += $(C_DEFS)
PLATFORM_INCLUDE   += $(BOARD_INCLUDES)
