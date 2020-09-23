include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := $(LITEOS_PLATFORM)

-include $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/config.mk

ALL_ASSRCS := $(wildcard board/$(LITEOS_PLATFORM)/*.S)
ASSRCS := $(subst board/$(LITEOS_PLATFORM)/board.ld.S,,$(ALL_ASSRCS))

LOCAL_SRCS += $(ASSRCS)
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

HARDWARE_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/Inc
        BOARD_INCLUDES += $(HARDWARE_INC)

USER_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Inc
        BOARD_INCLUDES += $(USER_INC)

USER_INC = \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Inc \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/include \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/Inc \
        -I $(LITEOSTOPDIR)/targets/STM32L431_BearPi/Hardware/LCD
        BOARD_INCLUDES += $(USER_INC)

# C defines
C_DEFS =  \
     -D USE_HAL_DRIVER \
     -D NDEBUG \
     -D __LITEOS__ \
     -D _ALL_SOURCE

ASM_SOURCES =  \
        ${wildcard $(LITEOSTOPDIR)/targets/STM32L431_BearPi/los_startup_gcc.S}

BOARD_SRCS += $(ASM_SOURCES)
BOARD_SRCS += $(C_SOURCES)

LOCAL_SRCS := $(subst $(CURDIR)/,, $(BOARD_SRCS))

BOARD_DEF += $(C_DEFS)
LOCAL_INCLUDE += $(BOARD_INCLUDES)

LOCAL_FLAGS := $(BOARD_DEF) $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

include $(MODULE)
