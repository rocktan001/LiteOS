/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Xtensa Lx6 Exception Handler Implementation
 * Author: Huawei LiteOS Team
 * Create: 2021-09-07
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
#include "los_typedef.h"
#include "los_printf_pri.h"
#include "xtensa_lx6.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

ExcInfo g_excInfo = {0};

UINT32 HwiNumValid(UINT32 num)
{
    return (num >= OS_SYS_VECTOR_CNT) && (num <= OS_VECTOR_CNT);
}

VOID ArchExcInit(VOID)
{
}
/* *
 * @ingroup los_hwi
 * Determine if the interrupt is locked
 */
STATIC INLINE UINT32 HalIntLocked(VOID)
{
    UINT32 intSave;
    __asm__ volatile("rsr %0, ps " : "=r"(intSave) : : "memory");

    return (intSave & SPREG_PS_DI_MASK);
}

#if (LOSCFG_KERNEL_PRINTF != 0)
STATIC VOID OsExcTypeInfo(const ExcInfo *excInfo)
{
    CHAR *phaseStr[] = {"exc in init", "exc in task", "exc in hwi"};

    PrintExcInfo("Type      = %d\n"
                 "ThrdPid   = %d\n"
                 "Phase     = %s\n"
                 "FaultAddr = 0x%x\n",
                 excInfo->type,
                 excInfo->thrdPid,
                 phaseStr[excInfo->phase], 
                 excInfo->faultAddr);
}

STATIC VOID OsExcCurTaskInfo(const ExcInfo *excInfo)
{
    PrintExcInfo("Current task info:\n");
    if (excInfo->phase == OS_EXC_IN_TASK) {
        LosTaskCB *taskCB = OS_TCB_FROM_TID(LOS_CurTaskIDGet());
        PrintExcInfo("Task name = %s\n"
                     "Task Id = %d\n"
                     "Task stackSize = 0x%x\n"
                     "Task stackPointer = 0x%x\n"
                     "Task topOfStack = 0x%x\n",
                     taskCB->taskName,
                     taskCB->taskId,
                     taskCB->stackSize,
                     (UINT32)taskCB->stackPointer,
                     taskCB->topOfStack);
    } else if (excInfo->phase == OS_EXC_IN_HWI) {
        PrintExcInfo("Exception occur in interrupt phase!\n");
    } else {
        PrintExcInfo("Exception occur in system init phase!\n");
    }
}

STATIC VOID OsExcRegInfo(const ExcInfo *excInfo)
{
    INT32 index;
    PrintExcInfo("Exception reg dump:\n"
                 "sar          = 0x%x\n"
                 "excCause     = 0x%x\n"
                 "excVaddr     = 0x%x\n"
                 "lbeg         = 0x%x\n"
                 "lend         = 0x%x\n"
                 "lcount       = 0x%x\n"
                 "pc           = 0x%x\n"
                 "ps           = 0x%x\n",
                 excInfo->context->sar, excInfo->context->excCause, excInfo->context->excVaddr,
                 excInfo->context->lbeg, excInfo->context->lend, excInfo->context->lcount,
                 excInfo->context->pc, excInfo->context->ps);
    for (index = 0; index < XTENSA_LOGREG_NUM; index++) {
        PrintExcInfo("regA%d        = 0x%x\n", index, excInfo->context->regA[index]);
   }
}

STATIC VOID OsExcBackTraceInfo(const ExcInfo *excInfo)
{
    UINT32 LR[LOSCFG_BACKTRACE_DEPTH] = {0};
    UINT32 index;

    OsBackTraceHookCall(LR, LOSCFG_BACKTRACE_DEPTH, 0, excInfo->context->regA[1]);

    PrintExcInfo("----- backtrace begin -----\n");
    for (index = 0; index < LOSCFG_BACKTRACE_DEPTH; index++) {
        if (LR[index] == 0) {
            break;
        }
        PrintExcInfo("backtrace %d -- lr = 0x%x\n", index, LR[index]);
    }
    PrintExcInfo("----- backtrace end -----\n");
}

STATIC VOID OsExcMemPoolCheckInfo(VOID)
{
    PrintExcInfo("\r\nmemory pools check:\n");
#if (LOSCFG_PLATFORM_EXC == 1)
    MemInfoCB memExcInfo[OS_SYS_MEM_NUM];
    UINT32 errCnt;
    UINT32 i;

    (VOID)memset_s(memExcInfo, sizeof(memExcInfo), 0, sizeof(memExcInfo));

    errCnt = OsMemExcInfoGet(OS_SYS_MEM_NUM, memExcInfo);
    if (errCnt < OS_SYS_MEM_NUM) {
        errCnt += OsMemboxExcInfoGet(OS_SYS_MEM_NUM - errCnt, memExcInfo + errCnt);
    }

    if (errCnt == 0) {
        PrintExcInfo("all memory pool check passed!\n");
        return;
    }

    for (i = 0; i < errCnt; i++) {
        PrintExcInfo("pool num    = %d\n", i);
        PrintExcInfo("pool type   = %d\n", memExcInfo[i].type);
        PrintExcInfo("pool addr   = 0x%x\n", memExcInfo[i].startAddr);
        PrintExcInfo("pool size   = 0x%x\n", memExcInfo[i].size);
        PrintExcInfo("pool free   = 0x%x\n", memExcInfo[i].free);
        PrintExcInfo("pool blkNum = %d\n", memExcInfo[i].blockSize);
        PrintExcInfo("pool error node addr  = 0x%x\n", memExcInfo[i].errorAddr);
        PrintExcInfo("pool error node len   = 0x%x\n", memExcInfo[i].errorLen);
        PrintExcInfo("pool error node owner = %d\n", memExcInfo[i].errorOwner);
    }
#endif
    UINT32 ret = LOS_MemIntegrityCheck(LOSCFG_SYS_HEAP_ADDR);
    if (ret == LOS_OK) {
        PrintExcInfo("system heap memcheck over, all passed!\n");
    }

    PrintExcInfo("memory pool check end!\n");
}
#endif

STATIC VOID OsExcInfoDisplay(const ExcInfo *excInfo)
{
#if (LOSCFG_KERNEL_PRINTF != 0)
    PrintExcInfo("*************Exception Information**************\n");
    OsExcTypeInfo(excInfo);
    OsExcCurTaskInfo(excInfo);
    OsExcRegInfo(excInfo);
    OsExcBackTraceInfo(excInfo);
    OsGetAllTskInfo();
    OsExcMemPoolCheckInfo();
#endif
}

VOID HalExcHandleEntry(UINT32 faultAddr, EXC_CONTEXT_S *excBufAddr, UINT32 type)
{
    g_excInfo.nestCnt++;
    g_excInfo.faultAddr = faultAddr;
    g_excInfo.type = (UINT16)type;

    LosTaskCB *taskCB = (LosTaskCB *)g_newTask;

    if ((taskCB == NULL) || (taskCB == OS_TCB_FROM_TID(g_taskMaxNum))) {
        g_excInfo.phase = OS_EXC_IN_INIT;
        g_excInfo.thrdPid = OS_NULL_INT;
    } else if (HalIntNumGet() != OS_NULL_INT) {
        g_excInfo.phase = OS_EXC_IN_HWI;
        g_excInfo.thrdPid = HalIntNumGet();
    } else {
        g_excInfo.phase = OS_EXC_IN_TASK;
        g_excInfo.thrdPid = taskCB->taskId;
    }

    g_excInfo.context = excBufAddr;

    OsExcInfoDisplay(&g_excInfo);
    for (;;) {

    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
