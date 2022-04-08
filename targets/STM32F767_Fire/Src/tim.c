/* *
 * *****************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 * of the TIM instances.
 * *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 * opensource.org/licenses/BSD-3-Clause
 *
 * *****************************************************************************
 */

/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Tim
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

/* Includes ------------------------------------------------------------------ */
#include "tim.h"
#include "sys_init.h"
#include "platform.h"
/* USER CODE BEGIN 0 */
#include "los_hwi.h"
#include "led.h"

// tim3 挂载到APB1 外设时钟 108MHZ

#define TIMER3_RELOAD 50000
/* USER CODE END 0 */
TIM_HandleTypeDef htim3;

static UINT64 g_tim3_cycleTimes = 0;
/* TIM3 init function */
void MX_TIM3_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };
    /* 累计TIM_Period个后产生一个更新或者中断*/
    //定时器时钟源TIMxCLK = 2 * PCLK1  
    //              PCLK1 = HCLK / 4 
    //              => TIMxCLK=HCLK/2=SystemCoreClock/2=108MHz
    // 设定定时器频率为 = TIMxCLK/(TIM_Prescaler+1)=1000000Hz
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 108 - 1; // 5400 - 1, Set timer3 prescaler.
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 50000 - 1; // 50000 - 1, Set timer3 period.

    /* Period (50000) / TIMxCLK(10000HZ) = 5s 产生一个中断*/
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 3);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}

/* *
 * @brief This function handles TIM3 global interrupt.
 */
void TIM3_IRQHandler(void)
{
    /* USER CODE BEGIN TIM3_IRQn 0 */

    /* USER CODE END TIM3_IRQn 0 */
    // Fire_DEBUG_GPIOB6_TRIGGER(); 
    Fire_DEBUG_GPIOB7(1);
    g_tim3_cycleTimes ++;
    HAL_TIM_IRQHandler(&htim3);
    Fire_DEBUG_GPIOB7(0);
    /* USER CODE BEGIN TIM3_IRQn 1 */

    /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */
VOID TimInit(VOID)
{
    MX_TIM3_Init();
}

VOID TimerHwiCreate(VOID)
{
    UINT32 ret;

    ret = LOS_HwiCreate(TIM_IRQ, 0, 0, TIM3_IRQHandler, 0); // 16: cortex-m irq num shift
    if (ret != 0) {
        printf("ret of TIM3 LOS_HwiCreate = %#x\n", ret);
        return;
    }
    // 开启定时器中断方式更新中断
    // (VOID)HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start(&htim3);
}

/* 2022-04-07 tanzhongqiang  
    返回基础定时器CNT 值，每1us 更新一次。
*/
UINT64 Hal_STM32F767_Get_Timer_CNT(VOID)
{
    static UINT64 bacCycle = 0;
    static UINT64 cycleTimes = 0;
    if (htim3.Instance == NULL) {
        return 0;
    }

    UINT64 swCycles = htim3.Instance->CNT;

    if (swCycles < bacCycle) {
        cycleTimes++;
    }
    bacCycle = swCycles;

    return (swCycles + cycleTimes * TIMER3_RELOAD);
}

/* 
    2022-04-07 tanzhongqiang 要求返回对应SYSCLK 的cycles 。前置YSCLK 216MHZ.
*/
UINT64 GetTimerCycles(VOID)
{
/** 调用堆栈
#1  0x0800f594 in HalClockGetCycles () at cortex_m_systick.c:107
#2  0x08003c22 in LOS_GetCpuCycle (highCnt=0x2007ff78, lowCnt=0x2007ff7c) at los_tick.c:125
#3  0x08013616 in OsCpupGetCycle () at los_cpup.c:215
#4  0x08013f36 in OsCpupIrqStart () at los_cpup.c:520
#5  0x08001f62 in OsIntHandle (hwiNum=45, hwiForm=0x20002490 <g_hwiForm+720>) at los_hwi.c:123
#6  0x0800f178 in IrqEntryV7M () at arm_nvic.c:100
* */

    return Hal_STM32F767_Get_Timer_CNT() * 216;// * 1000000;
}

TimControllerOps g_cpupTimerOps = {
    .timInit = TimInit,
    .timHwiCreate = TimerHwiCreate,
    .timGetTimerCycles = GetTimerCycles,
};
/* USER CODE END 1 */

/* *********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE*** */
