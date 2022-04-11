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
#include "los_task_pri.h"
#include "los_hwi_pri.h"
#include "securec.h"
#include "los_printf_pri.h"
#include "los_memory_pri.h"
#include "nvic.h"

#ifdef LOSCFG_KERNEL_TRACE
#include "los_trace_pri.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define USGFAULT               (1U << 18)
#define BUSFAULT               (1U << 17)
#define MEMFAULT               (1U << 16)
#define DIV0FAULT              (1U << 4)
#define HARD_FAULT_IRQN        (-13)
#define MASK_16_BIT            16
#define OFFSET_OF_PSP          40 /* 10 registers */

#ifdef LOSCFG_BACKTRACE
#define OS_MAX_BACKTRACE       15
#define THUM_OFFSET            2
#define STACK_OFFSET           4
#define MASK_OFFSET            2
#define HIGH_8_OFFSET          8
#define BL_CMD_OFFSET          4
#define BLX_CMD_OFFSET         2
#define PUSH_MASK_WITH_LR      0xb5
#define PUSH_MASK              0xb4
#define OFFSET_ADDRESS_MASK    0x7FF07FF
#define LOW_11_BITS_MASK       0x7FF
#define HIGH_11_BITS_MASK      0x7FF0000
#define HIGH_8_BITS_MASK       0xFF00
#define SIGN_BIT_MASK          0x400000
#define HIGH_OFFSET_NUMBER     12
#define LOW_OFFSET_NUMBER      1

#define BL_INS                 0xF000F000
#define BLX_INX                0x4700

extern CHAR _estack;
static const int g_textStart = (const int)&__text_start;
static const int g_textEnd = (const int)&__text_end;
static const int g_estack = (const int)&_estack;
#endif

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

STATIC VOID OsExcSysInfo(VOID)
{
    LosTaskCB *runTask = OsCurrTaskGet();

    if (runTask != NULL) {
        PrintExcInfo("TaskName = %s\n"
                     "TaskId = %u\n"
                     "Task stackSize = %u\n"
                     "System mem addr = 0x%x\n",
                     runTask->taskName,
                     runTask->taskId,
                     runTask->stackSize,
                     m_aucSysMem0);
    }
}

LITE_OS_SEC_TEXT_INIT VOID OsExcInfoDisplay(const ExcInfo *exc, const ExcContext *excBufAddr)
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
                 g_phaseName[exc->phase], exc->type, exc->faultAddr, exc->intNumOrTaskId, excBufAddr->R0,
                 excBufAddr->R1, excBufAddr->R2, excBufAddr->R3, excBufAddr->R4, excBufAddr->R5,
                 excBufAddr->R6, excBufAddr->R7, excBufAddr->R8, excBufAddr->R9,
                 excBufAddr->R10, excBufAddr->R11, excBufAddr->R12, excBufAddr->PriMask,
                 excBufAddr->SP, excBufAddr->LR, excBufAddr->PC, excBufAddr->xPSR);
}

LITE_OS_SEC_TEXT_INIT VOID OsExcHandleEntry(UINT32 excType, UINT32 faultAddr, UINT32 pid,
                                            const ExcContext *excBufAddr)
{
    ExcContext *BufAddr = NULL;
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
            OsExcSysInfo();
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

    if (g_excInfo.phase == OS_EXC_IN_TASK) {
        BufAddr =  (ExcContext *)(ArchGetPsp() - OFFSET_OF_PSP);
    } else {
        BufAddr = g_excInfo.context;
    }

    OsExcInfoDisplay((const ExcInfo *)&g_excInfo, BufAddr);

#ifdef LOSCFG_BACKTRACE
    ArchBackTraceWithSp(BufAddr);
#endif

#ifdef LOSCFG_KERNEL_TRACE
    OsTraceRecordDump(FALSE);
#endif
    while (1) { }
}

#ifdef LOSCFG_BACKTRACE
/* this function is used to validate sp or validate the checking range start and end. */
STATIC INLINE BOOL IsValidSP(UINTPTR regSP, UINTPTR start, UINTPTR end)
{
    return (regSP >= start) && (regSP < end);
}

STATIC INLINE BOOL FindSuitableStack(UINTPTR *regSP, UINTPTR *start, UINTPTR *end)
{
    UINT32 index, topOfStack, stackBottom;
    BOOL found = FALSE;
    LosTaskCB *taskCB = NULL;

    /* Search in the task stacks */
    for (index = 0; index < g_taskMaxNum; index++) {
        taskCB = OS_TCB_FROM_TID(index);
        if (taskCB->taskStatus & OS_TASK_STATUS_UNUSED) {
            continue;
        }
        topOfStack = taskCB->topOfStack;
        stackBottom = taskCB->topOfStack + taskCB->stackSize;

        if (IsValidSP(*regSP, topOfStack, stackBottom)) {
            found = TRUE;
            goto FOUND;
        }
    }

FOUND:
    if (found == TRUE) {
        *start = topOfStack;
        *end = stackBottom;
    } else if (*regSP < g_estack) {
        *start = *regSP;
        *end = g_estack;
        found = TRUE;
    }

    return found;
}

UINTPTR LoopUntilEntry(UINTPTR addr)
{
    while (addr > (UINTPTR)g_textStart) {
        if (((*((UINT16 *)addr) >> HIGH_8_OFFSET) == PUSH_MASK_WITH_LR) ||
            ((*((UINT16 *)addr) >> HIGH_8_OFFSET) == PUSH_MASK)) {
            break;
        }
        addr -= THUM_OFFSET;
    }

    return addr;
}

