include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := $(LITEOS_PLATFORM)

-include $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/config.mk

USER_SRC = \
    os_adapt/os_adapt.c \
    $(wildcard Src/*.c) \
    $(LITEOSTOPDIR)/targets/STM32F767_Fire/Drivers/BSP/stm32f767_fire_lcd.c
    C_SOURCES += $(USER_SRC)

# C includes
HAL_DRIVER_INC = \
   -I $(LITEOSTOPDIR)/targets/bsp/drivers/STM32F7xx_HAL_Driver_1_2_10/Inc \
   -I $(LITEOSTOPDIR)/targets/bsp/drivers/STM32F7xx_HAL_Driver_1_2_10/Inc/Legacy
    BOARD_INCLUDES += $(HAL_DRIVER_INC)

INCLUDE_INC = \
    -I $(LITEOSTOPDIR)/include
    BOARD_INCLUDES += $(INCLUDE_INC)

BSP_INC = \
    -I $(LITEOSTOPDIR)/targets/bsp/common \
    -I $(LITEOSTOPDIR)/targets/bsp/include \
    -I $(LITEOSTOPDIR)/targets/bsp/hw/include \
    -I $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/include \
    -I $(LITEOSTOPDIR)/kernel/extended/include \
    -I $(LITEOSTOPDIR)/kernel/include \
    -I $(LITEOSTOPDIR)/targets/STM32F767_Fire/Drivers/BSP/
    BOARD_INCLUDES += $(BSP_INC)

USER_INC = \
    -I $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/Inc
    BOARD_INCLUDES += $(USER_INC)

# C defines
C_DEFS += \
    -DUSE_HAL_DRIVER \
    -DSTM32F767xx \
    -DNDEBUG \
    -D__LITEOS__ \
    -D_ALL_SOURCE
###########################################add support for lvgl########################################################
ifeq ($(LOSCFG_GUI_ENABLE), y)
LITEGL_INCLUDE += $(DEMOS_INCLUDE)
LVGl_GUI_INC = \
    -I $(LITEOSTOPDIR)/targets/STM32F767_Fire/Drivers
    LITEGL_INCLUDE += $(LVGl_GUI_INC)

LVGL_DRIVER_SRC = \
    ${wildcard $(LITEOSTOPDIR)/targets/STM32F767_Fire/Drivers/tft/*.c}
    C_SOURCES += $(LVGL_DRIVER_SRC)

LITEGL_LIB = -Xlinker -no-enum-size-warning

BOARD_INCLUDES += $(LITEGL_INCLUDE) $(LIBSEC_INCLUDE) $(HAL_DRIVER_INC) $(USER_INC) $(CMSIS_INC) $(KERNEL_INC) $(ARCH_INC)
C_DEFS += -DLV_CONF_INCLUDE_SIMPLE
endif
#######################################################################################################################
ASM_SOURCES = \
    ${wildcard los_startup_gcc.S}

BOARD_SRCS += $(ASM_SOURCES)
BOARD_SRCS += $(C_SOURCES)

LOCAL_SRCS := $(subst $(CURDIR)/,, $(BOARD_SRCS))

BOARD_DEF += $(C_DEFS)
LOCAL_INCLUDE += $(BOARD_INCLUDES)

LOCAL_FLAGS := $(LITEOS_CFLAGS_INTERWORK) $(BOARD_DEF) $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

include $(MODULE)
