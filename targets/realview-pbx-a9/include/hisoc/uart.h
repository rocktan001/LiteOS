
/*----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Hiso Uart HeaderFile
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

#ifndef _HISOC_UART_H
#define _HISOC_UART_H

#include "asm/hal_platform_ints.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
    uint32_t DR;        // data reg
    uint32_t DSR;
    uint32_t pad1[4];   // 8+16=24 bytes to FR register
    uint32_t FR;        // flag reg at 0x18
    uint32_t pad2[7];
    uint32_t IMSC;      // at offset 0x38
}uart_t;

extern void uart_early_init(void);
extern void uart_init(void);
extern void uart_handler(void);
extern char uart_fputc(char c, void *f);
extern UINT8 uart_getc(void);

extern void uprintf(const char *fmt, va_list arg);
extern void kprintf(const char *fmt, va_list arg);
extern void dprintf(const char *fmt, ...);
extern UINT32 UartPutsReg(UINTPTR base, const CHAR *s, UINT32 len, BOOL isLock);
extern VOID UartPuts(const CHAR *s, UINT32 len, BOOL isLock);

#define UART_WITHOUT_LOCK 0
#define UART_WITH_LOCK    1

#define CONFIG_UART_CLK_INPUT       24000000 //24M or 6M

#define UART0                       0
#define CONSOLE_UART                UART0

#define CONSOLE_UART_BAUDRATE       115200
#define UART_NUM                    1

#define TTY_DEVICE                  "/dev/uartdev-0"

#define uart_clk_cfg(uart_num, flag)

#ifdef __cplusplus
}
#endif
#endif
