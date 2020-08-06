# Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.

## platform relative ##
LITEOS_ARM_ARCH :=
LITEOS_CPU_TYPE :=
## c as cxx ld options ##
LITEOS_ASOPTS :=
LITEOS_COPTS_BASE :=
LITEOS_COPTS_EXTRA :=
LITEOS_COPTS_EXTRA_INTERWORK :=
LITEOS_COPTS_DEBUG :=
LITEOS_COPTS_NODEBUG :=
LITEOS_INTERWORK :=
LITEOS_CXXOPTS :=
LITEOS_CXXOPTS_BASE :=
LITEOS_LD_OPTS :=
LITEOS_GCOV_OPTS :=
## dynload ld options ##
LITEOS_DYNLOADOPTS :=
## macro define ##
LITEOS_CMACRO :=
LITEOS_CMACRO_TEST :=
LITEOS_CXXMACRO :=
## head file path and ld path ##
LITEOS_PLATFORM_INCLUDE :=
LITEOS_CXXINCLUDE :=
LITEOS_LD_PATH :=
LITEOS_LD_SCRIPT :=
LITEOS_MK_PATH :=
## c as cxx ld flags ##
LITEOS_ASFLAGS :=
LITEOS_CFLAGS :=
LITEOS_CFLAGS_INTERWORK :=
LITEOS_LDFLAGS :=
LITEOS_CXXFLAGS :=
## depended lib ##
LITEOS_BASELIB :=
LITEOS_LIBDEP :=
## directory ##
LIB_BIGODIR :=
LIB_SUBDIRS :=
##compiler##
LITEOS_COMPILER_CXXLIB_PATH :=
LITEOS_COMPILER_GCCLIB_PATH :=
LITEOS_COMPILER_GCC_INCLUDE :=

-include $(LITEOSTOPDIR)/.config

# Introduced compiler binaries which might different from gcc compilers.
# Those compilers need to implement like $(CC) $(GPP) like gcc does.
# Meanwhile Introduced compiler includes and lib paths
# Export : $(LITEOS_COMPILER_GCC_INCLUDE)
#          $(LITEOS_CXXINCLUDE)
#          $(LITEOS_COMPILER_GCCLIB_PATH)
#          $(LITEOS_COMPILER_CXXLIB_PATH)
ifeq ($(LOSCFG_COMPILER_XTENSA_32), y)
include $(LITEOSTOPDIR)/build/mk/compiler_xtensa.mk
else
# Supported GCC Compilers
# Also support "make CROSS_COMPILE=" to use third party compilers.
include $(LITEOSTOPDIR)/build/mk/compiler_gcc.mk
endif

HIDE    := @
MKDIR    = mkdir
RM       = -rm -rf
ECHO     = echo
ARFLAGS := cr

OS       ?= $(shell uname -s)
OBJ_MKDIR = if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi

# Generate file that contains link targets.
# Also support old style sub module make directly using "LITEOS_BASELIB +="
# which is not recommented.
include $(LITEOSTOPDIR)/build/mk/gen_link_targets.mk

