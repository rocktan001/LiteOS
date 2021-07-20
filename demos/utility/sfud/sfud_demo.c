/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Sfud Demo Implementation
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

#include <sfud.h>
#include <stdio.h>
#include <stdlib.h>
#include "los_task.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define DEFAULT_TASK_PRIORITY   7
#define DEFAULT_TASK_STACK_SIZE 2048

STATIC UINT32 g_demoTaskId;

INT32 SfudDemoEntry(VOID) 
{
    INT32 ret = sfud_init();
    if (ret != SFUD_SUCCESS) {
        printf("Sfud init failed\n");
        return LOS_NOK;
    }
    // In sfdu device table, pointer is offset to SFUD_W25Q256JV_DEVICE_INDEX.
    const sfud_flash *flash = sfud_get_device_table() + SFUD_W25Q256JV_DEVICE_INDEX;
    INT32 addr = 0; // Operate on spi falsh address 0.
    INT32 size = 0x200; // Set the size of 512 data to operate.
    UINT8 *buff = (UINT8 *)malloc(size);
    if (buff == NULL) {
        return LOS_NOK;
    }
    for (INT32 i = 0, j = 0; i < size; i++, j++) {
         buff[i] = j;
         if (buff[i] == 0xFF) { // The maximum value of a byte is 0xFF;
             j = 0;
         }
    }

    // The following are write and read, erase example operations.
    printf("Do sfud write.\n");
    ret = sfud_write(flash, addr, size, buff);
    if (ret != SFUD_SUCCESS) {
        printf("Sfud write failed.\n");
        free(buff);
        return LOS_NOK;
    }
    printf("Sfud write success.\n");

    ret = memset_s(buff, size, 0, size);
    if (ret != EOK) {
       return LOS_NOK;
    }
    printf("Do sfud read.\n");
    ret = sfud_read(flash, addr, size, buff);
    if (ret != SFUD_SUCCESS) {
        printf("Sfud read failed.\n");
        free(buff);
        return LOS_NOK;
    }
    printf("Sfud read success.\n");
    for (INT32 i = 0; i < size; ++i) {
         printf("%02x ", buff[i]);
         if (((i + 1) % 0x10) == 0) { // Each row displays 16 pieces of data.
             printf("\n");
         }
    }
    printf("\n");

    printf("Do sfud erase.\n");
    ret = sfud_erase(flash, addr, size);
    if (ret != SFUD_SUCCESS) {
        printf("Sfud erase failed.\n");
        free(buff);
        return LOS_NOK;
    }
    printf("Sfud erase success.\n");
    free(buff);
    return LOS_OK;
}


VOID SfudDemoTask(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S taskInitParam;

    ret = memset_s(&taskInitParam, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    if (ret != EOK) {
        return;
    }
    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)SfudDemoEntry;
    taskInitParam.pcName       = "SfudDemoTask";
    taskInitParam.uwStackSize  = DEFAULT_TASK_STACK_SIZE;
    taskInitParam.usTaskPrio   = DEFAULT_TASK_PRIORITY;
    taskInitParam.uwResved     = LOS_TASK_STATUS_DETACHED;
    ret = LOS_TaskCreate(&g_demoTaskId, &taskInitParam);
    if (ret != LOS_OK) {
        printf("Create easyflash demo task failed.\n");
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
