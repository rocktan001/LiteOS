/*
 * Automatically generated C config: don't edit
 */
/*
 * Version Number
 */
#ifndef LOSCFG_MODULE_SWITCH
#define LOSCFG_MODULE_SWITCH

/*
 * Compiler
 */
#define LOSCFG_COMPILER_GCC 1
#undef LOSCFG_COMPILER_HIMIX_32
#undef LOSCFG_COMPILER_HIMIX100_64
#undef LOSCFG_COMPILER_HCC_64
#undef LOSCFG_COMPILER_RISCV
#undef LOSCFG_COMPILER_RISCV_UNKNOWN
#undef LOSCFG_COMPILER_XTENSA_32
#define LOSCFG_COMPILER_ARM_NONE_EABI 1
#undef LOSCFG_COMPILER_OPTIMIZE_NONE
#define LOSCFG_COMPILER_OPTIMIZE_SPEED 1
#undef LOSCFG_COMPILER_OPTIMIZE_SIZE

/*
 * Platform
 */
#define __LOSCFG_PLATFORM__ "STM32F769IDISCOVERY"
#undef LOSCFG_PLATFORM_HI3556V200
#undef LOSCFG_PLATFORM_HI1980_IMU
#undef LOSCFG_PLATFORM_QEMU_VIRT_A53
#undef LOSCFG_PLATFORM_PBX_A9
#undef LOSCFG_PLATFORM_HI3751V900_DSP
#undef LOSCFG_PLATFORM_HI3559DV100_DSP
#undef LOSCFG_PLATFORM_HI3519AV200
#undef LOSCFG_PLATFORM_HI3862_SE
#undef LOSCFG_PLATFORM_HI3516EV200
#define LOSCFG_PLATFORM_STM32F769IDISCOVERY 1
#define LOSCFG_USING_BOARD_LD 1
#undef LOSCFG_PLATFORM_BSP_GIC_V2
#undef LOSCFG_PLATFORM_BSP_GIC_V3
#define LOSCFG_PLATFORM_BSP_NVIC 1
#undef LOSCFG_PLATFORM_BSP_XTENSA_XEA3
#define LOSCFG_ARCH_ARM_AARCH32 1
#define LOSCFG_ARCH_ARM_CORTEX_M 1
#define LOSCFG_ARCH_ARM_V7M 1
#define __LOSCFG_ARCH_ARM_VER__ "armv7-m"
#define LOSCFG_ARCH_FPU_VFP_V5 1
#define LOSCFG_ARCH_FPU_VFP_D16 1
#define __LOSCFG_ARCH_FPU__ "fpv5-sp-d16"
#define LOSCFG_ARCH_CORTEX_M7 1
#define __LOSCFG_ARCH_CPU__ "cortex-m7"

/*
 * Extra Configurations
 */
#undef LOSCFG_ARCH_FPU_DISABLE
#undef LOSCFG_ARCH_INTERRUPT_PREEMPTION
#define LOSCFG_IRQ_USE_STANDALONE_STACK 1

/*
 * Kernel
 */
#undef LOSCFG_KERNEL_SMP

/*
 * Basic Config
 */
#define LOSCFG_SCHED_SQ 1
#undef LOSCFG_SCHED_MQ

/*
 * Task
 */
#define LOSCFG_OBSOLETE_API 1
#undef LOSCFG_LAZY_STACK
#undef LOSCFG_TASK_STATIC_ALLOCATION
#define LOSCFG_BASE_CORE_TSK_LIMIT 16
#define LOSCFG_BASE_CORE_TIMESLICE 1
#define LOSCFG_BASE_CORE_TIMESLICE_TIMEOUT 2
#define LOSCFG_BASE_CORE_USE_MULTI_LIST 1
#undef LOSCFG_BASE_CORE_USE_SINGLE_LIST

/*
 * Memory Management
 */