## variable define ##
OUT  = $(LITEOSTOPDIR)/out/$(LITEOS_PLATFORM)
BUILD  = $(OUT)/obj
MK_PATH  = $(LITEOSTOPDIR)/build/mk
LITEOS_SCRIPTPATH  ?= $(LITEOSTOPDIR)/tools/scripts
LITEOS_LIB_BIGODIR  = $(OUT)/lib/obj
LOSCFG_ENTRY_SRC    = $(LITEOSTOPDIR)/targets/bsp/common/los_config.c
LITEOS_MENUCONFIG_H = $(LITEOSTOPDIR)/targets/bsp/common/menuconfig.h
LITEOS_PLATFORM_MENUCONFIG_H = $(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/include/menuconfig.h

### include variable
MODULE = $(MK_PATH)/module.mk
ifeq ($(LOSCFG_COMPILER_HIMIX_32), y)
LITEOS_CMACRO      += -D__COMPILER_HUAWEILITEOS__
else ifeq ($(LOSCFG_COMPILER_HIMIX100_64), y)
LITEOS_CMACRO      += -D__COMPILER_HUAWEILITEOS__
else ifeq ($(LOSCFG_COMPILER_HCC_64), y)
LITEOS_CMACRO      += -D__COMPILER_HUAWEILITEOS__
else ifeq ($(LOSCFG_COMPILER_XTENSA_32), y)
LITEOS_CMACRO      += -D__COMPILER_HUAWEILITEOS__
LITEOS_CMACRO      += -D__COMPILER_XTENSA__
endif

LITEOS_CMACRO      += -D__LITEOS__ -DSECUREC_IN_KERNEL=0 -D_ALL_SOURCE
LITEOS_BASELIB     += -lgcc

ifneq ($(findstring $(LOSCFG_COMPILER_ARM_NONE_EABI)$(LOSCFG_COMPILER_XTENSA_32), y), )
else
LITEOS_BASELIB     += -lgcc_eh
endif
AS_OBJS_LIBC_FLAGS  = -D__ASSEMBLY__
WARNING_AS_ERROR   := -Wall -Werror

-include $(LITEOSTOPDIR)/build/mk/dynload_ld.mk

include $(LITEOSTOPDIR)/arch/cpu.mk
include $(LITEOSTOPDIR)/targets/bsp.mk


# Export APIs from these module.
include $(LITEOSTOPDIR)/lib/api.mk
include $(LITEOSTOPDIR)/compat/api.mk
#include $(LITEOSTOPDIR)/drivers/api.mk
#include $(LITEOSTOPDIR)/fs/api.mk

#LIB_SUBDIRS += kernel compat lib fs net drivers
LIB_SUBDIRS += kernel compat lib

LITEOS_KERNEL_INCLUDE := -I $(LITEOSTOPDIR)/kernel/include

################################### Kernel Option Begin ###################################
LITEOS_BASELIB += -lbase
LIB_SUBDIRS       += kernel/base
LITEOS_KERNEL_INCLUDE   := -I $(LITEOSTOPDIR)/kernel/include
ifeq ($(LOSCFG_KERNEL_MEM_BESTFIT_LITTLE), y)
    MEM_TYPE    := bestfit_little
else
    MEM_TYPE    := bestfit
endif

ifeq ($(LOSCFG_SCHED_MQ), y)
    SCHED_TYPE  := sched_mq
else
    SCHED_TYPE  := sched_sq
endif

ifeq ($(LOSCFG_KERNEL_CPUP), y)
    LITEOS_BASELIB   += -lcpup
    LIB_SUBDIRS         += kernel/extended/cpup
    LITEOS_CPUP_INCLUDE := -I $(LITEOSTOPDIR)/kernel/extended/cpup
endif

################################### Net Option Begin ###################################
ifeq ($(LOSCFG_NET_LWIP_SACK_2_0), y)
    LITEOS_BASELIB += -llwip
    LITEOS_LWIP_SACK_INCLUDE   += \
        -I $(LITEOSTOPDIR)/net/lwip-2.0/include \
        -I $(LITEOSTOPDIR)/net/mac
    LWIP_MACROS += -DLWIP_CONFIG_FILE=\"lwip/lwipopts.h\"
    LITEOS_CMACRO     +=  $(LWIP_MACROS)
endif

ifeq ($(LOSCFG_NET_TELNET), y)
    LITEOS_TELNET_INCLUDE   += -I $(LITEOSTOPDIR)/net/telnet/include
endif
#################################### Net Option End####################################

############################# Tools && Debug Option Begin ##############################
ifeq ($(LOSCFG_GDB), y)
    LITEOS_BASELIB    += -lgdb
    LIB_SUBDIRS       += tools/gdb
    LITEOS_CMACRO += -DLOSCFG_GDB -DLOS_GDB_ICACHE
endif
ifeq ($(LOSCFG_COREDUMP), y)
    LITEOS_BASELIB    += -lcoredump
    LIB_SUBDIRS       += tools/coredump
    LITEOS_CMACRO += -DLOSCFG_COREDUMP
    LOSCFG_COMPRESS := y
endif

ifeq ($(LOSCFG_LLTSER) ,y)
    LITEOS_BASELIB    += -lgcov_ser
    LIB_SUBDIRS       += tools/gcov_ser
    LITEOS_CMACRO += -DLOSCFG_LLTSER
    LOSCFG_COMPRESS := y
endif

ifeq ($(LOSCFG_COMPRESS), y)
    LITEOS_BASELIB    += -lcompress
    LIB_SUBDIRS       += tools/compress
endif

ifeq ($(LOSCFG_COMPILE_DEBUG), y)
    LITEOS_COPTS_OPTMIZE = -O0 -g
    LITEOS_COPTS_OPTION  = -g -gdwarf-2
else
    LITEOS_COPTS_OPTMIZE = -O2
endif
    LITEOS_COPTS_DEBUG  += $(LITEOS_COPTS_OPTION) $(LITEOS_COPTS_OPTMIZE)
    LITEOS_INTERWORK += $(LITEOS_COPTS_OPTION) $(LITEOS_COPTS_OPTMIZE)
    LITEOS_CXXOPTS_BASE += $(LITEOS_COPTS_OPTION) $(LITEOS_COPTS_OPTMIZE)
    LITEOS_ASOPTS   += $(LITEOS_COPTS_OPTION)

ifeq ($(LOSCFG_SHELL), y)
    LITEOS_BASELIB += -lshell
    LIB_SUBDIRS       += shell
    ifeq ($(LOSCFG_SHELL_FULL_CAP), y)
        LITEOS_SHELL_INCLUDE  += -I $(LITEOSTOPDIR)/shell/full/include
    else
        LITEOS_SHELL_INCLUDE  += -I $(LITEOSTOPDIR)/shell/mini/include
    endif
endif

ifeq ($(LOSCFG_3RDPARTY), y)
    -include $(LITEOSTOPDIR)/3rdParty/3rdParty.mk
endif

ifeq ($(LOSCFG_PLATFORM_OSAPPINIT), y)

else
    -include $(LITEOSTOPDIR)/test/test.mk
endif

ifeq ($(LOSCFG_NULL_ADDRESS_PROTECT), y)
    LITEOS_CMACRO += -DLOSCFG_NULL_ADDRESS_PROTECT
endif

############################# Tools && Debug Option End #################################

############################# Security Option Begin ##############################
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

# TODO : THIS feature whether support or not depands on if its C++ libs
#        are compiled with liteos which should be controlled with KCONFIGS.
LITEOS_CXXMACRO   += -DLOSCFG_KERNEL_CPP_EXCEPTIONS_SUPPORT
LITEOS_CMACRO     += -DLOSCFG_KERNEL_CPP_EXCEPTIONS_SUPPORT

LITEOS_CXXINCLUDE +=  $(LITEOS_COMPILER_GCC_INCLUDE)

LITEOS_CXXOPTS_BASE  += -std=c++11 -nostdlib -nostdinc -nostdinc++ -fexceptions -fpermissive -fno-use-cxa-atexit \
                        -fno-builtin -frtti -fno-pic -ffunction-sections -fdata-sections $(WARNING_AS_ERROR) $(LITEOS_SSP)

ifneq ($(LOSCFG_COMPILER_XTENSA_32), y)
LITEOS_CXXOPTS_BASE  += -fno-omit-frame-pointer -Winvalid-pch
endif

LITEOS_NET_INCLUDE         := $(LITEOS_LWIP_SACK_INCLUDE)
LITEOS_LIB_INCLUDE         := $(LITEOS_LIBC_INCLUDE)       $(LITEOS_LIBM_INCLUDE) \
                              $(LITEOS_ZLIB_INCLUDE)       $(LITEOS_COMPILER_GCC_INCLUDE)

LOSCFG_TOOLS_DEBUG_INCLUDE := $(LITEOS_SHELL_INCLUDE)      $(LITEOS_UART_INCLUDE) \
                              $(LITEOS_TELNET_INCLUDE)

ifneq ($(LOSCFG_COMPILER_XTENSA_32), y)
FP = -fno-omit-frame-pointer
endif

LITEOS_COPTS_BASE  := -fno-pic -fno-builtin -nostdinc -nostdlib $(WARNING_AS_ERROR) $(LITEOS_SSP)
LITEOS_COPTS_EXTRA := -std=c99 -Wpointer-arith -ffunction-sections -fdata-sections -fno-exceptions $(FP)

ifneq ($(LOSCFG_COMPILER_XTENSA_32), y)
LITEOS_COPTS_BASE  += -fno-aggressive-loop-optimizations
LITEOS_COPTS_EXTRA += -Winvalid-pch -Wstrict-prototypes
endif

ifeq ($(LOSCFG_COMPILER_ARM_NONE_EABI), y)
LITEOS_COPTS_EXTRA += -Wno-unused-value -Wno-unused-function
endif

# auto added the header file LITEOS_PLATFORM_MENUCONFIG_H in all files
LITEOS_PLATFORM_INCLUDE += -include $(LITEOS_PLATFORM_MENUCONFIG_H)
LITEOS_CXXINCLUDE += -include $(LITEOS_PLATFORM_MENUCONFIG_H)

ifneq ($(LOSCFG_COMPILER_XTENSA_32), y)
ifneq ($(LOSCFG_ARCH_ARM_AARCH64), y)
LITEOS_COPTS_BASE += -mno-unaligned-access
LITEOS_COPTS_EXTRA += -mthumb-interwork
endif
endif

#LITEOS_COPTS_EXTRA += -fno-short-enums

ifeq ($(LOSCFG_THUMB), y)
LITEOS_COPTS_EXTRA_INTERWORK := $(LITEOS_COPTS_EXTRA) -mthumb
LITEOS_CMACRO     += -DLOSCFG_INTERWORK_THUMB
else
LITEOS_COPTS_EXTRA_INTERWORK := $(LITEOS_COPTS_EXTRA)
#-fno-inline
endif

ifeq ($(LOSCFG_LLTREPORT) ,y)
# -fprofile-arcs may introduce false warnings on 'maybe-uninitialized'
LITEOS_GCOV_OPTS := -fprofile-arcs -ftest-coverage -Wno-maybe-uninitialized
LITEOS_BASELIB += -lgcov
endif
LITEOS_LD_OPTS += -nostartfiles -static --gc-sections

# determine libgcc.a for fpu, use thumb as default
ifeq ($(LOSCFG_ARCH_ARM_CORTEX_M), y)
ifeq ($(LOSCFG_ARCH_FPU_DISABLE), y)
GCCLIBA := $(LITEOS_COMPILER_GCCLIB_PATH)/thumb/v7e-m+fp/softfp
else
GCCLIBA := $(LITEOS_COMPILER_GCCLIB_PATH)/thumb/v7e-m+fp/hard
endif

LITEOS_LD_PATH += -L$(GCCLIBA)
endif

LITEOS_LD_OPTS += $(LITEOS_DYNLOADOPTS)

LITEOS_LD_PATH += -L$(LITEOS_SCRIPTPATH)/ld -L$(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM) -L$(OUT)/lib -L$(LITEOS_LIB_BIGODIR) -L$(LITEOSTOPDIR)/tools/build
LITEOS_LD_PATH += -L$(LITEOS_COMPILER_GCCLIB_PATH) -L$(LITEOS_COMPILER_CXXLIB_PATH)

ifeq ($(LOSCFG_VENDOR) ,y)
LITEOS_LD_PATH +=  -L$(OUT)/lib/rdk -L$(OUT)/lib/sdk \
                   -L$(OUT)/lib/main_server
endif

ifeq ($(LOSCFG_COMPILER_ARM_NONE_EABI), y)
LITEOS_LD_SCRIPT := -T$(LITEOSTOPDIR)/targets/$(LITEOS_PLATFORM)/board.ld
else
LITEOS_LD_SCRIPT := -T$(LITEOSTOPDIR)/liteos.ld
endif

# temporary
LITEOS_PLATFORM_INCLUDE += \
        -I $(LITEOSTOPDIR)/kernel/base/include
LITEOS_CXXINCLUDE += \
        $(LITEOS_NET_INCLUDE) \
        -I $(LITEOSTOPDIR)/kernel/base/include \
        -I $(LITEOSTOPDIR)/compat/posix/include \
        -I $(LITEOSTOPDIR)/lib/libc/include \
        -I $(LITEOSTOPDIR)/fs/include \
        -I $(LITEOSTOPDIR)/kernel/include \
        $(LITEOS_LIBC_INCLUDE)

LITEOS_COPTS_NODEBUG    := $(LITEOS_NODEBUG) $(LITEOS_COPTS_BASE) $(LITEOS_COPTS_EXTRA)
LITEOS_COPTS_INTERWORK  := $(LITEOS_INTERWORK) $(LITEOS_COPTS_BASE) $(LITEOS_COPTS_EXTRA_INTERWORK)
LITEOS_BASE_INCLUDE := $(LITEOS_KERNEL_INCLUDE) $(LITEOS_PLATFORM_INCLUDE) \
                       $(LITEOS_LIB_INCLUDE) $(LITEOS_FS_INCLUDE) \
                       $(LITEOS_EXTKERNEL_INCLUDE) \
                       $(LITEOS_COMPAT_INCLUDE) $(LITEOS_DRIVERS_INCLUDE) \
                       $(LOSCFG_TOOLS_DEBUG_INCLUDE) $(LITEOS_NET_INCLUDE)
LITEOS_CFLAGS_INTERWORK := $(LITEOS_COPTS_INTERWORK) $(LITEOS_CMACRO) \
                           $(LITEOS_CMACRO_TEST)     $(LITEOS_IMAGE_MACRO) \
                           $(LITEOS_BASE_INCLUDE)
LITEOS_CFLAGS_NODEBUG := $(LITEOS_COPTS_NODEBUG) $(LITEOS_CMACRO) \
                         $(LITEOS_CMACRO_TEST)   $(LITEOS_IMAGE_MACRO) \
                         TEOS_LD_SCRIPT$(LITEOS_BASE_INCLUDE)
