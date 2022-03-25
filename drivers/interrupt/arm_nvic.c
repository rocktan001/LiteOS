/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2018. All rights reserved.
 * Description: NVIC(Nested Vectored Interrupt Controller) for Cortex-M.
 * Author: Huawei LiteOS Team
 * Create: 2013-01-01
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

#include "nvic.h"
#include "los_hwi_pri.h"
#include "los_task_pri.h"

#ifdef LOSCFG_PLATFORM_STM32L073_NUCLEO
#include "stm32l0xx_hal.h"
#elif defined (LOSCFG_PLATFORM_STM32F072_Nucleo)
#include "stm32f0xx_hal.h"
#endif

#ifdef LOSCFG_PLATFORM_STM32F767_FIRE
// #include "debug_pc.h"
#include "led.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC UINT32 g_curIrqNum = 0;
UINT32 g_interruptTimer = 0;
LITE_OS_SEC_BSS HwiHandleInfo g_hwiForm[LOSCFG_PLATFORM_HWI_LIMIT] = { 0 };
#if 0 //
LITE_OS_SEC_DATA_VEC HWI_PROC_FUNC g_hwiVec[LOSCFG_PLATFORM_HWI_LIMIT] = {
    (HWI_PROC_FUNC)0,             /* [0] Top of Stack */
    (HWI_PROC_FUNC)Reset_Handler, /* [1] reset */
    (HWI_PROC_FUNC)IrqEntryV7M,   /* [2] NMI Handler */
    (HWI_PROC_FUNC)IrqEntryV7M,   /* [3] Hard Fault Handler */
    (HWI_PROC_FUNC)IrqEntryV7M,   /* [4] MPU Fault Handler */
    (HWI_PROC_FUNC)IrqEntryV7M,   /* [5] Bus Fault Handler */
    (HWI_PROC_FUNC)IrqEntryV7M,   /* [6] Usage Fault Handler */
    (HWI_PROC_FUNC)0,             /* [7] Reserved */
    (HWI_PROC_FUNC)0,             /* [8] Reserved */
    (HWI_PROC_FUNC)0,             /* [9] Reserved */
    (HWI_PROC_FUNC)0,             /* [10] Reserved */
    (HWI_PROC_FUNC)IrqEntryV7M,   /* [11] SVCall Handler */
    (HWI_PROC_FUNC)IrqEntryV7M,   /* [12] Debug Monitor Handler */
    (HWI_PROC_FUNC)0,             /* [13] Reserved */
    (HWI_PROC_FUNC)osPendSV,      /* [14] PendSV Handler */
    (HWI_PROC_FUNC)IrqEntryV7M,   /* [15] SysTick Handler */
};
#endif
#if 1 //2022-03-25 tanzhongqiang 用来测试中断调用时，之前的PC 
LITE_OS_SEC_DATA_VEC HWI_PROC_FUNC g_hwiVec[LOSCFG_PLATFORM_HWI_LIMIT] = {
    (HWI_PROC_FUNC)0,             /* [0] Top of Stack */
    (HWI_PROC_FUNC)Reset_Handler, /* [1] reset */
    (HWI_PROC_FUNC)IrqEntryV7M_Handler,   /* [2] NMI Handler */
    (HWI_PROC_FUNC)IrqEntryV7M_Handler,   /* [3] Hard Fault Handler */
    (HWI_PROC_FUNC)IrqEntryV7M_Handler,   /* [4] MPU Fault Handler */
    (HWI_PROC_FUNC)IrqEntryV7M_Handler,   /* [5] Bus Fault Handler */
    (HWI_PROC_FUNC)IrqEntryV7M_Handler,   /* [6] Usage Fault Handler */
    (HWI_PROC_FUNC)0,             /* [7] Reserved */
    (HWI_PROC_FUNC)0,             /* [8] Reserved */
    (HWI_PROC_FUNC)0,             /* [9] Reserved */
    (HWI_PROC_FUNC)0,             /* [10] Reserved */
    (HWI_PROC_FUNC)IrqEntryV7M_Handler,   /* [11] SVCall Handler */
    (HWI_PROC_FUNC)IrqEntryV7M_Handler,   /* [12] Debug Monitor Handler */
    (HWI_PROC_FUNC)0,             /* [13] Reserved */
    (HWI_PROC_FUNC)osPendSV,      /* [14] PendSV Handler */
    (HWI_PROC_FUNC)IrqEntryV7M_Handler,   /* [15] SysTick Handler */
};
#endif
LITE_OS_SEC_TEXT_MINOR VOID IrqEntryV7M(VOID)
{
#ifdef LOSCFG_PLATFORM_STM32F767_FIRE
        // Fire_LED_BLUE_ON(1);
    // Fire_DEBUG_GPIOB6(1);
    // DEBUG_INT_PC
#endif    
    g_curIrqNum = __get_IPSR();
    OsIntHandle(g_curIrqNum, &g_hwiForm[g_curIrqNum]);

    if (OsTaskProcSignal() != 0) {
        OsSchedPreempt();
    }
#ifdef LOSCFG_PLATFORM_STM32F767_FIRE    
   // Fire_DEBUG_GPIOB6(0);
    // Fire_LED_BLUE_ON(0);
#endif  
}

