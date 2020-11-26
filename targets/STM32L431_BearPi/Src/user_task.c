/*----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: User Task
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

#include "los_base.h"
#include "los_task_pri.h"
#include "los_typedef.h"
#include "los_sys.h"
#include "platform_config.h"

#define USER_TASK_PRIORITY 2
static UINT32 g_fs_tskHandle;

UINT32 create_fs_task(void)
{
    UINT32 ret = LOS_OK;
    TSK_INIT_PARAM_S task_init_param;

    memset(&task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    task_init_param.usTaskPrio = USER_TASK_PRIORITY;
    task_init_param.pcName = "fs_task";
    extern void fs_demo(void);
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)fs_demo;
    task_init_param.uwStackSize = 0x1000;

    ret = LOS_TaskCreate(&g_fs_tskHandle, &task_init_param);
    if (LOS_OK != ret) {
        return ret;
    }

    return ret;
}

UINT32 app_init(VOID)
{
    UINT32 ret = LOS_OK;

    printf("Hello, welcome to liteos!\n");

#ifdef LOSCFG_DEMOS_FS
    ret = create_fs_task();
    if (ret != LOS_OK) {
        return LOS_NOK;
    }
#endif

    return ret;
}