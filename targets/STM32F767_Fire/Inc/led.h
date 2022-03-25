#ifndef __LED__H__
#define __LED__H__
void Fire_LED_GPIO_Config(void);
void Fire_LED_RED_ON(int on);
void Fire_LED_GREEN_ON(int on);
void Fire_LED_BLUE_ON(int on);
void Fire_DEBUG_GPIOB6(int on);
void Fire_DEBUG_GPIOB7(int on);
void Fire_DEBUG_GPIOB6_TRIGGER(void);
void Fire_DEBUG_GPIOB7_TRIGGER(void);
#endif