/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Amba Pl011 Uart Driver
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

#include "amba_pl011.h"
#include "asm/platform.h"
#include "los_hwi.h"
#include "los_spinlock.h"
#include "los_event.h"
#include "los_task_pri.h"
#include "menuconfig.h"
#include "uart.h"

EVENT_CB_S g_stShellEvent;

CHAR g_inputCmd[CMD_LENGTH];
INT32 g_inputIdx = 0;

#ifdef LOSCFG_SERIAL_OUTPUT_ENABLE
UINT32 g_uart_fputc_en = 1;
#else
UINT32 g_uart_fputc_en = 0;
#endif

#define REG32(addr)         ((volatile UINT32 *)(UINTPTR)(addr))
#define UARTREG(base, reg)  (*REG32((base) + (reg)))
#define UART_FR_TXFF        (0x1U << 5)
#define UART_EVENT_MASK     0x1

static UINT8 g_uart_rec = 0;

STATIC VOID UartPutcReg(UINTPTR base, CHAR c)
{
    /* Spin while fifo is full */
    while (UARTREG(base, UART_FR) & UART_FR_TXFF) {
        ;
    }
    UARTREG(base, UART_DR) = c;
}

STATIC INLINE UINTPTR uart_to_ptr(UINTPTR n)
{
    (VOID)n;
    return UART_REG_BASE;
}

INT32 uart_putc(CHAR c)
{
    UINTPTR base = uart_to_ptr(0);
    UartPutcReg(base, c);
    return 1;
}

CHAR uart_fputc(CHAR c, VOID *f)
{
    (VOID)f;
    if (g_uart_fputc_en == 1) {
        if (c == '\n') {
            (VOID)uart_putc('\r');
        }
        return (uart_putc(c));
    } else {
        return 0;
    }
}

LITE_OS_SEC_BSS STATIC SPIN_LOCK_INIT(g_uartOutputSpin);

STATIC VOID UartPutStr(UINTPTR base, const CHAR *s, UINT32 len)
{
    UINT32 i;

    for (i = 0; i < len; i++) {
        /*
         * Only system uart output needs to add extra '\r' to improve
         * the compatibility on win.
         */
        if ((*(s + i) == '\n') && (base == UART_REG_BASE)) {
            UartPutcReg(base, '\r');
        }
        UartPutcReg(base, *(s + i));
    }
}

UINT32 UartPutsReg(UINTPTR base, const CHAR *s, UINT32 len, BOOL isLock)
{
    UINT32 intSave;

    if (g_uart_fputc_en == 0) {
        return 0;
    }

    if (isLock) {
        LOS_SpinLockSave(&g_uartOutputSpin, &intSave);
        UartPutStr(base, s, len);
        LOS_SpinUnlockRestore(&g_uartOutputSpin, intSave);
    } else {
        UartPutStr(base, s, len);
    }

    return len;
}

VOID UartPuts(const CHAR *s, UINT32 len, BOOL isLock)
{
    UINTPTR base = uart_to_ptr(0);
    (VOID)UartPutsReg(base, s, len, isLock);
}

UINT8 uart_getc(void)
{
    UINT8 ch = 0;
    UINTPTR base = UART_REG_BASE;

    UINT32 status;
    READ_UINT32(status, base + UART_FR);
    /* Wait until there is data in the FIFO */
    while (status & 0x10) {
        READ_UINT32(status, base + UART_FR);
        (VOID)LOS_TaskDelay(1);
    }

    READ_UINT8(ch, base + UART_DR);

    return ch;
}

INT32 uart_puts(const CHAR *s, UINTPTR len, VOID *state)
{
    (VOID)state;
    UINTPTR i;

    for (i = 0; i < len; i++) {
        if (*(s + i) != '\0') {
            if (*(s + i) == '\n') {
                (VOID)uart_fputc('\r', NULL);
            }

            (VOID)uart_fputc(*(s + i), NULL);
        }
    }

    return (INT32)len;
}

UINT32 uart_wait_adapt(VOID)
{
    UINT32 ret;
    ret = LOS_EventRead(&g_stShellEvent, UART_EVENT_MASK, LOS_WAITMODE_AND | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER);
    if (ret == UART_EVENT_MASK) {
        return LOS_OK;
    }

    return LOS_NOK;
}

UINT8 uart_read(VOID)
{
    UINT8 ch = 0;
    if (uart_wait_adapt() == LOS_OK) {
        ch = g_uart_rec;
        return ch;
    }
    return ch;
}

INT32 uart_write(const CHAR *buf, INT32 len, INT32 timeout)
{
    uart_puts(buf, len, &timeout);
    return len;
}

VOID uart_handler(VOID)
{
    UINTPTR base = uart_to_ptr(0);
    g_uart_rec = UARTREG(base, UART_DR);
    LOS_EventWrite(&g_stShellEvent, 0x1);
}

VOID uart_early_init(VOID)
{
    /* enable uart transmit */
    UARTREG(UART_REG_BASE, UART_CR) = (1 << 8) | (1 << 0);
}

INT32 uart_hwiCreate(VOID)
{
    UINT32 ret;
    LOS_EventInit(&g_stShellEvent);
    /* uart interrupt priority should be the highest in interrupt preemption mode */
    ret = LOS_HwiCreate(NUM_HAL_INTERRUPT_UART_PBX, 0, 0, (HWI_PROC_FUNC)uart_handler, NULL);
    if (ret != LOS_OK) {
        PRINT_ERR("%s,%d, uart interrupt created error:%x\n", __FUNCTION__, __LINE__, ret);
    } else {
        /* clear all irqs */
        UARTREG(UART_REG_BASE, UART_ICR) = 0x3ff;

        /* set fifo trigger level */
        UARTREG(UART_REG_BASE, UART_IFLS) = 0;

        /* enable rx interrupt */
        UARTREG(UART_REG_BASE, UART_IMSC) = (1 << 4 | 1 << 6);

        /* enable receive */
        UARTREG(UART_REG_BASE, UART_CR) |= (1 << 9);

        HalIrqUnmask(NUM_HAL_INTERRUPT_UART_PBX);
    }
    return ret;
}

VOID uart_init(VOID) {}