UINTPTR CalculateBLTargetAddress(UINTPTR bl)
{
    UINTPTR target;
    UINT32 off0, off1, off;

    if (*(UINT16 *)bl & SIGN_BIT_MASK) {
        off1 = *(UINT16 *)bl & LOW_11_BITS_MASK;
        off0 = *(UINT16 *)(bl + MASK_OFFSET) & LOW_11_BITS_MASK;
    } else {
        off0 = *(UINT16 *)bl & LOW_11_BITS_MASK;
        off1 = *(UINT16 *)(bl + MASK_OFFSET) & LOW_11_BITS_MASK;
    }
    off = (off0 << HIGH_OFFSET_NUMBER) + (off1 << LOW_OFFSET_NUMBER);
    if (off & SIGN_BIT_MASK) {
        target = bl + BL_CMD_OFFSET - ((~(off - 1)) & 0x7FFFFF); // 0x7FFFFF : offset mask
    } else {
        target = bl + BL_CMD_OFFSET + off;
    }

    return target;
}

UINTPTR CalculateTargetAddress(UINTPTR bl)
{
    UINTPTR target;
    STATIC UINTPTR tmpBL = 0;

    if ((((*(UINT16 *)(bl - BLX_CMD_OFFSET)) & HIGH_8_BITS_MASK) == BLX_INX)) {
        if (tmpBL != 0) {
            target = LoopUntilEntry(tmpBL);
            tmpBL = bl - BLX_CMD_OFFSET;
            return target;
        }
        tmpBL = bl - BLX_CMD_OFFSET;
        return LoopUntilEntry(tmpBL);
    } else if ((*(UINT32 *)(bl - BL_CMD_OFFSET) & BL_INS) == BL_INS) {
        tmpBL = bl - BL_CMD_OFFSET;
        return CalculateBLTargetAddress(tmpBL);
    }

    return 0;
}

VOID BackTraceSub(UINTPTR sp)
{
    UINTPTR stackPointer = sp;
    UINT32 count = 0;
    UINTPTR topOfStack = 0;
    UINTPTR stackBottom = 0;
    STATIC UINTPTR tmpJump = 0;

    if (FindSuitableStack(&stackPointer, &topOfStack, &stackBottom) == FALSE) {
        return;
    }

    while ((stackPointer < stackBottom) && (count < OS_MAX_BACKTRACE)) {
        if ((*(UINT32 *)stackPointer >= (UINT32)g_textStart) &&
            (*(UINT32 *)stackPointer <= (UINT32)g_textEnd) &&
            /**
             * 2022-04-11 tanzhongqiang 堆栈中保存的LR 值，一定是奇数。应该是thumb 指令都是16bit 。
             * 如何判断堆栈中保存是LR 还是函数地址？ 通过判断LR 值 对应上一条指令是否BL,BX 。
             * */
            IS_ALIGNED(*(UINT32 *)stackPointer - 1, THUM_OFFSET)) {
            /* Get the entry address of current function. */
            UINTPTR checkBL = CalculateTargetAddress(*(UINT32 *)stackPointer - 1);
            if ((checkBL == 0) || (checkBL == tmpJump)) {
                stackPointer += STACK_OFFSET;
                continue;
            }
            tmpJump = checkBL;
            count++;
            PrintExcInfo("traceback %u -- lr = 0x%08x -- fp = 0x%08x\n", count, *(UINT32 *)stackPointer - 1, tmpJump);
        }
        stackPointer += STACK_OFFSET;
    }
}

STATIC VOID BackTraceWithSp(UINTPTR sp)
{
    PrintExcInfo("*******backtrace begin*******\n");
    BackTraceSub(sp);
    PrintExcInfo("*******backtrace end*******\n");
}
#endif

VOID ArchBackTrace(VOID)
{
#ifdef LOSCFG_BACKTRACE
    UINTPTR sp = ArchGetSp();
    PrintExcInfo("sp:0x%08x\n", sp);
    BackTraceWithSp(sp);
#endif
}

VOID ArchBackTraceWithSp(const VOID *stackPointer)
{
#ifdef LOSCFG_BACKTRACE
    BackTraceWithSp((UINTPTR)stackPointer);
#else
    (VOID)stackPointer;
#endif
}

LITE_OS_SEC_TEXT_INIT VOID ArchExcInit(VOID)
{
#ifndef LOSCFG_ARCH_CORTEX_M0
#ifndef LOSCFG_ARCH_CORTEX_M0_PLUS
    g_hwiVec[HARD_FAULT_IRQN + OS_SYS_VECTOR_CNT] = OsExcHardFault;
    g_hwiVec[NonMaskableInt_IRQn + OS_SYS_VECTOR_CNT] = OsExcNMI;
    g_hwiVec[MemoryManagement_IRQn + OS_SYS_VECTOR_CNT] = OsExcMemFault;
    g_hwiVec[BusFault_IRQn + OS_SYS_VECTOR_CNT] = OsExcBusFault;
    g_hwiVec[UsageFault_IRQn + OS_SYS_VECTOR_CNT] = OsExcUsageFault;
    g_hwiVec[SVCall_IRQn + OS_SYS_VECTOR_CNT] = OsExcSvcCall;
#else
    g_hwiVec[HARD_FAULT_IRQN + OS_SYS_VECTOR_CNT] = OsExcHardFault;
    g_hwiVec[SVC_IRQn + OS_SYS_VECTOR_CNT] = OsExcSvcCall;
    g_hwiVec[NonMaskableInt_IRQn + OS_SYS_VECTOR_CNT] = OsExcNMI;
#endif
#endif
    /* Enable USGFAULT, BUSFAULT, MEMFAULT */
    *(volatile UINT32 *)OS_NVIC_SHCSR |= (USGFAULT | BUSFAULT | MEMFAULT);
    /* Enable DIV 0 and unaligned exception */
    *(volatile UINT32 *)OS_NVIC_CCR |= DIV0FAULT;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
