/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2019. All rights reserved.
 * Description: AArch64 Exc Implementation
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

#include "los_exc.h"
#include "los_sys_stack_pri.h"
#include "los_memory_pri.h"
#include "los_printf_pri.h"
#include "los_task_pri.h"
#include "los_hw_pri.h"
#include "los_excinfo_pri.h"
#include "los_stackinfo_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC EXC_PROC_FUNC g_excHook = NULL;
UINT32 g_curNestCount = 0;

#define OS_MAX_BACKTRACE 15
#define DUMPSIZE         128U
#define DUMPREGS         30
#define FP_NUM           29

#define NBIT(val, high, low) (((val) >> (low)) & ((1U << (((high) - (low)) + 1)) - 1))
#define GET_IL(esr) ((esr) & (1U << 25))
#define IS_VALID_ADDR(ptr) (((ptr) >= SYS_MEM_BASE) &&       \
                            ((ptr) <= g_sys_mem_addr_end) && \
                            IS_ALIGNED((ptr), sizeof(CHAR *)))

VOID OsDecodeDataAbortISS(UINT32 bitsISS)
{
    UINT32 bitFnV = bitsISS & (1U << 10);   /* FnV bit[10] */
    UINT32 bitWnR = bitsISS & (1U << 6);    /* WnR bit[6] */
    UINT32 bitsDFSC = NBIT(bitsISS, 5, 0);  /* DFSC bits[5:0] */

    if (!bitFnV) {
        if (bitWnR) {
            PRINTK("Abort caused by a write instruction.");
        } else {
            PRINTK("Abort caused by a read instruction.");
        }
        switch (bitsDFSC) {
            case 0x21:  /* 0b100001 */
                PRINTK("Alignment fault.\n");
                break;
            case 0x0:   /* 0b000000 */
            case 0x01:  /* 0b000001 */
            case 0x03:  /* 0b000011 */
            case 0x04:  /* 0b000100 */
                PRINTK("Address size fault.\n");
                break;
            default:
                PRINTK("\nOMG!UNKNOWN fault, "
                       "check ISS encoding for an exception from a Data Abort in AARM for armv8-a.\n");
                break;
        }
    } else {
        PRINTK("FAR is not valid, and holds an UNKNOWN value.\n");
    }
}

STATIC VOID OsExcType(const ExcContext *frame, UINT32 regESR, UINT32 bitsEC)
{
    UINT32 bitIL = GET_IL(regESR);
    UINT32 bitsISS = NBIT(regESR, 24, 0); /* Instruction Specific Syndrome in ESR_ELx[24:0] */
    UINT64 regFAR;

    switch (bitsEC) {
        case 0x24:  /* 0b100100 */
        case 0x25:  /* 0b100101 */
            PrintExcInfo("Data Abort.\n");
            /* read the FAR register */
            regFAR = AARCH64_SYSREG_READ(FAR_ELx);
            /* decode the iss */
            if (bitIL) {
                OsDecodeDataAbortISS(bitsISS);
            }
            PrintExcInfo("PC at 0x%llx,FAR 0x%llx,ISS 0x%x\n", frame->regELR, regFAR, bitsISS);
            break;
        case 0x20:  /* 0b100000 */
        case 0x21:  /* 0b100001 */
            PrintExcInfo("Instruction Abort.\n");
            break;
        case 0x22:  /* 0b100010 */
            PrintExcInfo("PC alignment fault.\n");
            break;
        case 0x26:  /* 0b100110 */
            PrintExcInfo("SP alignment fault.\n");
            break;
        default:
            PrintExcInfo("OMG!Unknown synchronous exception, "
                         "check Exception Syndrome Register in AARM for armv8-a.\n");
            break;
    }
    PrintExcInfo("ESR 0x%x: ec 0x%x, il 0x%x, iss 0x%x\n", regESR, bitsEC, bitIL, bitsISS);
}

UINT32 LOS_ExcRegHook(EXC_PROC_FUNC excHook)
{
    UINT32 intSave;

    intSave = LOS_IntLock();
    g_excHook = excHook;
    LOS_IntRestore(intSave);

    return LOS_OK;
}

