/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: Low-power Framework.
 * Author: Huawei LiteOS Team
 * Create: 2020-09-19
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

#ifndef _LOS_LOWPOWER_IMPL_H
#define _LOS_LOWPOWER_IMPL_H

#include "los_lowpower.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct {
    VOID (*changeFreq)(UINT8 freq);
    VOID (*enterLightSleep)(VOID);
    VOID (*enterDeepSleep)(VOID);
    VOID (*setWakeUpTimer)(UINT32 timeout);
    VOID (*withdrawWakeUpTimer)(VOID);
    UINT32 (*getSleepTime)(VOID);
    UINT32 (*selectSleepMode)(UINT32);
    UINT32 (*preConfig)(VOID);
    VOID (*postConfig)(VOID);
    VOID (*contextSave)(VOID);
    VOID (*contextRestore)(VOID);
    UINT32 (*getDeepSleepVoteCount)(VOID);
    UINT32 (*getSleepMode)(VOID);
    VOID (*setSleepMode)(UINT32 mode);
} PowerMgrRunOps;

typedef struct {
    UINT32 minLightSleepTicks;
    UINT32 minDeepSleepTicks;
    UINT32 maxDeepSleepTicks;
} PowerMgrConfig;

typedef struct {
    BOOL (*couldDeepSleep)(VOID);
    VOID (*systemWakeup)(VOID);
    BOOL (*suspendPreConfig)(VOID);
    VOID (*suspendDevice)(VOID);
    VOID (*rollback)(VOID);
    VOID (*resumeDevice)(VOID);
    VOID (*resumePostConfig)(VOID);
    VOID (*resumeCallBack)(VOID);
    VOID (*otherCoreResume)(VOID);
    VOID (*resumeFromReset)(VOID);
} PowerMgrDeepSleepOps;

typedef struct {
    PowerMgrRunOps runOps;
    PowerMgrDeepSleepOps deepSleepOps;
    PowerMgrConfig config;
} PowerMgrParameter;

extern VOID LOS_PowerMgrInit(const PowerMgrParameter *para);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif  // _LOS_LOWPOWER_IMPL_H
