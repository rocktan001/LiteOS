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

#ifdef LOSCFG_COMPONNETS_NET_AT
#include "sys_init.h"
#include "nb_iot/los_nb_api.h"
#include "at_frame/at_api.h"
#include "bc95.h"
#endif
#ifdef LOSCFG_SHELL
#include "shell.h"
#include "shcmd.h"
#endif

#define USER_TASK_PRIORITY 2

static UINT32 g_fs_tskHandle;
static UINT32 g_atiny_tskHandle;

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
    if (ret != LOS_OK) {
        return ret;
    }

    return ret;
}


void atiny_task_entry(void)
{
#if defined(LOSCFG_COMPONNETS_NET_AT)

    #if defined(LOSCFG_COMPONENTS_NET_AT_ESP8266)
    extern at_adaptor_api esp8266_interface;
    printf("\r\n=============agent_tiny_entry  LOSCFG_COMPONENTS_NET_AT_ESP8266============================\n");
    at_api_register(&esp8266_interface);

    #elif defined(LOSCFG_COMPONENTS_NET_AT_BG36)
    extern at_adaptor_api emtc_bg36_interface;
    printf("\r\n=============agent_tiny_entry  LOSCFG_COMPONENTS_NET_AT_BG36============================\n");
    at_api_register(&emtc_bg36_interface);

    #elif defined(LOSCFG_COMPONENTS_NET_AT_SIM900A)
    extern at_adaptor_api sim900a_interface;
    printf("\r\n=============agent_tiny_entry  LOSCFG_COMPONENTS_NET_AT_SIM900A============================\n");
    at_api_register(&sim900a_interface);

    #elif defined(LOSCFG_COMPONENTS_NET_AT_BC95)
    extern at_adaptor_api bc95_interface;
    printf("\r\n=============agent_tiny_entry  LOSCFG_COMPONENTS_NET_AT_BC95============================\n");
    los_nb_init((const int8_t *)"172.25.233.98",(const int8_t *)"5600",NULL);
    los_nb_notify("\r\n+NSONMI:",strlen("\r\n+NSONMI:"),NULL,nb_cmd_match);
    at_api_register(&bc95_interface);

    #elif defined(USE_NB_NEUL95_NO_ATINY)
    demo_nbiot_only();
    #else

    #endif
#endif
}

UINT32 creat_agenttiny_task(VOID)
{
    UINT32 ret = LOS_OK;
    TSK_INIT_PARAM_S task_init_param;

    task_init_param.usTaskPrio = 2;
    task_init_param.pcName = "agenttiny_task";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)atiny_task_entry;
    task_init_param.uwStackSize = 0x1000;

    ret = LOS_TaskCreate(&g_atiny_tskHandle, &task_init_param);
    if (ret != LOS_OK) {
        return ret;
    }

    return ret;
}

UINT32 app_init(VOID)
{
    UINT32 ret = LOS_OK;
#ifdef LOSCFG_COMPONNETS_NET_AT
    ret = creat_agenttiny_task();
    if (ret != LOS_OK) {
        return LOS_NOK;
    }
#endif

#ifdef LOSCFG_DEMOS_FS
    ret = create_fs_task();
    if (ret != LOS_OK) {
        return LOS_NOK;
    }
#endif

#ifdef LOSCFG_SHELL
    if (OsShellInit(0) != LOS_OK) {
        PRINT_ERR("shell init failed\n");
    }
#endif

    return ret;
}