#undef LOSCFG_KERNEL_MEM_BESTFIT
#define LOSCFG_KERNEL_MEM_BESTFIT_LITTLE 1
#undef LOSCFG_KERNEL_MEM_SLAB_EXTENTION
#define LOSCFG_MEM_TASK_STAT 1
#define LOSCFG_KERNEL_MEMBOX 1
#define LOSCFG_KERNEL_MEMBOX_STATIC 1
#undef LOSCFG_KERNEL_MEMBOX_DYNAMIC

/*
 * Hardware Interrupt
 */
#undef LOSCFG_NO_SHARED_IRQ
#define LOSCFG_PLATFORM_HWI_LIMIT 256
#define LOSCFG_BASE_CORE_SWTMR 1

/*
 * Software Timer Options
 */
#define LOSCFG_BASE_CORE_SWTMR_LIMIT 16
#undef LOSCFG_BASE_CORE_SWTMR_IN_ISR
#define LOSCFG_BASE_IPC_QUEUE 1

/*
 * Queue Options
 */
#undef LOSCFG_QUEUE_STATIC_ALLOCATION
#define LOSCFG_BASE_IPC_QUEUE_LIMIT 10
#define LOSCFG_BASE_IPC_EVENT 1

/*
 * Event Options
 */
#define LOSCFG_BASE_IPC_EVENT_LIMIT 10
#define LOSCFG_BASE_IPC_MUX 1

/*
 * Mutex Options
 */
#define LOSCFG_MUTEX_WAIT_PRIORITY 1
#define LOSCFG_BASE_IPC_MUX_LIMIT 20
#define LOSCFG_BASE_IPC_SEM 1

/*
 * Sem Options
 */
#define LOSCFG_BASE_IPC_SEM_LIMIT 20
#define LOSCFG_KERNEL_EXTKERNEL 1
#define LOSCFG_KERNEL_CPPSUPPORT 1
#undef LOSCFG_KERNEL_MPU
#define LOSCFG_KERNEL_CPUP 1
#define LOSCFG_CPUP_INCLUDE_IRQ 1
#undef LOSCFG_KERNEL_DYNLOAD
#define LOSCFG_KERNEL_TICKLESS 1
#undef LOSCFG_KERNEL_TRACE

/*
 * Lib
 */
#define LOSCFG_LIB_LIBC 1
#define LOSCFG_COMPAT_POSIX 1
#define LOSCFG_LIB_LIBM 1
#define LOSCFG_LIB_STDIO 1
#define LOSCFG_LIB_ZLIB 1

/*
 * Compat
 */
#define LOSCFG_COMPAT_CMSIS 1
#undef LOSCFG_COMPAT_LINUX

/*
 * FileSystem
 */
#undef LOSCFG_FS_VFS

/*
 * Net
 */
#undef LOSCFG_NET_LWIP_SACK

/*
 * Debug
 */
#undef LOSCFG_COMPILE_DEBUG
#define LOSCFG_PLATFORM_ADAPT 1
#undef LOSCFG_COREDUMP
#undef LOSCFG_GDB
#undef LOSCFG_ENABLE_MAGICKEY
#undef LOSCFG_THUMB
#undef LOSCFG_DEBUG_VERSION
#undef LOSCFG_DRIVERS_UART
#define LOSCFG_PLATFORM_UART_WITHOUT_VFS 1
#undef LOSCFG_PLATFORM_NO_UART
#define LOSCFG_SERIAL_OUTPUT_ENABLE 1

/*
 * TestSuite or AppInit
 */
#define LOSCFG_PLATFORM_OSAPPINIT 1
#undef LOSCFG_TEST
#undef LOSCFG_TESTSUIT_SHELL
#undef LOSCFG_TEST_MANUAL_TEST
#undef LOSCFG_FUZZ_DT

/*
 * Driver
 */
#undef LOSCFG_DRIVERS

/*
 * Stack Smashing Protector (SSP) Compiler Feature
 */
#undef LOSCFG_CC_NO_STACKPROTECTOR
#undef LOSCFG_CC_STACKPROTECTOR
#define LOSCFG_CC_STACKPROTECTOR_STRONG 1
#undef LOSCFG_CC_STACKPROTECTOR_ALL

#endif
