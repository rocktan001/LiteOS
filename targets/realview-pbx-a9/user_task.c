/*----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Os Adapt
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

#include "uart.h"
#include "hisoc/uart.h"
#ifdef LOSCFG_SHELL_FULL_CAP
#include "show.h"
#endif
#ifdef LOSCFG_DRIVERS_BASE
#include "linux/device.h"
#include "linux/platform_device.h"
#include "linux/module.h"
#endif
#ifdef LOSCFG_KERNEL_CONSOLE
#include "virtual_serial.h"
#include "console.h"
#endif

#ifdef LOSCFG_DEMOS_KERNEL
#include "los_inspect_entry.h"
#include "los_demo_entry.h"
#endif

#ifdef LOSCFG_DEMOS_LMS
#include "lms_demo.h"
#endif


UINT32 app_init(VOID)
{
    PRINTK("app_init\n");
#ifdef LOSCFG_SHELL
    if (OsShellInit(0) != LOS_OK) {
        PRINT_ERR("shell init failed\n");
    }
#endif

#ifdef LOSCFG_DEMOS_LMS
    Example_LMSEntry();
#endif

#ifdef LOSCFG_DEMOS_KERNEL
#ifdef LOSCFG_DEMOS_KERNEL_ENTRY
    KernelDemoEntry();
#endif
#ifdef LOSCFG_DEMOS_KERNEL_INSPECT_ENTRY
    KernelDemoInspectEntry();
#endif
#endif
return LOS_OK;
}