UINT32 ArchIrqUnmask(UINT32 hwiNum)
{
    UINT32 intSave;

    if (!HWI_NUM_VALID(hwiNum)) {
        return LOS_ERRNO_HWI_NUM_INVALID;
    }

    hwiNum -= OS_SYS_VECTOR_CNT;
    intSave = LOS_IntLock();
    NVIC_EnableIRQ((IRQn_Type)hwiNum);
    LOS_IntRestore(intSave);
    return LOS_OK;
}

UINT32 HalIrqSetPriority(UINT32 hwiNum, UINT8 priority)
{
    UINT32 intSave;

    if (!HWI_NUM_VALID(hwiNum)) {
        return LOS_ERRNO_HWI_NUM_INVALID;
    }

    if (!HWI_PRI_VALID(priority)) {
        return OS_ERRNO_HWI_PRIO_INVALID;
    }

    hwiNum -= OS_SYS_VECTOR_CNT;
    intSave = LOS_IntLock();
    NVIC_SetPriority((IRQn_Type)hwiNum, priority);
    LOS_IntRestore(intSave);

    return LOS_OK;
}

UINT32 ArchIrqMask(HWI_HANDLE_T hwiNum)
{
    UINT32 intSave;

    if (!HWI_NUM_VALID(hwiNum)) {
        return LOS_ERRNO_HWI_NUM_INVALID;
    }

    hwiNum -= OS_SYS_VECTOR_CNT;
    intSave = LOS_IntLock();
    NVIC_DisableIRQ((IRQn_Type)hwiNum);
    LOS_IntRestore(intSave);
    return LOS_OK;
}

UINT32 ArchIrqPending(UINT32 hwiNum)
{
    UINT32 intSave;

    if (!HWI_NUM_VALID(hwiNum)) {
        return LOS_ERRNO_HWI_NUM_INVALID;
    }

    hwiNum -= OS_SYS_VECTOR_CNT;
    intSave = LOS_IntLock();
    NVIC_SetPendingIRQ((IRQn_Type)hwiNum);
    LOS_IntRestore(intSave);
    return LOS_OK;
}

UINT32 ArchIrqClear(UINT32 hwiNum)
{
    if (!HWI_NUM_VALID(hwiNum)) {
        return LOS_ERRNO_HWI_NUM_INVALID;
    }

    hwiNum -= OS_SYS_VECTOR_CNT;
    NVIC_ClearPendingIRQ((IRQn_Type)hwiNum);
    return LOS_OK;
}

UINT32 HalCurIrqGet(VOID)
{
    g_curIrqNum = __get_IPSR();
    return g_curIrqNum;
}

CHAR *HalIrqVersion(VOID)
{
    return "NVIC";
}

HwiHandleInfo *ArchIrqGetHandleForm(HWI_HANDLE_T hwiNum)
{
    if (!HWI_NUM_VALID(hwiNum)) {
        return NULL;
    }

    return &g_hwiForm[hwiNum];
}

STATIC const HwiControllerOps g_nvicOps = {
    .triggerIrq     = ArchIrqPending,
    .enableIrq      = ArchIrqUnmask,
    .disableIrq     = ArchIrqMask,
    .setIrqPriority = HalIrqSetPriority,
    .getCurIrqNum   = HalCurIrqGet,
    .getIrqVersion  = HalIrqVersion,
    .getHandleForm  = ArchIrqGetHandleForm,
    .clearIrq       = ArchIrqClear,
};

VOID ArchIrqInit(VOID)
{
    UINT32 i;

    for (i = OS_SYS_VECTOR_CNT; i < LOSCFG_PLATFORM_HWI_LIMIT; i++) {
        g_hwiVec[i] = (HWI_PROC_FUNC)IrqEntryV7M;
    }
#if (__CORTEX_M == 0x0U)  /* only for Cortex-M0 */
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    /* Remap SRAM at 0x00000000 */
    __HAL_SYSCFG_REMAPMEMORY_SRAM();
#else
    /* Interrupt vector table location */
    SCB->VTOR = (UINT32)g_hwiVec;
#endif
#if (__CORTEX_M >= 0x03U) /* only for Cortex-M3 and above */
    NVIC_SetPriorityGrouping(OS_NVIC_AIRCR_PRIGROUP);
#endif

    /* register interrupt controller's operations */
    OsHwiControllerReg(&g_nvicOps);
    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
