/*----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Uart Module Implementation
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

#include <ctype.h>
#include <los_hwi.h>
#include <los_sem.h>
#include "usart.h"

#define UART_EVENT_MASK 0x1
#define UART_READ_MASK  0xFF

STATIC UINT8 g_rec = 0;
EVENT_CB_S g_uartEvent;

INT32 uart_putc(CHAR c)
{
    return uart_write(&c, 1, 0);
}

UINT8 uart_getc(VOID)
{
    UINT8 ch = 0;
    LOS_IntLock();
    HAL_UART_Receive(&huart1, &ch, 1, 0);
    LOS_IntUnLock();
    return ch;
}

STATIC VOID uart_notice_adapt(VOID)
{
    LOS_EventWrite(&g_uartEvent, UART_EVENT_MASK);
}

UINT32 uart_wait_adapt(VOID)
{
    UINT32 ret;
    ret = LOS_EventRead(&g_uartEvent, UART_EVENT_MASK,
                        LOS_WAITMODE_AND | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER);
    if (ret == UART_EVENT_MASK) {
        return LOS_OK;
    }

    return LOS_NOK;
}

STATIC VOID uart_irqhandle(VOID)
{
    g_rec = uart_getc();
    uart_notice_adapt();
}

INT32 uart_hwiCreate(VOID)
{
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
    (VOID)LOS_HwiCreate(USART1_IRQn + 16, 0, 0, uart_irqhandle, NULL); // 16: cortex-m irq number shift
    (VOID)LOS_EventInit(&g_uartEvent);

    return LOS_OK;
}

UINT8 uart_read(VOID)
{
    UINT8 c = 0;
    if (uart_wait_adapt() == LOS_OK) {
        c = g_rec;
        return c;
    }
    return c;
}

INT32 uart_write(const CHAR *buf, INT32 len, INT32 timeout)
{
#ifdef LOSCFG_PLATFORM_STM32F072_Nucleo
    (VOID)HAL_UART_Transmit(&huart2, (UINT8 *)buf, len, DEFAULT_TIMEOUT);
#else
    (VOID)HAL_UART_Transmit(&huart1, (UINT8 *)buf, len, DEFAULT_TIMEOUT);
#endif
    return len;
}
VOID UartPuts(const CHAR *s, UINT32 len, BOOL isLock)
{
    uart_write(s, len, 0);
}