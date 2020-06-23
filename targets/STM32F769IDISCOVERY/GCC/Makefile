##########################################################################################################################
# STM32F769IDISCOVERY GCC compiler Makefile
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
#BIN       = $(OBJCOPY) -O binary -S
BIN       = $(OBJCOPY) -O binary -S -R .sdram.bss


PROJECTBASE = $(CURDIR)
override PROJECTBASE    := $(abspath $(PROJECTBASE))
TOP_DIR = $(PROJECTBASE)/../../..


#######################################
# paths
#######################################
# firmware library path
PERIFLIB_PATH =

# Build path
BUILD_DIR = build

######################################
# source
######################################
# ASM
ASM_SOURCES_s =  \
        ${wildcard $(PROJECTBASE)/los_startup_gcc.s}

ASM_SOURCES_S =  \
        ${wildcard $(TOP_DIR)/arch/arm/cortex-m/cortex-m7/gcc/*.S}

# C sources
HAL_DRIVER_SRC =  \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/ft5336/ft5336.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/ft6x06/ft6x06.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/otm8009a/otm8009a.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/wm8994/wm8994.c \
        ${wildcard $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/*.c} \
        ${wildcard $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/STM32F769I-Discovery/*.c} \
        ${wildcard $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/tft/*.c} \
        ${wildcard $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/touchpad/*.c} \

HAL_DRIVER_SRC_FILTERS = \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mmc.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smbus.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_rtc_alarm_template.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_rtc_wakeup_template.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_tim_template.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dac.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma2d.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_i2c.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_lptim.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_pwr.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rng.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rtc.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_spi.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_tim.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.c
        C_SOURCES += $(filter-out $(HAL_DRIVER_SRC_FILTERS), $(HAL_DRIVER_SRC))

LIBSEC_SRC = \
        ${wildcard $(TOP_DIR)/components/lib/libsec/src/*.c}
        C_SOURCES += $(LIBSEC_SRC)

KERNEL_SRC =  \
        ${wildcard $(TOP_DIR)/kernel/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/core/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/ipc/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/mem/bestfit_little/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/mem/membox/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/mem/common/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/misc/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/mp/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/om/*.c} \
        ${wildcard $(TOP_DIR)/kernel/base/sched/sched_sq/*.c} \
        ${wildcard $(TOP_DIR)/kernel/extended/tickless/*.c} \
        ${wildcard $(TOP_DIR)/kernel/extended/cpup/*.c} \
        ${wildcard $(TOP_DIR)/kernel/extended/cppsupport/*.c}
        C_SOURCES += $(KERNEL_SRC)

CMSIS_SRC =  \
        ${wildcard $(TOP_DIR)/osdepends/liteos/cmsis/*.c}
        C_SOURCES += $(CMSIS_SRC)

BSP_SRC = \
        ${wildcard $(TOP_DIR)/targets/bsp/common/*.c}
BSP_SRC_EXCLUDE = \
        $(TOP_DIR)/targets/bsp/common/console.c \
        $(TOP_DIR)/targets/bsp/common/virtual_serial.c
BSP_SRC := $(filter-out $(BSP_SRC_EXCLUDE), $(BSP_SRC))
        C_SOURCES += $(BSP_SRC)

ARCH_SRC =  \
        ${wildcard $(TOP_DIR)/arch/common/*.c} \
        ${wildcard $(TOP_DIR)/arch/arm/cortex-m/src/*.c} \
        ${wildcard $(TOP_DIR)/arch/arm/cortex-m/cortex-m7/*.c}
        C_SOURCES += $(ARCH_SRC)

USER_SRC =  \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/os_adapt/os_adapt.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Src/main.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Src/platform_init.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Src/stm32f7xx_it.c \
        $(TOP_DIR)/targets/STM32F769IDISCOVERY/Src/system_stm32f7xx.c
        C_SOURCES += $(USER_SRC)

######################################
# firmware library
######################################
PERIFLIB_SOURCES =


#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7
# fpu
FPU = -mfpu=fpv5-sp-d16
# float-abi
FLOAT-ABI = -mfloat-abi=softfp
# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS =  \
        -D STM32F7 \
        -D STM32F769xx \
        -D USE_HAL_DRIVER \
        -D USE_STM32F769I_DISCO \
        -D USE_STM32769I_DISCOVERY \
        -D MBEDTLS_CONFIG_FILE=\"mbedtls_config.h\" \
        -D HAVE_STDINT_H

# AS includes
AS_INCLUDES =

# C includes
HAL_DRIVER_INC = \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/STM32F769I-Discovery \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/STM32F7xx_HAL_Driver/Inc \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/STM32F769I-Discovery/Utilities/Fonts
        C_INCLUDES += $(HAL_DRIVER_INC)

INCLUDE_INC = \
        -I $(TOP_DIR)/include
        C_INCLUDES += $(INCLUDE_INC)

CMSIS_INC = \
        -I $(TOP_DIR)/arch/arm/common/cmsis
        C_INCLUDES += $(CMSIS_INC)

LITEOS_CMSIS = \
        -I $(TOP_DIR)/osdepends/liteos/cmsis
        C_INCLUDES += $(LITEOS_CMSIS)

BSP_INC = \
        -I $(TOP_DIR)/targets/bsp/common \
        -I $(TOP_DIR)/targets/bsp/include \
        -I $(TOP_DIR)/targets/bsp/hw/include \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/include
        C_INCLUDES += $(BSP_INC)


ARCH_INC = \
        -I $(TOP_DIR)/arch/common \
        -I $(TOP_DIR)/arch/arm/include \
        -I $(TOP_DIR)/arch/arm/cortex-m/include \
        -I $(TOP_DIR)/arch/arm/cortex-m/src/include \
        -I $(TOP_DIR)/arch/arm/cortex-m/cortex-m7/include
        C_INCLUDES += $(ARCH_INC)

KERNEL_INC = \
        -I $(TOP_DIR)/kernel/base/include  \
        -I $(TOP_DIR)/kernel/extended/include  \
        -I $(TOP_DIR)/kernel/include \
        -I $(TOP_DIR)/kernel/base/core \
        -I $(TOP_DIR)/components/lib/libsec/include
        C_INCLUDES += $(KERNEL_INC)

EXAMPLES_INC = \
        -I $(TOP_DIR)/examples/include
        C_INCLUDES += $(EXAMPLES_INC)


USER_INC = \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/Inc \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/Drivers/BSP/Components/wm8994 \
        -I $(TOP_DIR)/targets/STM32F769IDISCOVERY/OS_CONFIG
        C_INCLUDES += $(USER_INC)

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

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) $(LITEOS_SSP) -Wall -fdata-sections -ffunction-sections #-nostartfiles -static -fno-short-enums -fno-short-wchar

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

CFLAGS += -std=c99


#LiteGL Build Options
LVGL_DIR = $(TOP_DIR)/components/gui/lvgl
LVGL_DEMO_DIR = $(TOP_DIR)/demos/gui
LVGL_SRC_DIR = $(LVGL_DIR)/src

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
LITEGL_INCLUDE = -I$(LVGL_DIR) -I$(LVGL_SRC_DIR) -I$(LVGL_DEMO_DIR)
LITEGL_LIB = -Xlinker -no-enum-size-warning

C_SOURCES += $(LVGL_SRC) $(LVGL_DEMO_SRC)
C_INCLUDES += $(LITEGL_INCLUDE) $(LIBSEC_INCLUDE) $(HAL_DRIVER_INC) $(USER_INC) $(CMSIS_INC) $(KERNEL_INC) $(ARCH_INC) $(THIRD_INC)
CFLAGS += -DLV_CONF_INCLUDE_SIMPLE


#######################################
# LDFLAGS
#######################################
# link script
LD_FILE = STM32F769IDISCOVERY_LiteOS.ld
LDSCRIPT = $(PROJECTBASE)/$(LD_FILE)

# libraries
LIBS = -lc -lm -lnosys -L .

LDFLAGS = $(MCU) -specs=nano.specs -specs=nosys.specs  -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES_s:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES_s)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES_S:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES_S)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
