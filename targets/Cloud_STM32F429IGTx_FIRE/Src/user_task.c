/*----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: User Task Implementation
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

#include "sys_init.h"
#ifdef CONFIG_FEATURE_FOTA
#include "ota_port.h"
#endif 
#include "nb_iot/los_nb_api.h"
#include "at_frame/at_api.h"

#ifdef LOSCFG_COMPONENTS_NET_AT_BC95
#include "bc95.h"
#endif

#ifdef LOSCFG_DEMOS_AGENT_TINY_MQTT
#include "flash_adaptor.h"
#include "agent_tiny_mqtt_demo.h"
#endif
#ifdef LOSCFG_DEMOS_AGENT_TINY_LWM2M
#include "agent_tiny_lwm2m_demo.h"
#endif
#ifdef WITH_SENSORHUB
#include "sensorhub_demo.h"
#endif
#ifdef LOSCFG_DEMOS_KERNEL
#include "los_inspect_entry.h"
#include "los_demo_entry.h"
#endif
#ifdef LOSCFG_DEMOS_DTLS_SERVER
#include "test_dtls_server.h"
#endif
#if LOSCFG_DEMOS_NBIOT_WITHOUT_ATINY
#include "nb_demo.h"
#endif
#ifdef LOSCFG_DEMOS_LMS
#include "lms_demo.h"
#endif
#ifdef LOSCFG_SHELL
#include "shell.h"
#include "shcmd.h"
#endif

#define USER_TASK_PRIORITY 2
#define DTLS_TASK_PRIORITY 3
static UINT32 g_atiny_tskHandle;
static UINT32 g_fs_tskHandle;

void atiny_task_entry(void)
{
#if defined(WITH_LINUX) || defined(LOSCFG_COMPONENTS_NET_LWIP)
    hieth_hw_init();
    net_init();
#endif
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
    at_api_register(&bc95_interface);
    #endif

    #if defined(LOSCFG_DEMOS_NBIOT_WITHOUT_ATINY)
    demo_nbiot_only();
    #endif
#endif

#ifdef LOSCFG_DEMOS_AGENT_TINY_MQTT
    flash_adaptor_init();
    {
        demo_param_s demo_param = {.init = NULL,
                                   .write_flash_info = flash_adaptor_write_mqtt_info,
                                   .read_flash_info = flash_adaptor_read_mqtt_info};
        agent_tiny_demo_init(&demo_param);
    }
#endif


#if !defined(LOSCFG_DEMOS_NBIOT_WITHOUT_ATINY)
#ifdef CONFIG_FEATURE_FOTA
    hal_init_ota();
#endif
#ifdef LOSCFG_DEMOS_AGENT_TINY_MQTT
    agent_tiny_mqtt_entry();
#endif

#ifdef LOSCFG_DEMOS_AGENT_TINY_LWM2M
    agent_tiny_lwm2m_entry();
#endif
#endif
}

UINT32 creat_agenttiny_task(VOID)
{
    UINT32 ret = LOS_OK;
    TSK_INIT_PARAM_S task_init_param;

    memset(&task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    task_init_param.usTaskPrio = USER_TASK_PRIORITY;
    task_init_param.pcName = "agenttiny_task";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)atiny_task_entry;

#if defined(CONFIG_FEATURE_FOTA) || defined(LOSCFG_COMPONENTS_CONNECTIVITY_MQTT)
    task_init_param.uwStackSize = 0x2000; /* fota use mbedtls bignum to verify signature consuming more stack */
#else
    task_init_param.uwStackSize = 0x1000;
#endif

    ret = LOS_TaskCreate(&g_atiny_tskHandle, &task_init_param);
    if (ret != LOS_OK) {
        return ret;
    }

    return ret;
}


UINT32 create_fs_task(void)
{
    UINT32 ret = LOS_OK;
    TSK_INIT_PARAM_S task_init_param;

    memset(&task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    task_init_param.usTaskPrio = USER_TASK_PRIORITY;
    task_init_param.pcName = "main_task";
    extern void fs_demo(void);
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)fs_demo;
    task_init_param.uwStackSize = 0x1000;

    ret = LOS_TaskCreate(&g_fs_tskHandle, &task_init_param);
    if (LOS_OK != ret) {
        return ret;
    }

    return ret;
}

#if defined(LOSCFG_COMPONENTS_SECURITY_MBEDTLS) && defined(LOSCFG_DEMOS_DTLS_SERVER)
static UINT32 g_dtls_server_tskHandle;
uint32_t create_dtls_server_task(void)
{
    uint32_t ret = LOS_OK;
    TSK_INIT_PARAM_S task_init_param;

    memset(&task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    task_init_param.usTaskPrio = DTLS_TASK_PRIORITY;
    task_init_param.pcName = "dtls_server_task";
    extern void dtls_server_task(void);
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)dtls_server_task;

    task_init_param.uwStackSize = 0x1000;

    ret = LOS_TaskCreate(&g_dtls_server_tskHandle, &task_init_param);
    if (ret != LOS_OK) {
        return ret;
    }

    return ret;
}
#endif

UINT32 app_init(VOID)
{
#ifdef LOSCFG_DEMOS_LMS
    Example_LMSEntry();
#endif
    UINT32 ret = LOS_OK;

    ret = creat_agenttiny_task();
    if (ret != LOS_OK) {
        return LOS_NOK;
    }

#ifdef LOSCFG_DEMOS_KERNEL
#ifdef LOSCFG_DEMOS_KERNEL_ENTRY
    KernelDemoEntry();
#endif
#ifdef LOSCFG_DEMOS_KERNEL_INSPECT_ENTRY
    KernelDemoInspectEntry();
#endif
#endif

#ifdef LOSCFG_DEMOS_FS
    ret = create_fs_task();
    if (ret != LOS_OK) {
        return LOS_NOK;
    }
#endif

#if defined(USE_PPPOS)
    #include "osport.h"
    extern void uart_init(void); // this uart used for the pppos interface
    uart_init();
    extern VOID *main_ppp(UINT32  args);
    task_create("main_ppp", main_ppp, 0x1500, NULL, NULL, 2);
#endif

#if defined(LOSCFG_COMPONENTS_SECURITY_MBEDTLS) && defined(LOSCFG_DEMOS_DTLS_SERVER)
    ret = create_dtls_server_task();
    if (ret != LOS_OK) {
        return LOS_NOK;
    }
#endif

#if defined(WITH_SENSORHUB)
    MiscInit();
#endif

#ifdef LOSCFG_SHELL
    if (OsShellInit(0) != LOS_OK) {
        PRINT_ERR("shell init failed\n");
    }
#endif

    return ret;
}
