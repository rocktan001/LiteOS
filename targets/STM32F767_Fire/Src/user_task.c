/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: User Task Implementation
 * Author: Huawei LiteOS Team
 * Create: 2021-07-01
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

#include <stdio.h>
#include "user_task.h"
#include "los_typedef.h"
#include "demo_entry.h"
#include "los_task.h"
#include "los_event.h"
#include "led.h"
#include "los_spinlock.h"
#include "los_exc.h"
#include "los_swtmr.h"
#include "gt9xx.h"
extern uint32_t g_interrupt_pc;
static EVENT_CB_S g_pevent;
/* ????????????????????? */
#define EVENT_WAIT 0x00000001
UINT64 g_lastTick;
STATIC UINT32 LedTask1(VOID)
{// 2022-3-31 tanzhongqiang ??????event ???????????????????????????????????????????????????????????????????????????CPU?????????event ??????????????????

    UINT32 event;

    while (1) {          
        event = LOS_EventRead(&g_pevent, EVENT_WAIT, LOS_WAITMODE_AND, LOS_WAIT_FOREVER);
        if (event == EVENT_WAIT) {
            LOS_EventClear(&g_pevent, ~g_pevent.uwEventID);
            // printf("last_pc : 0x%x\n",g_interrupt_pc);  
            Fire_DEBUG_GPIOB6_TRIGGER();                 
        }else{
            printf("event 0x%x\n",event);
        }    
    }
    return 0;
}

STATIC UINT32 LedTask2(VOID)
{
    while (1) {       
        LOS_TaskDelay(500); 
        // LOS_TaskYield();   
        Fire_DEBUG_GPIOB7_TRIGGER();
        // LedTaskTrigger();
    }
    return 0;
}
VOID Timer1_CallBack(UINT32 arg)
{
    g_lastTick=LOS_TickCountGet();
}

STATIC UINT32 LedTaskCreate(VOID)
{
    UINT32 ret;
    UINT32 taskId = 0;
    UINT16 id1;     // Timer1 id

#if 0
    GTP_Init_Panel();
#endif
    TSK_INIT_PARAM_S ledTaskParam;

       /* ??????????????? */
    ret = LOS_EventInit(&g_pevent);
    if (ret != LOS_OK) {
        printf("init event failed .\n");
        return -1;
    }

    ret = (UINT32)memset_s(&ledTaskParam, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    if (ret != EOK) {
        return ret;
    }

    // LOS_TaskLock();
    ledTaskParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LedTask1;
    ledTaskParam.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    ledTaskParam.pcName = "ledTask1";
    ledTaskParam.usTaskPrio = LOSCFG_BASE_CORE_TSK_DEFAULT_PRIO;
    ledTaskParam.uwResved = LOS_TASK_STATUS_DETACHED;
    LOS_TaskCreate(&taskId, &ledTaskParam);

    ledTaskParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LedTask2;
    ledTaskParam.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    ledTaskParam.pcName = "ledTask2";
    ledTaskParam.usTaskPrio = LOSCFG_BASE_CORE_TSK_DEFAULT_PRIO;
    ledTaskParam.uwResved = LOS_TASK_STATUS_DETACHED;
    LOS_TaskCreate(&taskId, &ledTaskParam);

    LOS_SwtmrCreate(1000*30, LOS_SWTMR_MODE_PERIOD, Timer1_CallBack, &id1, 1);
    LOS_SwtmrStart(id1);
    // LOS_TaskUnlock();
    return 0; 
}

VOID app_init(VOID)
{
    printf("app init!\n");
    (VOID)LedTaskCreate();
    DemoEntry();
}

void LedTaskTrigger(void)
{
    LOS_EventWrite(&g_pevent, EVENT_WAIT);
}
