/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Main
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

#include "main.h"
#include "dma2d.h"
#include "los_task_pri.h"
#include "arch/canary.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "fmc.h"
#ifdef HAL_RNG_MODULE_ENABLED
#include "hal_rng.h"
#endif
#include "led.h"
#include "stm32f767_fire_lcd.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// uint32_t pbuff[(32*1024*1024)/4] __attribute__((at(0xD0000000)));
/* USER CODE END 0 */

VOID BoardConfig(VOID)
{
    g_sys_mem_addr_end = __LOS_HEAP_ADDR_END__;
}

INT32 HardwareInit(VOID)
{
    (VOID)HAL_Init();
    SystemClock_Config();
    TimInit();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_FMC_Init();
    MX_DMA2D_Init();

#if 0    
    BSP_LCD_DisplayOn();
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(1);
    BSP_LCD_Clear(0);
    BSP_LCD_SelectLayer(0);
    BSP_LCD_Clear(0);
    BSP_LCD_SetTextColor(0xff0000);
    // BSP_LCD_FillRect(0,0,400,400);
    // BSP_LCD_SetLayerVisible(0, ENABLE);
    BSP_LCD_DisplayChar(100,100,'h');
#endif

    return 0;
}


/**
  * @brief  The application entry point.
  * @retval int
  */
INT32 main (VOID)
{
#ifdef __GNUC__
    ArchStackGuardInit();
#endif
    OsSetMainTask();
    OsCurrTaskSet(OsGetMainTask());

    BoardConfig();
    (VOID)HardwareInit();

    PRINT_RELEASE("\n********Hello Huawei LiteOS********\n"
                  "\nLiteOS Kernel Version : %s\n"
                  "build date : %s %s\n\n"
                  "**********************************\n",
                  HW_LITEOS_KERNEL_VERSION_STRING, __DATE__, __TIME__);

    UINT32 ret = OsMain();
    if (ret != LOS_OK) {
        return LOS_NOK;
    }

    OsStart();

    return LOS_OK;
}