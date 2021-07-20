/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2021. All rights reserved.
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
#include "los_task.h"
#include "los_queue.h"

#ifndef LOSCFG_PLATFORM_HIFIVE1_REV1_B01
#include "usart.h"
#else
#include "metal/tty.h"
#include "metal/machine/platform.h"
#endif /* LOSCFG_PLATFORM_HIFIVE1_REV1_B01 */

#define UART_QUEUE_SIZE        64
#define UART_QUEUE_BUF_MAX_LEN 1
#define UART_QUEUE_REC_DELAY   5

STATIC UINT32 g_uartQueue;

INT32 uart_putc(CHAR c)
{
    return uart_write(&c, 1, 0);
}

UINT8 uart_getc(VOID)
{
    UINT8 ch = 0;
#if defined(LOSCFG_PLATFORM_STM32L4R9I_DISCOVERY) || defined(LOSCFG_PLATFORM_STM32L073_NUCLEO)
    HAL_UART_Receive(&huart2, &ch, sizeof(UINT8), 0);
#elif defined(LOSCFG_PLATFORM_STM32L496_NUCLEO) || defined(LOSCFG_PLATFORM_STM32L552_NUCLEO)
    HAL_UART_Receive(&hlpuart1, &ch, sizeof(UINT8), 0);
#elif defined(LOSCFG_PLATFORM_GD32F303RGT6_BEARPI)
    if (usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE) == RESET) {
        return ch;
    }
    ch = (UINT8)(usart_data_receive(USART0) & 0xFF);
#elif defined(LOSCFG_PLATFORM_GD32E103C_START)
    if (usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE) == RESET) {
        return ch;
    }
    ch = (UINT8)(usart_data_receive(USART1) & 0xFF);
#elif defined(LOSCFG_PLATFORM_GD32VF103V_EVAL)
    if (usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE) == RESET) {
        return ch;
    }
    ch = (UINT8)usart_data_receive(USART0);
#elif defined(LOSCFG_PLATFORM_HIFIVE1_REV1_B01)
        INT32 tmp;
        metal_tty_getc(&tmp);
        ch =  (UINT8)tmp;
#elif defined(LOSCFG_PLATFORM_FM33LC0XX_DEMO)
	(VOID)HAL_UART_Receive(UART5, &ch, sizeof(UINT8), 0);
#elif defined (LOSCFG_FAMILY_RASPBERRY)
    if (miniUart->LSR & UART_RXREADY_FLAG) {
        ch = (UINT8)(miniUart->IO & 0xff);
    }
#elif defined(LOSCFG_PLATFORM_STM32F746_NUCLEO)
    (VOID)HAL_UART_Receive(&huart3, &ch, sizeof(UINT8), 0);
#else
    (VOID)HAL_UART_Receive(&huart1, &ch, sizeof(UINT8), 0);
#endif
    (VOID)LOS_QueueWriteCopy(g_uartQueue, &ch, sizeof(UINT8), 0);
    return ch;
}

STATIC VOID UartHandler(VOID)
{
    (VOID)uart_getc();
}

INT32 ShellQueueCreat(VOID)
{
    return (INT32)LOS_QueueCreate("uartQueue", UART_QUEUE_SIZE, &g_uartQueue, 0, UART_QUEUE_BUF_MAX_LEN);
}

INT32 uart_hwiCreate(VOID)
{
#if defined(LOSCFG_PLATFORM_STM32L4R9I_DISCOVERY) || defined(LOSCFG_PLATFORM_STM32L073_NUCLEO)
    if (huart2.Instance == NULL) {
        return LOS_NOK;
    }
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    __HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_TC);
    (VOID)LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
#elif defined(LOSCFG_PLATFORM_STM32L496_NUCLEO) || defined(LOSCFG_PLATFORM_STM32L552_NUCLEO)
    if (hlpuart1.Instance == NULL) {
        return LOS_NOK;
    }
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
    __HAL_UART_CLEAR_FLAG(&hlpuart1, UART_FLAG_TC);
    (VOID)LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    __HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_RXNE);
#elif defined(LOSCFG_PLATFORM_GD32F303RGT6_BEARPI)
    nvic_irq_enable(USART0_IRQn, 0, 0);
    usart_flag_clear(USART0, USART_INT_RBNE);
    LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    usart_interrupt_enable(USART0, USART_INT_RBNE);
#elif defined(LOSCFG_PLATFORM_GD32E103C_START)
    nvic_irq_enable(USART1_IRQn, 0, 0);
    usart_flag_clear(USART1, USART_INT_RBNE);
    LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    usart_interrupt_enable(USART1, USART_INT_RBNE);
#elif defined(LOSCFG_PLATFORM_GD32VF103V_EVAL)
    eclic_enable_interrupt(USART0_IRQn);
    LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    usart_interrupt_enable(USART0, USART_INT_RBNE);
