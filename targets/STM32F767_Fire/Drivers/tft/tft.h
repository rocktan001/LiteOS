/**
 * @file disp.h
 *
 */

#ifndef DISP_H
#define DISP_H

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define TFT_HOR_RES     STM32F767_FIRE_LCD_PIXEL_WIDTH
#define TFT_VER_RES     STM32F767_FIRE_LCD_PIXEL_HEIGHT
#define TFT_NO_TEARING  0   /*1: no tearing but slower*/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void tft_init(void);

/**********************
 *      MACROS
 **********************/

#endif