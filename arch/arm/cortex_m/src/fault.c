/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Cortex-M Exception Handler
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

#include "arch/exception.h"
#ifdef LOSCFG_LIB_LIBC
#include "string.h"
#endif
#include "los_task_pri.h"
#include "los_hwi_pri.h"
#include "securec.h"
#include "los_printf_pri.h"
#include "nvic.h"

#ifdef LOSCFG_KERNEL_TRACE
#include "los_trace_pri.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define USGFAULT (1U << 18)
#define BUSFAULT (1U << 17)
#define MEMFAULT (1U << 16)
#define DIV0FAULT (1U << 4)
#define HARD_FAULT_IRQN (-13)
#define MASK_16_BIT 16

UINT32 g_curNestCount = 0;
ExcInfo g_excInfo;
UINT8 g_excTbl[FAULT_STATUS_REG_BIT] = {
    0, 0, 0, 0, 0, 0, OS_EXC_UF_DIVBYZERO, OS_EXC_UF_UNALIGNED,
    0, 0, 0, 0, OS_EXC_UF_NOCP, OS_EXC_UF_INVPC, OS_EXC_UF_INVSTATE, OS_EXC_UF_UNDEFINSTR,
    0, 0, 0, OS_EXC_BF_STKERR, OS_EXC_BF_UNSTKERR, OS_EXC_BF_IMPRECISERR, OS_EXC_BF_PRECISERR, OS_EXC_BF_IBUSERR,
    0, 0, 0, OS_EXC_MF_MSTKERR, OS_EXC_MF_MUNSTKERR, 0, OS_EXC_MF_DACCVIOL, OS_EXC_MF_IACCVIOL
};
ExcInfoArray g_excArray[OS_EXC_TYPE_MAX - 1];
STATIC const CHAR *g_phaseName[] = {
    "fault in init",
    "fault in task",
    "fault in interrupt",
};

LITE_OS_SEC_TEXT_INIT VOID OsExcInfoDisplay(const ExcInfo *exc)
{
    PrintExcInfo("Phase      = %s\n"
                 "Type       = 0x%x\n"
                 "FaultAddr  = 0x%x\n"
                 "intNumOrTaskId    = 0x%x\n"
                 "R0         = 0x%x\n"
                 "R1         = 0x%x\n"
                 "R2         = 0x%x\n"
                 "R3         = 0x%x\n"
                 "R4         = 0x%x\n"
                 "R5         = 0x%x\n"
                 "R6         = 0x%x\n"
                 "R7         = 0x%x\n"
                 "R8         = 0x%x\n"
                 "R9         = 0x%x\n"
                 "R10        = 0x%x\n"
                 "R11        = 0x%x\n"
                 "R12        = 0x%x\n"
                 "PriMask    = 0x%x\n"
                 "SP         = 0x%x\n"
                 "LR         = 0x%x\n"
                 "PC         = 0x%x\n"
                 "xPSR       = 0x%x\n",
                 g_phaseName[exc->phase], exc->type, exc->faultAddr, exc->intNumOrTaskId, exc->context->R0,
                 exc->context->R1, exc->context->R2, exc->context->R3, exc->context->R4, exc->context->R5,
                 exc->context->R6, exc->context->R7, exc->context->R8, exc->context->R9,
                 exc->context->R10, exc->context->R11, exc->context->R12, exc->context->PriMask,
                 exc->context->SP, exc->context->LR, exc->context->PC, exc->context->xPSR);
    return;
}

LITE_OS_SEC_TEXT_INIT VOID OsExcHandleEntry(UINT32 excType, UINT32 faultAddr, UINT32 pid,
                                            const ExcContext *excBufAddr)
{
    UINT16 tmpFlag = (excType >> MASK_16_BIT) & OS_NULL_SHORT; /* 2:in intrrupt,1:faul addr valid */
    g_curNestCount++;
    g_excInfo.nestCnt = (UINT16)g_curNestCount;

    g_excInfo.type = excType & OS_NULL_SHORT;

    if (tmpFlag & OS_EXC_FLAG_FAULTADDR_VALID) {
        g_excInfo.faultAddr = faultAddr;
    } else {
        g_excInfo.faultAddr = OS_EXC_IMPRECISE_ACCESS_ADDR;
    }

    if (ArchCurrTaskGet() != NULL) {
        if (tmpFlag & OS_EXC_FLAG_IN_HWI) {
            g_excInfo.phase = OS_EXC_IN_HWI;
            g_excInfo.intNumOrTaskId = pid;
        } else {
            g_excInfo.phase = OS_EXC_IN_TASK;
            g_excInfo.intNumOrTaskId = ((LosTaskCB *)ArchCurrTaskGet())->taskId;
        }
    } else {
        g_excInfo.phase = OS_EXC_IN_INIT;
        g_excInfo.intNumOrTaskId = OS_NULL_INT;
    }

    if (excType & OS_EXC_FLAG_NO_FLOAT) {
        g_excInfo.context = (ExcContext *)((CHAR *)excBufAddr - LOS_OFF_SET_OF(ExcContext, R4));
    } else {
        g_excInfo.context = (ExcContext *)excBufAddr;
    }

    OsExcInfoDisplay((const ExcInfo *)&g_excInfo);
#ifdef LOSCFG_KERNEL_TRACE
    OsTraceRecordDump(FALSE);
#endif
    while (1) { }
}

LITE_OS_SEC_TEXT_INIT VOID ArchExcInit(VOID)
{
    g_hwiVec[HARD_FAULT_IRQN + OS_SYS_VECTOR_CNT] = OsExcHardFault;
    g_hwiVec[NonMaskableInt_IRQn + OS_SYS_VECTOR_CNT] = OsExcNMI;
    g_hwiVec[MemoryManagement_IRQn + OS_SYS_VECTOR_CNT] = OsExcMemFault;
    g_hwiVec[BusFault_IRQn + OS_SYS_VECTOR_CNT] = OsExcBusFault;
    g_hwiVec[UsageFault_IRQn + OS_SYS_VECTOR_CNT] = OsExcUsageFault;
    g_hwiVec[SVCall_IRQn + OS_SYS_VECTOR_CNT] = OsExcSvcCall;
    /* Enable USGFAULT, BUSFAULT, MEMFAULT */
    *(volatile UINT32 *)OS_NVIC_SHCSR |= (USGFAULT | BUSFAULT | MEMFAULT);
    /* Enable DIV 0 and unaligned exception */
    *(volatile UINT32 *)OS_NVIC_CCR |= DIV0FAULT;
}

VOID ArchBackTrace(VOID)
{
    return;
}

VOID ArchBackTraceWithSp(const VOID *stackPointer)
{
    (VOID)stackPointer;
    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