#elif defined(LOSCFG_PLATFORM_HIFIVE1_REV1_B01)
    LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 1, 0, UartHandler, NULL);
    LOS_HwiEnable(NUM_HAL_INTERRUPT_UART);
    *(UINT32 volatile *)(METAL_SIFIVE_UART0_10013000_BASE_ADDRESS + METAL_SIFIVE_UART0_IE) |= (1 << 1);
#elif defined(LOSCFG_PLATFORM_FM33LC0XX_DEMO)
    NVIC_DisableIRQ(UART5_IRQn);
    NVIC_SetPriority(UART5_IRQn, 1);
    NVIC_EnableIRQ(UART5_IRQn);
    LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 1, 0, UartHandler, NULL);
    LOS_HwiEnable(NUM_HAL_INTERRUPT_UART);
#elif defined (LOSCFG_FAMILY_RASPBERRY)
    LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    miniUart->IIR = 0x1;
    if (miniUart->LSR & UART_RXREADY_FLAG) {
        (VOID)(miniUart->IO & 0xff); /* Clear Uart Rx Irq */
    }
    LOS_HwiEnable(NUM_HAL_INTERRUPT_UART);
#elif defined(LOSCFG_PLATFORM_STM32F746_NUCLEO)
    if (huart3.Instance == NULL) {
        return LOS_NOK;
    }
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    __HAL_UART_CLEAR_FLAG(&huart3, UART_FLAG_TC);
    (VOID)LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
#else
    if (huart1.Instance == NULL) {
        return LOS_NOK;
    }
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_TC);
    (VOID)LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
#endif
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
        (VOID)LOS_TaskDelay(UART_QUEUE_REC_DELAY);
        return rec;
    }
    return rec;
}

INT32 uart_write(const CHAR *buf, INT32 len, INT32 timeout)
{
    (VOID)timeout;
#if defined(LOSCFG_PLATFORM_STM32F072_Nucleo) || defined(LOSCFG_PLATFORM_STM32L4R9I_DISCOVERY) || \
    defined(LOSCFG_PLATFORM_STM32L073_NUCLEO)
    (VOID)HAL_UART_Transmit(&huart2, (UINT8 *)buf, len, DEFAULT_TIMEOUT);
#elif defined(LOSCFG_PLATFORM_STM32L496_NUCLEO) || defined(LOSCFG_PLATFORM_STM32L552_NUCLEO)
    (VOID)HAL_UART_Transmit(&hlpuart1, (UINT8 *)buf, len, DEFAULT_TIMEOUT);
#elif defined(LOSCFG_PLATFORM_GD32F303RGT6_BEARPI)
    if (len == 1) {
        while (usart_flag_get(USART0, USART_FLAG_TBE) == 0) {}
        usart_data_transmit(USART0, *buf);
    }
#elif defined (LOSCFG_PLATFORM_GD32E103C_START)
    if (len == 1) {
        while (usart_flag_get(USART1, USART_FLAG_TBE) == 0) {}
        usart_data_transmit(USART1, *buf);
    }
#elif defined (LOSCFG_PLATFORM_GD32VF103V_EVAL)
    INT32 i;
    for (i = 0; i < len; i++) {
        usart_data_transmit(USART0, *buf);
        while (RESET == usart_flag_get(USART0, USART_FLAG_TBE)) { }
        buf++;
    }
#elif defined(LOSCFG_PLATFORM_HIFIVE1_REV1_B01)
    INT32 i;
    for (i = 0; i < len; i++) {
        metal_tty_putc(buf[i]);
    }
#elif defined(LOSCFG_PLATFORM_FM33LC0XX_DEMO)
    HAL_UART_Transmit(UART5, (VOID *)buf, len, DEFAULT_TIMEOUT);
#elif defined (LOSCFG_FAMILY_RASPBERRY)
    UINT32 i;
    for (i = 0; i < len; i++) {
        while(!(miniUart->LSR & UART_TXEMPTY_FLAG)) {};
        miniUart->IO = buf[i];
    }
#elif defined(LOSCFG_PLATFORM_STM32F746_NUCLEO)
    (VOID)HAL_UART_Transmit(&huart3, (UINT8 *)buf, (UINT16)len, DEFAULT_TIMEOUT);
#else
    (VOID)HAL_UART_Transmit(&huart1, (UINT8 *)buf, (UINT16)len, DEFAULT_TIMEOUT);
#endif
    return len;
}

VOID UartPuts(const CHAR *s, UINT32 len, BOOL isLock)
{
    UINT32 i;
    (VOID)isLock;
    if (s == NULL) {
        return;
    }
    for (i = 0; i < len; i++) {
        /*
         * Only system uart output needs to add extra '\r' to improve
         * the compatibility.
         */
        if (*(s + i) == '\n') {
            (VOID)uart_putc('\r');
        }
        (VOID)uart_putc(*(s + i));
    }
}

VOID uart_init(VOID) {}
