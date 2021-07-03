
/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Usart Init Implementation
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

#include "usart.h"
#include "register_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

MINIUART_INFO *miniUart;

#define GPIO_MODE_INPUT     0
#define GPIO_MODE_OUTPUT    1
#define GPIO_ALT_FUNC0      4
#define GPIO_ALT_FUNC1      5
#define GPIO_ALT_FUNC2      6
#define GPIO_ALT_FUNC3      7
#define GPIO_ALT_FUNC4      3
#define GPIO_ALT_FUNC5      2
#define GPIO_FSEL_MASK      0x7
#define MINI_UART_TX        14
#define MINI_UART_RX        15
#define PER_GPFSEL_GPIONUM  10
#define GPIO_FSEL_BITNUM    3

VOID UartInit(VOID)
{
    UINT32 value;
    GPIO_INFO * gpio = GPIO_REG_BASE;

    value = gpio->GPFSEL[1];
    value &= ~(GPIO_FSEL_MASK << ((MINI_UART_TX % PER_GPFSEL_GPIONUM) * GPIO_FSEL_BITNUM));     /* GPIO14 */
    value |= GPIO_ALT_FUNC5 << ((MINI_UART_TX % PER_GPFSEL_GPIONUM) * GPIO_FSEL_BITNUM) ;       /* ALT5 */
    value &= ~(GPIO_FSEL_MASK << ((MINI_UART_RX % PER_GPFSEL_GPIONUM) * GPIO_FSEL_BITNUM));     /* GPIO15 */
    value |= GPIO_ALT_FUNC5 << ((MINI_UART_RX % PER_GPFSEL_GPIONUM) * GPIO_FSEL_BITNUM) ;       /* ALT5 */
    gpio->GPFSEL[1] = value;

    /* PullUD disable */
    gpio->GPPUD = 0;
    gpio->GPPUDCLK[0] = (1 << MINI_UART_TX) | (1 << MINI_UART_RX); /* GPIO14, GPIO15 */
    gpio->GPPUDCLK[0] = 0;

    miniUart = MINI_UART;
    *((volatile UINT32 *)(AUX_ENABLES)) |= 1; /* mini uart enable */
    miniUart->LCR   = 3;        /* Works in 8-bit mode */
    miniUart->IER   = 0;        /* Disable interrupt */
    miniUart->CNTL  = 0;        /* Disable Transmitter and Receiver */
    miniUart->MCR   = 0;        /* Disable RTS */
    miniUart->IIR   = 0xC6;     /* Enable FIFO, Clear FIFO */
    miniUart->BAUD  = 270;      /* 115200 = system clock 250MHz / (8 * (baud + 1)), baud = 270 */
    miniUart->CNTL  = 3;        /* Enable Transmitter and Receiver */
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */