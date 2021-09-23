/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description : Pl011 uart implementation
 * Author : Huawei LiteOS Team
 * Create : 2021-01-01
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

#include "hisoc/uart.h"
#include "los_printf.h"
#include "los_base.h"
#include "los_spinlock.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define UART_DR                         0x0   /* data register */
#define UART_RSR                        0x04  /* recv status register */
#define UART_FR                         0x18  /* flag register */
#define UART_CLR                        0x44  /* interrupt clear register */
#define UART_CR                         0x30  /* control register */
#define UART_IBRD                       0x24  /* interger baudrate register */
#define UART_FBRD                       0x28  /* decimal baudrate register */
#define UART_LCR_H                      0x2C
#define UART_IFLS                       0x34  /* fifo register */
#define UART_IMSC                       0x38  /* interrupt mask register */
#define UART_RIS                        0x3C  /* base interrupt state register */
#define UART_MIS                        0x40  /* mask interrupt state register */
#define UART_ICR                        0x44
#define UART_DMACR                      0x48  /* DMA control register */

#define UART_IFLS_RX1_8                 (0x00U << 3)
#define UART_IFLS_RX4_8                 (0x02U << 3)
#define UART_IFLS_RX7_8                 (0x04U << 3)
#define UART_IFLS_TX1_8                 (0x00U << 0)
#define UART_IFLS_TX4_8                 (0x02U << 0)
#define UART_IFLS_TX7_8                 (0x04U << 0)

#define UART_CR_CTS                     (0x01U <<15)
#define UART_CR_RTS                     (0x01U <<14)
#define UART_CR_RX_EN                   (0x01U << 9)
#define UART_CR_TX_EN                   (0x01U << 8)
#define UART_CR_LOOPBACK                (0x01U << 7)
#define UART_CR_EN                      (0x01U << 0)

#define UART_FR_TXFE                    (0x01U << 7)
#define UART_FR_RXFF                    (0x01U << 6)
#define UART_FR_TXFF                    (0x01U << 5)
#define UART_FR_RXFE                    (0x01U << 4)
#define UART_FR_BUSY                    (0x01U << 3)

#define UART_LCR_H_BREAK                (0x01U << 0)
#define UART_LCR_H_PEN                  (0x01U << 1)
#define UART_LCR_H_EPS                  (0x01U << 2)
#define UART_LCR_H_STP2                 (0x01U << 3)
#define UART_LCR_H_FIFO_EN              (0x01U << 4)
#define UART_LCR_H_8_BIT                (0x03U << 5)
#define UART_LCR_H_7_BIT                (0x02U << 5)
#define UART_LCR_H_6_BIT                (0x01U << 5)
#define UART_LCR_H_5_BIT                (0x00U << 5)
#define UART_LCR_H_SPS                  (0x01U << 7)

#define UART_RXDMAE                     (0x01U << 0)
#define UART_TXDMAE                     (0x01U << 1)

#define UART_MIS_OVER                   (0x01U << 10)
#define UART_MIS_TIMEOUT                (0x01U << 6)
#define UART_MIS_TX                     (0x01U << 5)
#define UART_MIS_RX                     (0x01U << 4)

#define UART_IMSC_OVER                  (0x01U << 10)
#define UART_IMSC_BREAK                 (0x01U << 9)
#define UART_IMSC_CHK                   (0x01U << 8)
#define UART_IMSC_ERR                   (0x01U << 7)
#define UART_IMSC_TIMEOUT               (0x01U << 6)
#define UART_IMSC_TX                    (0x01U << 5)
#define UART_IMSC_RX                    (0x01U << 4)

#define UART_DMACR_RX                   (0x01U << 0)
#define UART_DMACR_TX                   (0x01U << 1)
#define UART_DMACR_ONERR                (0x01U << 2)
#define UART_INFO                       (0x01U << 1)
#define UART_CLEAR_ALL_INTER            0xFFFF

#ifdef LOSCFG_SERIAL_OUTPUT_ENABLE
STATIC UINT32 g_uartPutcEn = 1;
#else
STATIC UINT32 g_uartPutcEn = 0;
#endif

#define REG32(addr)                     ((volatile UINT32 *)(UINTPTR)(addr))
#define UARTREG(base, reg)              (*REG32((base) + (reg)))

STATIC VOID UartPutcReg(UINTPTR base, CHAR c)
{
    UINT32 cycle = 10000;           /* 10000: wait cpu cycles */

    /* Spin while fifo is full */
    while ((UARTREG(base, UART_FR) & UART_FR_TXFF) && (cycle != 0)) {
        cycle--;
    }
    UARTREG(base, UART_DR) = c;
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
        if ((*(s + i) == '\n') && (base == UART_REG_BASE))  {
            UartPutcReg(base, '\r');
        }
        UartPutcReg(base, *(s + i));
    }
}

STATIC UINT32 UartPutsReg(UINTPTR base, const CHAR *s, UINT32 len, BOOL isLock)
{
    UINT32 intSave;

    if (g_uartPutcEn == 0) {
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
    (VOID)UartPutsReg(UART_REG_BASE, s, len, isLock);
}

VOID UartInit(VOID)
{
    UINT32 baudRate;
    UINT32 divider;
    UINT32 remainder;
    UINT32 fraction;

    /* First, disable everything */
    WRITE_UINT32(0x0, UART_REG_BASE + UART_CR);

    /* set Scale factor of baud rate */
    baudRate = 16 * CONSOLE_UART_BAUDRATE;                 /* 16: division factors for integer baud rate */
    divider = CONFIG_UART_CLK_INPUT / baudRate;
    remainder = CONFIG_UART_CLK_INPUT % baudRate;
    baudRate = (8 * remainder) / CONSOLE_UART_BAUDRATE;    /* 8: division factors for fraction baud rate */
    fraction = (baudRate >> 1) + (baudRate & 1);

    WRITE_UINT32(divider, UART_REG_BASE + UART_IBRD);
    WRITE_UINT32(fraction, UART_REG_BASE + UART_FBRD);

    /* Set the UART to be 8 bits, 1 stop bit, no parity, fifo enabled. */
    WRITE_UINT32(UART_LCR_H_8_BIT | UART_LCR_H_FIFO_EN, UART_REG_BASE + UART_LCR_H);

    /* set the fifo threshold of recv interrupt >= 1/8 full */
    WRITE_UINT32(UART_IFLS_RX4_8 | UART_IFLS_TX7_8, UART_REG_BASE + UART_IFLS);

    /* set nonblock of recv interrupt and recv timeout interrupt */
    WRITE_UINT32(UART_IMSC_RX | UART_IMSC_TIMEOUT, UART_REG_BASE + UART_IMSC);

    /* enable the UART */
    WRITE_UINT32(UART_CR_EN | UART_CR_TX_EN | UART_CR_RX_EN, UART_REG_BASE + UART_CR);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
