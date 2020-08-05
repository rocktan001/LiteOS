############################# SRCs #################################
HWI_SRC     :=
MMU_SRC     :=
NET_SRC     :=
TIMER_SRC   :=
HRTIMER_SRC :=
UART_SRC    :=
USB_SRC     :=

############################# HI3556V200 Options#################################
ifeq ($(LOSCFG_PLATFORM_HI3556V200), y)
    HWI_TYPE     := arm/interrupt/gic
    TIMER_TYPE   := arm/timer/arm_generic
    HRTIMER_TYPE := hisoc/hrtimer
    NET_TYPE     := hieth
    UART_TYPE    := amba_pl011
    USB_TYPE     := usb3.0_hi3556v200
    LITEOS_CMACRO_TEST += -DTEST3556V200

########################## hi1980_imu Options##############################
else ifeq ($(LOSCFG_PLATFORM_HI1980_IMU), y)
    HWI_TYPE    := arm/interrupt/gic
    TIMER_TYPE  := arm/timer/arm_generic
    UART_TYPE   := amba-pl011
    WARNING_AS_ERROR   :=
    LITEOS_CMACRO_TEST += -DTESTHI1980IMU

########################## qemu virt a53 Options##############################
else ifeq ($(LOSCFG_PLATFORM_QEMU_VIRT_A53), y)
    HWI_TYPE    := arm/interrupt/gic
    TIMER_TYPE  := arm/timer/arm_generic
    UART_TYPE   := amba_pl011
    LITEOS_CMACRO_TEST += -DTESTVIRTA53

######################### realview pbx a9 Options#############################
else ifeq ($(LOSCFG_PLATFORM_PBX_A9), y)
    HWI_TYPE    := arm/interrupt/gic
    TIMER_TYPE  := arm/timer/arm_private
    UART_TYPE   := amba_pl011
    LITEOS_CMACRO_TEST += -DTESTPBXA9
######################### STM32F769IDISCOVERY Options#############################
else ifeq ($(LOSCFG_PLATFORM_STM32F769IDISCOVERY), y)
    LITEOS_CMACRO_TEST += -DTESTSTM32F769IDISCOVERY
    TIMER_TYPE := arm/timer/arm_cortex_m

######################### STM32F429IGTX Options#############################
else ifeq ($(LOSCFG_PLATFORM_STM32F429IGTX), y)
#    TIMER_TYPE := arm/timer/arm_private
#    LITEOS_CMACRO_TEST += -DTESTSTM32F429IGTX
endif

HWI_SRC     := bsp/hw/$(HWI_TYPE)
TIMER_SRC   := bsp/hw/$(TIMER_TYPE)
HRTIMER_SRC := bsp/hw/$(HRTIMER_TYPE)
NET_SRC     := bsp/net/$(NET_TYPE)
UART_SRC    := bsp/uart/$(UART_TYPE)
USB_SRC     := bsp/usb/$(USB_TYPE)

#LITEOS_BASELIB       += -lbsp

LITEOS_PLATFORM      := $(subst $\",,$(LOSCFG_PLATFORM))


PLATFORM_INCLUDE := -I $(LITEOSTOPDIR)/targets/bsp/common \
                    -I $(LITEOSTOPDIR)/targets/bsp/common/pm \
                    -I $(LITEOSTOPDIR)/targets/bsp/hw/include \
                    -I $(LITEOSTOPDIR)/targets/bsp/include \
                    -I $(LITEOSTOPDIR)/targets/bsp/$(UART_SRC)
                    #-I $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/include \
                    -I $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/include/asm \

#$(info,  platform include = $(PLATFORM_INCLUDE))

ifeq ($(LITEOS_PLATFORM), hi3556v200)
    PLATFORM_INCLUDE += -I $(LITEOSTOPDIR)/platform/bsp/board/$(LITEOS_PLATFORM)/include/hisoc
endif

-include $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/GCC/config.mk
-include $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/board.mk

#LIB_SUBDIRS             += targets
#LIB_SUBDIRS             += targets/$(LITEOS_PLATFORM)

LITEOS_PLATFORM_INCLUDE += $(PLATFORM_INCLUDE)
LITEOS_CXXINCLUDE       += $(PLATFORM_INCLUDE)