VOID BackTraceSub(UINTPTR regFP)
{
    UINTPTR tmpFP;
    UINTPTR backLR;
    UINTPTR backFP = regFP;
    UINT32 count = 0;

    while ((backFP > OS_SYS_FUNC_ADDR_START) && (backFP < OS_SYS_FUNC_ADDR_END)) {
        tmpFP = backFP;
        backFP = *((UINTPTR *)(tmpFP));
        backLR = *((UINTPTR *)(tmpFP + sizeof(CHAR *)));
        PrintExcInfo("traceback %u -- lr = 0x%llx    fp = 0x%llx\n", count, backLR, backFP);

        count++;
        if (count == OS_MAX_BACKTRACE) {
            break;
        }
    }
}

VOID BackTrace(UINTPTR regFP)
{
    UINTPTR backFP;

    if ((VOID *)regFP == NULL) {
        backFP = Get_Fp();
    } else {
        backFP = regFP;
    }

    PrintExcInfo("*******backtrace begin*******\n");
    BackTraceSub(backFP);
}

VOID OsCallStackInfo(VOID)
{
    UINT32 count = 0;
    LosTaskCB *runTask = OsCurrTaskGet();

    UINTPTR *stackBottom = (UINTPTR *)(runTask->topOfStack + runTask->stackSize);
    UINTPTR *stackPointer = stackBottom;

    PrintExcInfo("runTask->stackPointer = 0x%llx\n"
                 "runTask->topOfStack = 0x%llx\n"
                 "text_start = 0x%llx,text_end = 0x%llx\n",
                 stackPointer, runTask->topOfStack, &__text_start, &__text_end);

    while ((stackPointer > (UINTPTR *)runTask->topOfStack) && (count < OS_MAX_BACKTRACE)) {
        if ((*stackPointer > (UINTPTR)(&__text_start)) &&
            (*stackPointer < (UINTPTR)(&__text_end)) &&
            IS_ALIGNED(*stackPointer, sizeof(CHAR *))) {
            if ((*(stackPointer - 1) > (UINTPTR)runTask->topOfStack) &&
                (*(stackPointer - 1) < (UINTPTR)stackBottom) &&
                IS_ALIGNED(*(stackPointer - 1), sizeof(CHAR *))) {
                count++;
                PrintExcInfo("traceback %u -- lr = 0x%llx\n", count, *stackPointer);
            }
        }
        stackPointer--;
    }
    PRINTK("\n");
}

VOID OsDumpContextMem(const ExcContext *excBufAddr)
{
    UINT32 count = 0;
    const UINT64 *excReg = NULL;

    for (excReg = &(excBufAddr->X[0]); count <= (DUMPREGS - 1); excReg++, count++) {
        if (IS_VALID_ADDR(*excReg)) {
            PrintExcInfo("\ndump mem around X%u:%p", count, (*excReg));
        }
    }

    if (IS_VALID_ADDR(excBufAddr->SP)) {
        PrintExcInfo("\ndump mem around SP:%p", excBufAddr->SP);
    }
}

STATIC const StackInfo g_excStack[] = {
    {&__stack_startup, OS_EXC_START_STACK_SIZE, "start_stack"},
#ifdef LOSCFG_IRQ_USE_STANDALONE_STACK
    {&__irq_stack, OS_EXC_IRQ_STACK_SIZE, "irq_stack"}
#endif
};

VOID OsExcInit(VOID)
{
    OsExcStackInfoReg(g_excStack, sizeof(g_excStack) / sizeof(g_excStack[0]));
}

