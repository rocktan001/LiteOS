include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := $(LITEOS_PLATFORM)

-include $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/config.mk

ALL_ASSRCS := $(wildcard board/$(LITEOS_PLATFORM)/*.S)
ASSRCS := $(subst board/$(LITEOS_PLATFORM)/board.ld.S,,$(ALL_ASSRCS))

LOCAL_SRCS += $(ASSRCS)
# C sources
HAL_DRIVER_SRC =  \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
        C_SOURCES += $(HAL_DRIVER_SRC)

HARDWARE_SRC =  \
        ${wildcard $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Hardware/Src/*.c}
        C_SOURCES += $(HARDWARE_SRC)

HAL_DRIVER_SRC_NO_BOOTLOADER =  \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c
        C_SOURCES += $(HAL_DRIVER_SRC_NO_BOOTLOADER)

USER_SRC =  \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/os_adapt/os_adapt.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Src/main.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Src/system_stm32f4xx.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Src/usart.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Src/dwt.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Src/eth.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Src/sys_init.c \
        $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Src/user_task.c
        C_SOURCES += $(USER_SRC)

# C includes
HAL_DRIVER_INC = \
        -I $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Inc \
        -I $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
        BOARD_INCLUDES += $(HAL_DRIVER_INC)

INCLUDE_INC = \
        -I $(LITEOSTOPDIR)/include
        BOARD_INCLUDES += $(INCLUDE_INC)

BSP_INC = \
        -I $(LITEOSTOPDIR)/targets/bsp/common \
        -I $(LITEOSTOPDIR)/targets/bsp/include \
        -I $(LITEOSTOPDIR)/targets/bsp/hw/include \
        -I $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/include \
        -I $(LITEOSTOPDIR)/kernel/extended/include
        BOARD_INCLUDES += $(BSP_INC)

HARDWARE_INC = \
        -I $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Hardware/Inc
        BOARD_INCLUDES += $(HARDWARE_INC)

USER_INC = \
        -I $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/Inc
        BOARD_INCLUDES += $(USER_INC)

# C defines
C_DEFS =  \
        -DUSE_HAL_DRIVER \
        -DSTM32F429xx \
        -DNDEBUG \
        -D__LITEOS__ \
        -D_ALL_SOURCE


ASM_SOURCES =  \
        ${wildcard $(LITEOSTOPDIR)/targets/Cloud_STM32F429IGTx_FIRE/los_startup_gcc.S}

BOARD_SRCS += $(ASM_SOURCES)
BOARD_SRCS += $(C_SOURCES)

LOCAL_SRCS := $(subst $(CURDIR)/,, $(BOARD_SRCS))

BOARD_DEF += $(C_DEFS)
LOCAL_INCLUDE += $(BOARD_INCLUDES)

LOCAL_FLAGS := $(BOARD_DEF) $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

include $(MODULE)
