/**************************************************************************//**
 * @file     system_FM33LC0XX.h
 * @brief    CMSIS Cortex-M# Device Peripheral Access Layer Header File for
 *           Device FM33LC0XX
 * @version  V1.02
 * @date     31-8-2019
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#ifndef SYSTEM_FM33LC0XX_H
#define SYSTEM_FM33LC0XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "fm33lc0xx.h"

//#define   USE_LSCLK_CLOCK_SRC_XTLF

//#define   SYSCLK_SRC_RC4M
//#define   SYSCLK_SRC_XTHF
#define   SYSCLK_SRC_RCHF
//#define   SYSCLK_SRC_PLL


//#define   USE_PLL_CLOCK_SRC_RCHF
//#define   USE_PLL_CLOCK_SRC_XTHF

#define __HAL_RCC_SYSCFG_CLK_ENABLE()
#define __HAL_SYSCFG_REMAPMEMORY_SRAM()

#if ((!defined(SYSCLK_SRC_RC4M)) && (!defined(SYSCLK_SRC_XTHF))&&(!defined(SYSCLK_SRC_PLL))&&(!defined(SYSCLK_SRC_RCHF)))
    #error "Must select a clock source form the SYSCLK_SRC_RC4M or SYSCLK_SRC_XTHF or SYSCLK_SRC_PLL or SYSCLK_SRC_RCHF as the master clock."
#elif (((defined(SYSCLK_SRC_RC4M)) && ((defined(SYSCLK_SRC_XTHF))||(defined(SYSCLK_SRC_PLL))||(defined(SYSCLK_SRC_RCHF))))||\
     ((defined(SYSCLK_SRC_XTHF)) && ((defined(SYSCLK_SRC_RC4M))||(defined(SYSCLK_SRC_PLL))||(defined(SYSCLK_SRC_RCHF))))||\
     ((defined(SYSCLK_SRC_PLL)) && ((defined(SYSCLK_SRC_XTHF))||(defined(SYSCLK_SRC_RC4M))||(defined(SYSCLK_SRC_RCHF))))||\
     ((defined(SYSCLK_SRC_RCHF)) && ((defined(SYSCLK_SRC_XTHF))||(defined(SYSCLK_SRC_PLL))||(defined(SYSCLK_SRC_RC4M)))))
    #error "Only one clock source can be selected as the master clock."
#endif

#if defined(SYSCLK_SRC_PLL) && !defined(USE_PLL_CLOCK_SRC_RCHF) && !defined(USE_PLL_CLOCK_SRC_XTHF)
    #error "You have chosen to enable the PLL, so you need to specify the clock source for the PLL.."
#elif defined(SYSCLK_SRC_PLL) && (defined(USE_PLL_CLOCK_SRC_RCHF) && defined(USE_PLL_CLOCK_SRC_XTHF))
    #error "Please select one of the USE_PLL_CLOCK_SRC_RCHF and USE_PLL_CLOCK_SRC_XTHF in your application"
#endif

#if !defined  (XTHF_VALUE)
    #define XTHF_VALUE    ((uint32_t)8000000U) /*!< Value of the External oscillator in Hz */
#endif /* XTHF_VALUE */    

#if !defined  (XTLF_VALUE)
    #define XTLF_VALUE    ((uint32_t)32768U) /*!< Value of the Internal oscillator in Hz*/
#endif /* XTLF_VALUE */         




#define __SYSTEM_CLOCK          (8000000)
#define DELAY_US                (__SYSTEM_CLOCK/1000000)
#define DELAY_MS                (__SYSTEM_CLOCK/1000)


#define Do_DelayStart()  { \
                        uint32_t LastTick = SysTick->VAL;   do {
                        
#define While_DelayMsEnd(Count) }while(((LastTick - SysTick->VAL)&0xFFFFFF)<DELAY_MS*Count); \
                      }
                      
#define While_DelayUsEnd(Count) }while(((LastTick - SysTick->VAL)&0xFFFFFF)<DELAY_US*Count); \
}            

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
void SystemCoreClockUpdate (void);


#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_FM33LC0XX_H */
