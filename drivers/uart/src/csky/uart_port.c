
/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Uart Module Implementation
 * Author: Huawei LiteOS Team
 * Create: 2021-04-28
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

#include <los_hwi.h>
#include <los_task.h>
#include "los_queue.h"
#include "drv_usart.h"
#include "pin.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define UART_QUEUE_SIZE        64
#define UART_QUEUE_BUF_MAX_LEN 1
#define UART_QUEUE_REC_DELAY   5
#define UART_BAUDRATE          115200

STATIC UINT32 g_uartQueue;
STATIC usart_handle_t g_consoleHandle;

INT32 uart_putc(CHAR c)
{
    if (g_consoleHandle == NULL) {
        return -1;
    }
    csi_usart_putchar(g_consoleHandle, c);

    return 1;
}

UINT8 uart_getc(VOID)
{
    UINT8 ch = 0;

    if (g_consoleHandle == NULL) {
        return -1;
    }

    csi_usart_getchar(g_consoleHandle, &ch);
    (VOID)LOS_QueueWriteCopy(g_uartQueue, &ch, sizeof(UINT8), 0);
    return ch;
}

STATIC VOID UartHandler(VOID)
{
    (VOID)uart_getc();
}

INT32 ShellQueueCreat(VOID)
{
    return LOS_QueueCreate("uartQueue", UART_QUEUE_SIZE, &g_uartQueue, 0, UART_QUEUE_BUF_MAX_LEN);
}

INT32 uart_hwiCreate(VOID)
{
    (VOID)LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    LOS_HwiEnable(NUM_HAL_INTERRUPT_UART);

    return LOS_OK;
}

UINT8 uart_read(VOID)
{
    UINT8 rec = 0;
    UINT32 ret;
    UINT32 len;
    len = UART_QUEUE_BUF_MAX_LEN;
    ret = LOS_QueueReadCopy(g_uartQueue, &rec, &len, LOS_WAIT_FOREVER);
    if (ret == LOS_OK) {
        LOS_TaskDelay(UART_QUEUE_REC_DELAY);
        return rec;
    }
    return rec;
}

INT32 uart_write(const CHAR *buf, INT32 len, INT32 timeout)
{
    (VOID)timeout;
    for (int i = 0; i < len; i++) {
        uart_putc(buf[i]);
    }
    return len;
}

VOID UartPuts(const CHAR *s, UINT32 len, BOOL isLock)
{
    UINT32 i;
    if (s == NULL) {
        return;
    }
    for (i = 0; i < len; i++) {
        /*
         * Only system uart output needs to add extra '\r' to improve
         * the compatibility.
         */
        if (*(s + i) == '\n') {
            uart_putc('\r');
        }
        uart_putc(*(s + i));
    }
}

void uart_early_init(void)
{
    drv_pinmux_config(CONSOLE_TXD, CONSOLE_TXD_FUNC);
    drv_pinmux_config(CONSOLE_RXD, CONSOLE_RXD_FUNC);

    /* init the console */
    g_consoleHandle = csi_usart_initialize(CONSOLE_IDX, NULL);
    /* config the UART */
    csi_usart_config(g_consoleHandle, UART_BAUDRATE, USART_MODE_ASYNCHRONOUS,
                     USART_PARITY_NONE, USART_STOP_BITS_1, USART_DATA_BITS_8);
}

VOID uart_init(VOID) {
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */