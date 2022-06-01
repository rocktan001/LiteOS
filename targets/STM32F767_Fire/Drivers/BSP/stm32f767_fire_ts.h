/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F767_FIRE_TS_H
#define __STM32F767_FIRE_TS_H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f7xx.h"
#include "main.h"

#define TS_MAX_NB_TOUCH                 ((uint32_t) 1)

#define TS_NO_IRQ_PENDING               ((uint8_t) 0)
#define TS_IRQ_PENDING                  ((uint8_t) 1)

#define GTP_ADDRESS            0xBA

#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/*I2C引脚*/
#define GTP_I2C                          I2C2
#define GTP_I2C_CLK_ENABLE()             __HAL_RCC_I2C2_CLK_ENABLE()
#define GTP_I2C_CLK_INIT         RCC_APB1PeriphClockCmd 

#define GTP_I2C_SCL_PIN                  GPIO_PIN_4                 
#define GTP_I2C_SCL_GPIO_PORT            GPIOH                       
#define GTP_I2C_SCL_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOH_CLK_ENABLE()
#define GTP_I2C_SCL_AF                   GPIO_AF4_I2C2

#define GTP_I2C_SDA_PIN                  GPIO_PIN_5                  
#define GTP_I2C_SDA_GPIO_PORT            GPIOH                     
#define GTP_I2C_SDA_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOH_CLK_ENABLE()
#define GTP_I2C_SDA_AF                   GPIO_AF4_I2C2

/*复位引脚*/
#define GTP_RST_GPIO_PORT                GPIOI
#define GTP_RST_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOI_CLK_ENABLE()
#define GTP_RST_GPIO_PIN                 GPIO_PIN_8
/*中断引脚*/
#define GTP_INT_GPIO_PORT                GPIOD
#define GTP_INT_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOD_CLK_ENABLE()
#define GTP_INT_GPIO_PIN                 GPIO_PIN_13
#define GTP_INT_EXTI_IRQ                 EXTI15_10_IRQn
  
/**
*  @brief TS_StateTypeDef
*  Define TS State structure
*/
typedef struct
{
  uint8_t  touchDetected;                /*!< Total number of active touches detected at last scan */
  uint16_t touchX[TS_MAX_NB_TOUCH];      /*!< Touch X[0], X[1] coordinates on 12 bits */
  uint16_t touchY[TS_MAX_NB_TOUCH];      /*!< Touch Y[0], Y[1] coordinates on 12 bits */

#if (TS_MULTI_TOUCH_SUPPORTED == 1)
  uint8_t  touchWeight[TS_MAX_NB_TOUCH]; /*!< Touch_Weight[0], Touch_Weight[1] : weight property of touches */
  uint8_t  touchEventId[TS_MAX_NB_TOUCH];     /*!< Touch_EventId[0], Touch_EventId[1] : take value of type @ref TS_TouchEventTypeDef */
  uint8_t  touchArea[TS_MAX_NB_TOUCH];   /*!< Touch_Area[0], Touch_Area[1] : touch area of each touch */
  uint32_t gestureId; /*!< type of gesture detected : take value of type @ref TS_GestureIdTypeDef */
#endif  /* TS_MULTI_TOUCH_SUPPORTED == 1 */

} TS_StateTypeDef;

uint8_t BSP_TS_Init(uint16_t ts_SizeX, uint16_t ts_SizeY);
uint8_t BSP_TS_GetState(TS_StateTypeDef *TS_State);
#ifdef __cplusplus
}
#endif

#endif /* __STM32F767_FIRE_TS_H */