#include "stm32f7xx.h"
#include "stm32f7xx_hal_gpio.h"

#define ON  GPIO_PIN_RESET
#define OFF GPIO_PIN_SET

//R 红色灯
#define LED_RED_PIN                  GPIO_PIN_10
#define LED_RED_GPIO_PORT            GPIOH
#define LED_RED_GPIO_CLK_ENABLE()    __GPIOH_CLK_ENABLE()
//G 绿色灯
#define LED_GREEN_PIN                  GPIO_PIN_11
#define LED_GREEN_GPIO_PORT            GPIOH
#define LED_GREEN_GPIO_CLK_ENABLE()    __GPIOH_CLK_ENABLE()

//B 蓝色灯
#define LED_BLUE_PIN                  GPIO_PIN_12                 
#define LED_BLUE_GPIO_PORT            GPIOH                       
#define LED_BLUE_GPIO_CLK_ENABLE()    __GPIOH_CLK_ENABLE()

void Fire_LED_RED_ON(int on)
{
    HAL_GPIO_WritePin(LED_RED_GPIO_PORT,LED_RED_PIN,!on);
}

void Fire_LED_GREEN_ON(int on)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO_PORT,LED_GREEN_PIN,!on);
}

void Fire_LED_BLUE_ON(int on)
{

	HAL_GPIO_WritePin(LED_BLUE_GPIO_PORT,LED_BLUE_PIN,!on);
}

void Fire_DEBUG_GPIOB6_TRIGGER(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
}

void Fire_DEBUG_GPIOB7_TRIGGER(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
}

void Fire_DEBUG_GPIOA4_TRIGGER(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
}
void Fire_DEBUG_GPIOI7_TRIGGER(void)
{
    // HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_7);
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_7, 1);
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_7, 0);
}

void Fire_DEBUG_GPIOI7(int on)
{
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_7, on);

}
void Fire_DEBUG_GPIOA4(int on)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, on);
}

void Fire_DEBUG_GPIOB6(int on)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, on);
}

void Fire_DEBUG_GPIOB7(int on)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, on);
}

void Fire_LED_GPIO_Config(void)
{		
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef  GPIO_InitStruct;

    /*开启LED相关的GPIO外设时钟*/
    LED_RED_GPIO_CLK_ENABLE();
    LED_GREEN_GPIO_CLK_ENABLE();

    /*选择要控制的GPIO引脚*/															   
    GPIO_InitStruct.Pin = LED_RED_PIN;	

    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  

    /*设置引脚为上拉模式*/
    GPIO_InitStruct.Pull  = GPIO_PULLUP;

    /*设置引脚速率为高速 */   
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH; 

    /*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
    HAL_GPIO_Init(LED_RED_GPIO_PORT, &GPIO_InitStruct);	

   /*选择要控制的GPIO引脚*/                                                            
    GPIO_InitStruct.Pin = LED_GREEN_PIN; 
    HAL_GPIO_Init(LED_GREEN_GPIO_PORT, &GPIO_InitStruct);  

    GPIO_InitStruct.Pin = LED_BLUE_PIN; 
    HAL_GPIO_Init(LED_BLUE_GPIO_PORT, &GPIO_InitStruct); 

    Fire_LED_RED_ON(0);
    Fire_LED_GREEN_ON(0);  
    Fire_LED_BLUE_ON(0);  
		
}

