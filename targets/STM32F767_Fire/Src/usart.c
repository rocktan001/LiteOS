/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include <los_hwi.h>
#include "platform.h"
#include "main.h"
#include "led.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART3 init function */

void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStructure = {0};
  if(uartHandle->Instance==USART1)
  {
     /* Enable GPIOA clock */
      __HAL_RCC_GPIOA_CLK_ENABLE();
      /* Enable USART1 clock */
      __HAL_RCC_USART1_CLK_ENABLE();

      /* Configure USART1_TX (PA9) and USART1_RX (PA10) */
      GPIO_InitStructure.Pin = GPIO_PIN_9 | GPIO_PIN_10;
      GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStructure.Pull = GPIO_PULLUP;
      GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
      GPIO_InitStructure.Alternate = GPIO_AF7_USART1;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /* Configure USART1_TX (PA9) and USART1_RX (PA10) */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_9|GPIO_PIN_10);
  }
}

/* USER CODE BEGIN 1 */
VOID UsartInit(VOID) {
    MX_USART1_UART_Init();
}

VOID UsartWrite(const CHAR c)
{
    (VOID)HAL_UART_Transmit(&huart1, (UINT8 *)&c, 1, DEFAULT_TIMEOUT);
}

UINT8 UsartRead(VOID)
{
    UINT8 ch;
    Fire_LED_GREEN_ON(1);
    (VOID)HAL_UART_Receive(&huart1, &ch, sizeof(UINT8), 0);
    Fire_LED_GREEN_ON(0);
    return ch;
}

STATIC VOID UartHandler(VOID)
{
    (VOID)uart_getc();
}

INT32 UsartHwi(VOID)
{
    if (huart1.Instance == NULL) {
        return LOS_NOK;
    }
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_TC);
    (VOID)LOS_HwiCreate(NUM_HAL_INTERRUPT_UART, 0, 0, UartHandler, NULL);
    HAL_NVIC_SetPriority(USART1_IRQn, 15, 0U);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
    return LOS_OK;
}

UartControllerOps g_genericUart = {
    .uartInit = UsartInit,
    .uartWriteChar = UsartWrite,
    .uartReadChar = UsartRead,
    .uartHwiCreate = UsartHwi
};
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
