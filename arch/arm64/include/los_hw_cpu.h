/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2019. All rights reserved.
 * Description: AArch64 Hw CPU HeadFile
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 * --------------------------------------------------------------------------- */

/**
 * @defgroup los_hw Hardware
 * @ingroup kernel
 */

#ifndef _LOS_HW_CPU_H
#define _LOS_HW_CPU_H

#include "menuconfig.h"
#include "los_hw_arch.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#ifdef LOSCFG_ARCH_SECURE_MONITOR_MODE
#define RUNLVL    12
#define SPSR_ELx  spsr_el3
#define ELR_ELx   elr_el3
#define TPIDR_ELx tpidr_el3
#define ESR_ELx   esr_el3
#define FAR_ELx   far_el3
#else
#define RUNLVL    4
#define SPSR_ELx  spsr_el1
#define ELR_ELx   elr_el1
#define TPIDR_ELx tpidr_el1
#define ESR_ELx   esr_el1
#define FAR_ELx   far_el1
#endif

#ifndef LOSCFG_USED_IN_ASSEMBLY
#define DSB         __asm__ volatile("dsb sy" ::: "memory")
#define DMB         __asm__ volatile("dmb sy" ::: "memory")
#define ISB         __asm__ volatile("isb" ::: "memory")
#define BARRIER     __asm__ volatile("":::"memory")
#define DSB_ISHST   __asm__ volatile("dsb ishst" ::: "memory")
#define DMB_ISHST   __asm__ volatile("dmb ishst" ::: "memory")

/* AARCH64 System Registers */
#define STRINGIFY_1(x)  #x
#define STRINGIFY(x)    STRINGIFY_1(x)

#define AARCH64_SYSREG_READ(reg)                              \
({                                                            \
    UINT64 _val;                                              \
    __asm__ volatile("mrs %0," STRINGIFY(reg) : "=r" (_val)); \
    _val; \
})

#define AARCH64_SYSREG_WRITE(reg, val)                           \
({                                                               \
    __asm__ volatile("msr " STRINGIFY(reg) ", %0" :: "r" (val)); \
    __asm__ volatile("isb" ::: "memory");                        \
})

/*
 *  mpidr register (64bit)
 *       res0  aff3  res1  u  res0  mt  aff2  aff1  aff0
 *  bit 63-40 39-32   31  30 29~25  24 23-16  15-8   7~0
 */
#define MPIDR_U_MASK                    (0x1ULL << 30)
#define MPIDR_MT_MASK                   (0x1ULL << 24)

#define MPIDR_AFF_LEVEL_MASK            0xFFULL
#define MPIDR_AFF_SHIFT(level)          (((1 << (level)) >> 1) << 3)
#define MPIDR_AFF_LEVEL(mpidr, level)   (((mpidr) >> MPIDR_AFF_SHIFT(level)) & MPIDR_AFF_LEVEL_MASK)

/*
 *  midr register (32bit)
 *       implementer variant  arch partnum  rev
 *  bit     31-24    23-20   19~16  15-4    3-0
 */
#define MIDR_REV_MASK                   0xFF
#define MIDR_REV(midr)                  ((midr) & MIDR_REV_MASK)
#define MIDR_PARTNO_SHIFT               0x4
#define MIDR_PARTNO_MASK                (0xFFF << MIDR_PARTNO_SHIFT)
#define MIDR_PARTNO(midr)               (((midr) & MIDR_PARTNO_MASK) >> MIDR_PARTNO_SHIFT)

STATIC INLINE VOID *ArchCurrTaskGet(VOID)
{
    return (VOID *)(UINTPTR)AARCH64_SYSREG_READ(TPIDR_ELx);
}

STATIC INLINE VOID ArchCurrTaskSet(VOID *val)
{
    AARCH64_SYSREG_WRITE(TPIDR_ELx, (UINT64)(UINTPTR)val);
}

STATIC INLINE UINT32 ArchCurrCpuid(VOID)
{
    return 0;
}

STATIC INLINE UINT32 ArchSPGet(VOID)
{
    UINT32 val;
    __asm__ __volatile__("mov %0, sp" : "=r"(val));
    return val;
}

STATIC INLINE UINT64 OsHwIDGet(VOID)
{
    return AARCH64_SYSREG_READ(mpidr_el1);
}

STATIC INLINE UINT32 OsMainIDGet(VOID)
{
    return (UINT32)AARCH64_SYSREG_READ(midr_el1);
}

/* CPU interrupt mask handle implementation */
STATIC INLINE UINT32 ArchIntLock(VOID)
{
    UINT32 intSave;
    __asm__ __volatile__(
        "mrs    %0, daif      \n"
        "msr    daifset, #0xf   "
        : "=r" (intSave)
        :
        : "memory");
    return intSave;
}

STATIC INLINE UINT32 ArchIntUnlock(VOID)
{
    UINT32 intSave;
    __asm__ __volatile__(
        "mrs    %0, daif      \n"
        "msr    daifclr, #3     "
        : "=r"(intSave)
        :
        : "memory");
    return intSave;
}

STATIC INLINE VOID ArchIntRestore(UINT32 intSave)
{
    __asm__ __volatile__(
        "msr    daif, %0        "
        :
        : "r"(intSave)
        : "memory");
}

#define PSR_I_BIT   0x00000080U

STATIC INLINE UINT32 OsIntLocked(VOID)
{
    UINT32 intSave;

    asm volatile(
        "mrs    %0, daif        "
        : "=r" (intSave)
        :
        : "memory");

    return intSave & PSR_I_BIT;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_HW_CPU_H */