VOID OsExcDumpContext(const ExcContext *excBufAddr)
{
    UINT32 i;
    LosTaskCB *runTask = OsCurrTaskGet();

    PrintExcInfo("taskName = %s\nTaskID = %u\nTask StackSize = %u\n"
                 "system mem addr = %p\nPC = 0x%llx\nLR = 0x%llx\n",
                 runTask->taskName, runTask->taskID, runTask->stackSize,
                 m_aucSysMem0, excBufAddr->regELR, excBufAddr->LR);

    for (i = 0; i < DUMPREGS; i++) {
        PrintExcInfo("X%-02d = 0x%llx\n", i, excBufAddr->X[i]);
    }

    PrintExcInfo("LR = 0x%llx\nELR = 0x%llx\nSPSR = 0x%llx\n",
                 excBufAddr->LR, excBufAddr->regELR, excBufAddr->SPSR);

    BackTrace(excBufAddr->X[FP_NUM]);
    OsExcStackInfo();

    OsDumpContextMem(excBufAddr);
}

VOID OsCurrentELGet(UINT32 reg)
{
    PRINT_ERR("The current exception level is EL%d\n", NBIT(reg, 3, 2));
}

VOID OsExceptSyncExcHdl(ExcContext *frame)
{
    UINT32 regESR = AARCH64_SYSREG_READ(ESR_ELx);
    UINT32 bitsEC = NBIT(regESR, 31, 26);       /* get the 26-31bit for EC */

#ifdef LOSCFG_SHELL_EXCINFO
    log_read_write_fn func = GetExcInfoRW();
#endif

    g_curNestCount++;

    if (g_curNestCount == 1) {
        if (g_excHook != NULL) {
            g_excHook(0, frame);
        }

#ifdef LOSCFG_SHELL_EXCINFO
        if (func != NULL) {
            SetExcInfoIndex(0);
        }
        OsRecordExcInfoTime();
#endif
        PrintExcInfo("/*******************Exception Information*******************/"
                     "\nExcClass:0x%x => ", bitsEC);

        OsExcType(frame, regESR, bitsEC);
        OsExcDumpContext(frame);

        PrintExcInfo("/*******************Exception Information END*****************/\n");
    } else {
        OsCallStackInfo();
    }
#ifdef LOSCFG_SHELL_EXCINFO
    if (func != NULL) {
        PrintExcInfo("Be sure flash space bigger than GetExcInfoIndex():0x%x\n", GetExcInfoIndex());
        WriteExcInfoToBuf("Be sure flash space bigger than GetExcInfoIndex():0x%x\n", GetExcInfoIndex());
        func(GetRecordAddr(), GetRecordSpace(), 0, GetExcInfoBuf());
    }
#endif
#ifdef LOSCFG_EXC_INTERACTION
    OsExcInteractionTaskKeep();
#endif
    for (;;) {
        ;
    }
}

VOID OsTaskBackTrace(UINT32 taskID)
{
    LosTaskCB *taskCB = NULL;

    if (taskID >= g_taskMaxNum) {
        PRINT_ERR("\r\nTask PID is invalid!\n");
        return;
    }
    taskCB = OS_TCB_FROM_TID(taskID);
    if ((taskCB->taskStatus & OS_TASK_STATUS_UNUSED) ||
        (taskCB->taskEntry == NULL) ||
        (taskCB->taskName == NULL)) {
        PRINT_ERR("\r\nThe task is not created!\n");
        return;
    }
    PRINTK("TaskName = %s\n", taskCB->taskName);
    PRINTK("TaskID = 0x%x\n", taskCB->taskID);
    BackTrace(((TaskContext *)(taskCB->stackPointer))->X[FP_NUM]);
}

VOID OsBackTrace(VOID)
{
    LosTaskCB *runTask = OsCurrTaskGet();

    PrintExcInfo("runTask->taskName = %s\n", runTask->taskName);
    PrintExcInfo("runTask->taskID = %u\n", runTask->taskID);
    BackTrace((UINTPTR)NULL);
}

__attribute__((noinline)) VOID LOS_Panic(const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    UartVprintf(fmt, ap);
    va_end(ap);
    __asm__ __volatile__("svc #0");
}

/* stack protector */
UINT64 __stack_chk_guard = 0x11223344d00a0dff;

VOID __stack_chk_fail(VOID)
{
    /* __builtin_return_address is a builtin function, building in gcc */
    LOS_Panic("stack-protector: Kernel stack is corrupted in: %p\n",
              __builtin_return_address(0));
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
