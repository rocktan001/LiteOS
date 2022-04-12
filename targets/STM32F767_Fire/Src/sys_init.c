/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: System Init Implementation
 * Author: Huawei LiteOS Team
 * Create: 2021-07-29
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

#include "sys_init.h"
#include "los_sys.h"

uint32_t HAL_GetTick(void) {
#ifdef LOSCFG_PLATFORM_STM32F767_FIRE
    extern UINT64 Hal_STM32F767_Get_Timer_CNT(VOID);
    return Hal_STM32F767_Get_Timer_CNT()/1000;
#else
    return (UINT32)LOS_TickCountGet();
#endif    
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char const *file, int line) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    (void)file;
    (void)line;
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef rccOscInitStruct = {0};
    RCC_ClkInitTypeDef rccClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure LSE Drive Capability
    */
    HAL_PWR_EnableBkUpAccess();
    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */

    rccOscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    rccOscInitStruct.HSEState = RCC_HSE_ON;
    rccOscInitStruct.PLL.PLLState = RCC_PLL_ON;
    rccOscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    rccOscInitStruct.PLL.PLLM = 25;// 4, Division factor for PLL VCO iput clock.
    rccOscInitStruct.PLL.PLLN = 432; // 216, Multiplication factor for PLL VCO output clock.
    rccOscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    rccOscInitStruct.PLL.PLLQ = 2; // 9, Division factor for
    rccOscInitStruct.PLL.PLLR = 2;


    if (HAL_RCC_OscConfig(&rccOscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Activate the Over-Drive mode
    */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    rccClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    rccClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    rccClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    rccClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    rccClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&rccClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
        Error_Handler();
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Enables the Clock Security System
    */
    HAL_RCC_EnableCSS();
}

void HAL_MspInit(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();
}

