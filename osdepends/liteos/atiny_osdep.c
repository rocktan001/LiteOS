/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: LiteOS Task Module Implementation
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

#include "osdepends/atiny_osdep.h"
#include "los_memory.h"
#include "los_sys_pri.h"
#include "los_sem_pri.h"
#include "los_tick_pri.h"
#include <stdbool.h>
#include "los_mux.h"

#define ATINY_CNT_MAX_WAITTIME 0xFFFFFFFF
#define LOG_BUF_SIZE 256

#ifndef OK
#define OK 0
#endif

#ifndef ERR
#define ERR (-1)
#endif

static uint64_t osKernelGetTickCount (void)
{
    uint64_t ticks;
    UINTPTR uvIntSave;

    if (OS_INT_ACTIVE) {
        ticks = 0U;
    } else {
        uvIntSave = LOS_IntLock();
        ticks = g_tickCount[0];
        LOS_IntRestore(uvIntSave);
    }

    return ticks;
}

uint64_t atiny_gettime_ms(void)
{
    return osKernelGetTickCount() * (OS_SYS_MS_PER_SECOND / LOSCFG_BASE_CORE_TICK_PER_SECOND);
}

void *atiny_malloc(size_t size)
{
    return LOS_MemAlloc(m_aucSysMem0, size);
}

void atiny_free(void *ptr)
{
    (void)LOS_MemFree(m_aucSysMem0, ptr);
}

int atiny_snprintf(char *buf, unsigned int size, const char *format, ...)
{
    int ret;
    va_list args;

    va_start(args, format);
    ret = vsprintf_s(buf, size, format, args);
    va_end(args);

    return ret;
}

int atiny_printf(const char *format, ...)
{
    int ret;
    char str_buf[LOG_BUF_SIZE] = {0};
    va_list list;

    (void)memset_s(str_buf, LOG_BUF_SIZE, 0, LOG_BUF_SIZE);
    va_start(list, format);
    ret = vsprintf_s(str_buf, LOG_BUF_SIZE, format, list);
    va_end(list);

    printf("%s", str_buf);

    return ret;
}

char *atiny_strdup(const char *ch)
{
    char *copy = NULL;
    size_t length;

    if (ch == NULL) {
        return NULL;
    }

    length = strlen(ch);
    copy = (char *)atiny_malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    (void)strcpy_s(copy, length + 1, ch);
    copy[length] = '\0';

    return copy;
}

void atiny_delay(uint32_t second)
{
    (void)LOS_TaskDelay(second * LOSCFG_BASE_CORE_TICK_PER_SECOND);
}

#if (LOSCFG_BASE_IPC_SEM == YES)

void *atiny_mutex_create(void)
{
    uint32_t ret;
    uint32_t semId;

    if (OS_INT_ACTIVE) {
        return NULL;
    }

    ret = LOS_BinarySemCreate(1, (UINT32 *)&semId);
    if (ret == LOS_OK) {
        return (void *)(GET_SEM(semId));
    } else {
        return NULL;
    }
}

void atiny_mutex_destroy(void *mutex)
{
    if (OS_INT_ACTIVE) {
        return;
    }

    if (mutex == NULL) {
        return;
    }

    (void)LOS_SemDelete(((LosSemCB *)mutex)->semId);
}

void atiny_mutex_lock(void *mutex)
{
    if (mutex == NULL) {
        return;
    }

    if (OS_INT_ACTIVE) {
        return;
    }

    (void)LOS_SemPend(((LosSemCB *)mutex)->semId, ATINY_CNT_MAX_WAITTIME);
}

void atiny_mutex_unlock(void *mutex)
{
    if (mutex == NULL) {
        return;
    }

    (void)LOS_SemPost(((LosSemCB *)mutex)->semId);
}

#else

void *atiny_mutex_create(void)
{
    return NULL;
}

void atiny_mutex_destroy(void *mutex)
{
    ((void)mutex);
}

void atiny_mutex_lock(void *mutex)
{
    ((void)mutex);
}

void atiny_mutex_unlock(void *mutex)
{
    ((void)mutex);
}

#endif /* LOSCFG_BASE_IPC_SEM == YES */


#if (LOSCFG_BASE_IPC_MUX == YES)
static bool atiny_task_mutex_is_valid(const atiny_task_mutex_s *mutex)
{
    return (mutex != NULL) && (mutex->valid);
}

int atiny_task_mutex_create(atiny_task_mutex_s *mutex)
{
    int ret;

    if (mutex == NULL) {
        return ERR;
    }

    (void)memset_s(mutex, sizeof(atiny_task_mutex_s), 0, sizeof(atiny_task_mutex_s));
    ret = (int)LOS_MuxCreate(&mutex->mutex);
    if (ret != LOS_OK) {
        return ret;
    }
    mutex->valid = true;
    return LOS_OK;
}

#define ATINY_DESTROY_MUTEX_WAIT_INTERVAL 100
int atiny_task_mutex_delete(atiny_task_mutex_s *mutex)
{
    int ret;

    if (mutex == NULL) {
        return ERR;
    }

    if (!atiny_task_mutex_is_valid(mutex)) {
        return ERR;
    }

    do {
        ret = (int)LOS_MuxDelete(mutex->mutex);
        if (ret == (int)LOS_ERRNO_MUX_PENDED) {
            (void)LOS_TaskDelay(ATINY_DESTROY_MUTEX_WAIT_INTERVAL);
        } else {
            break;
        }
    }while (true);

    (void)memset_s(mutex, sizeof(atiny_task_mutex_s), 0, sizeof(atiny_task_mutex_s));

    return ret;
}
int atiny_task_mutex_lock(atiny_task_mutex_s *mutex)
{
    if (mutex == NULL) {
        return ERR;
    }

    if (!atiny_task_mutex_is_valid(mutex)) {
        return ERR;
    }
    return (int)LOS_MuxPend(mutex->mutex, ATINY_CNT_MAX_WAITTIME);
}
int atiny_task_mutex_unlock(atiny_task_mutex_s *mutex)
{
    if (mutex == NULL) {
        return ERR;
    }

    if (!atiny_task_mutex_is_valid(mutex)) {
        return ERR;
    }
    return (int)LOS_MuxPost(mutex->mutex);
}
#endif /* LOSCFG_BASE_IPC_MUX == YES */


