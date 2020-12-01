/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
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

/* *
 * @defgroup los_powermgr Basic definitions
 * @ingroup kernel
 */

#ifndef _LOS_LOWPOWER_H
#define _LOS_LOWPOWER_H

#include "los_base.h"
#include "los_sys.h"
#include "los_err.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef enum LOS_INTERMIT_MODE {
    /* intermit modes */
    LOS_INTERMIT_NONE = 0,
    LOS_INTERMIT_LIGHT_SLEEP,
    LOS_INTERMIT_DEEP_SLEEP,
    LOS_INTERMIT_STANDBY,
    LOS_INTERMIT_SHUTDOWN,
    LOS_INTERMIT_MAX,
} LosIntermitMode;

typedef enum LOS_FREQ_MODE {
    /* frequency modes */
    LOS_SYS_FREQ_SUPER = 0,
    LOS_SYS_FREQ_HIGH,
    LOS_SYS_FREQ_NORMAL,
    LOS_SYS_FREQ_LOW,
    LOS_SYS_FREQ_MAX,
} LosFreqMode;

typedef UINT32 (*LowpowerExternalVoterHandle)(VOID);

STATIC INLINE BOOL FreqHigher(LosFreqMode freq1, LosFreqMode freq2)
{
    return freq1 < freq2;
}

/* *
 * @ingroup los_powermgr
 * Define the structure of the power manager operations.
 *
 */
typedef struct {
    VOID (*process)(VOID);
    VOID (*wakeupFromReset)(VOID);
    VOID (*resumeFromInterrupt)(UINT32);

    VOID (*changeFreq)(LosFreqMode);
    VOID (*deepSleepVoteBegin)(VOID);
    VOID (*deepSleepVoteEnd)(VOID);
    VOID (*deepSleepVoteDelay)(UINT32 tick);
    VOID (*registerExternalVoter)(UINT32 (*handler)(VOID));
    UINT32 (*getDeepSleepVoteCount)(VOID);
    UINT32 (*getSleepMode)(VOID);
    VOID (*setSleepMode)(UINT32 mode);
} PowerMgrOps;

extern VOID LOS_PowerMgrChangeFreq(LosFreqMode freq);

extern VOID LOS_PowerMgrDeepSleepVoteBegin(VOID);

extern VOID LOS_PowerMgrDeepSleepVoteEnd(VOID);

extern VOID LOS_PowerMgrSleepDelay(UINT32 tick);

extern VOID LOS_PowerMgrRegisterExtVoter(UINT32 (*)(VOID));

extern UINT32 LOS_PowerMgrGetSleepMode(VOID);

extern UINT32 LOS_PowerMgrGetDeepSleepVoteCount(VOID);

// register pm_mgr or customized mgr by developers
extern VOID LOS_LowpowerInit(const PowerMgrOps *pmOps);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* _LOS_LOWPOWER_H */