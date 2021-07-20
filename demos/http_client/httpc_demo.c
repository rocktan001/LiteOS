/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Http Client Demo Implementation
 * Author: Huawei LiteOS Team
 * Create: 2021-07-20
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

#include "http_client.h"
#include "los_task.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define TASK_PRIORITY           7
#define TASK_STACK_SIZE         0x2000
#define DEFAULT_HOST            "192.168.10.182"
#define DEFAULT_PORT            80
#define DEFAULT_URL             "/index.html"
#define HTTP_CLIENT_WAIT_TIME   20000

STATIC UINT32 g_demoTaskId;

STATIC err_t HttpcRecv(VOID *arg, struct altcp_pcb *pcb, struct pbuf *p, err_t err)
{
    struct pbuf *q;

    LWIP_ASSERT("p != NULL", p != NULL);

    printf("http receive:\n");
    for (q = p; q != NULL; q = q->next) {
        printf("%s", (char *)q->payload);
    }
    printf("http receive finished.\n");
    altcp_recved(pcb, p->tot_len);
    pbuf_free(p);
    return ERR_OK;
}

STATIC err_t HttpcHeaderDone(httpc_state_t *connection, VOID *arg, struct pbuf *hdr, UINT16 hdr_len, UINT32 content_len)
{
    return ERR_OK;
}

STATIC VOID HttpcResult(VOID *arg, httpc_result_t httpc_result, UINT32 rx_content_len, UINT32 srv_res, err_t err)
{
    if (httpc_result != HTTPC_RESULT_OK) {
        printf("http close failed result :%d.\n", httpc_result);
    }
}

STATIC httpc_connection_t g_setting = {
    .use_proxy = 0,
    .headers_done_fn = HttpcHeaderDone,
    .result_fn = HttpcResult,
};

err_t HttpcGet(const char *server, uint16_t port, const char *url, altcp_recv_fn recv_fn)
{
    return httpc_get_file_dns(server, port, url, &g_setting, recv_fn, NULL, NULL);
}

STATIC VOID DemoTaskEntry(VOID)
{
    printf("Http client demo start to run.\n");
    LOS_TaskDelay(20000);   // wait lwip dhcp get ip.
    (VOID)HttpcGet(DEFAULT_HOST, DEFAULT_PORT, DEFAULT_URL, (altcp_recv_fn)HttpcRecv);
}

VOID HttpClientDemoTask(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S taskInitParam;

    ret = memset_s(&taskInitParam, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    if (ret != EOK) {
        return;
    }
    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)DemoTaskEntry;
    taskInitParam.uwStackSize = TASK_STACK_SIZE;
    taskInitParam.pcName = "HttpClientDemoTask";
    taskInitParam.usTaskPrio = TASK_PRIORITY;
    taskInitParam.uwResved = LOS_TASK_STATUS_DETACHED;
    ret = LOS_TaskCreate(&g_demoTaskId, &taskInitParam);
    if (ret != LOS_OK) {
        printf("Create lua demo task failed.\n");
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
