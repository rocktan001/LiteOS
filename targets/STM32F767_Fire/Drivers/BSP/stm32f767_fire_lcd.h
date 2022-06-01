#ifndef __STM32F767_FIRE_LCD_H
#define __STM32F767_FIRE_LCD_H


/* Define to prevent recursive inclusion -------------------------------------*/


#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "../../Utilities/Fonts/fonts.h"
#include "main.h"

#define STM32F767_FIRE_LCD_PIXEL_WIDTH 800
#define STM32F767_FIRE_LCD_PIXEL_HEIGHT 480
#define LTDC_BL_GPIO_PIN_Pin GPIO_PIN_7
#define LTDC_BL_GPIO_PIN_GPIO_Port GPIOD

#define LCD_LayerCfgTypeDef    LTDC_LayerCfgTypeDef
/** 
  * @brief  LCD FB_StartAddress  
  */
#define LCD_FB_START_ADDRESS       ((uint32_t)0xD0000000)
   
/** @brief Maximum number of LTDC layers
 */
#define LTDC_MAX_LAYER_NUMBER             ((uint32_t) 2)

/** @brief LTDC Background layer index
 */
#define LTDC_ACTIVE_LAYER_BACKGROUND      ((uint32_t) 0)

/** @brief LTDC Foreground layer index
 */
#define LTDC_ACTIVE_LAYER_FOREGROUND      ((uint32_t) 1)

/** @brief Number of LTDC layers
 */
#define LTDC_NB_OF_LAYERS                 ((uint32_t) 2)

/** @brief LTDC Default used layer index
 */
#define LTDC_DEFAULT_ACTIVE_LAYER         LTDC_ACTIVE_LAYER_FOREGROUND

/**
  * @brief  LCD color definitions values
  * in ARGB8888 format.
  */

/** @brief Blue value in ARGB8888 format
 */
#define LCD_COLOR_BLUE          ((uint32_t) 0xFF0000FF)

/** @brief Green value in ARGB8888 format
 */
#define LCD_COLOR_GREEN         ((uint32_t) 0xFF00FF00)

/** @brief Red value in ARGB8888 format
 */
#define LCD_COLOR_RED           ((uint32_t) 0xFFFF0000)

/** @brief Cyan value in ARGB8888 format
 */
#define LCD_COLOR_CYAN          ((uint32_t) 0xFF00FFFF)

/** @brief Magenta value in ARGB8888 format
 */
#define LCD_COLOR_MAGENTA       ((uint32_t) 0xFFFF00FF)

/** @brief Yellow value in ARGB8888 format
 */
#define LCD_COLOR_YELLOW        ((uint32_t) 0xFFFFFF00)

/** @brief Light Blue value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTBLUE     ((uint32_t) 0xFF8080FF)

/** @brief Light Green value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTGREEN    ((uint32_t) 0xFF80FF80)

/** @brief Light Red value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTRED      ((uint32_t) 0xFFFF8080)

/** @brief Light Cyan value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTCYAN     ((uint32_t) 0xFF80FFFF)

/** @brief Light Magenta value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTMAGENTA  ((uint32_t) 0xFFFF80FF)

/** @brief Light Yellow value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTYELLOW   ((uint32_t) 0xFFFFFF80)

/** @brief Dark Blue value in ARGB8888 format
 */
#define LCD_COLOR_DARKBLUE      ((uint32_t) 0xFF000080)

/** @brief Light Dark Green value in ARGB8888 format
 */
#define LCD_COLOR_DARKGREEN     ((uint32_t) 0xFF008000)

/** @brief Light Dark Red value in ARGB8888 format
 */
#define LCD_COLOR_DARKRED       ((uint32_t) 0xFF800000)

/** @brief Dark Cyan value in ARGB8888 format
 */
#define LCD_COLOR_DARKCYAN      ((uint32_t) 0xFF008080)

/** @brief Dark Magenta value in ARGB8888 format
 */
#define LCD_COLOR_DARKMAGENTA   ((uint32_t) 0xFF800080)

/** @brief Dark Yellow value in ARGB8888 format
 */
#define LCD_COLOR_DARKYELLOW    ((uint32_t) 0xFF808000)

/** @brief White value in ARGB8888 format
 */
#define LCD_COLOR_WHITE         ((uint32_t) 0xFFFFFFFF)

/** @brief Light Gray value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTGRAY     ((uint32_t) 0xFFD3D3D3)

/** @brief Gray value in ARGB8888 format
 */
#define LCD_COLOR_GRAY          ((uint32_t) 0xFF808080)

/** @brief Dark Gray value in ARGB8888 format
 */
#define LCD_COLOR_DARKGRAY      ((uint32_t) 0xFF404040)

/** @brief Black value in ARGB8888 format
 */
#define LCD_COLOR_BLACK         ((uint32_t) 0xFF000000)

/** @brief Brown value in ARGB8888 format
 */
#define LCD_COLOR_BROWN         ((uint32_t) 0xFFA52A2A)

/** @brief Orange value in ARGB8888 format
 */
#define LCD_COLOR_ORANGE        ((uint32_t) 0xFFFFA500)

/** @brief Transparent value in ARGB8888 format
 */
#define LCD_COLOR_TRANSPARENT   ((uint32_t) 0xFF000000)

/**
  * @brief LCD default font
  */
#define LCD_DEFAULT_FONT        Font24

/**
  * @}
  */

/** @defgroup STM32F769I_DISCOVERY_LCD_Exported_Types STM32F769I DISCOVERY LCD Exported Types
  * @{
  */

/**
* @brief  LCD Drawing main properties
*/
typedef struct
{
  uint32_t TextColor; /*!< Specifies the color of text */
  uint32_t BackColor; /*!< Specifies the background color below the text */
  sFONT    *pFont;    /*!< Specifies the font used for the text */

} LCD_DrawPropTypeDef;

/**
  * @brief  LCD Drawing point (pixel) geometric definition
  */
typedef struct
{
  int16_t X; /*!< geometric X position of drawing */
  int16_t Y; /*!< geometric Y position of drawing */

} Point;

/**
  * @brief  Pointer on LCD Drawing point (pixel) geometric definition
  */
typedef Point * pPoint;

/**
  * @brief  LCD drawing Line alignment mode definitions
  */
typedef enum
{
  CENTER_MODE             = 0x01,    /*!< Center mode */
  RIGHT_MODE              = 0x02,    /*!< Right mode  */
  LEFT_MODE               = 0x03     /*!< Left mode   */

} Text_AlignModeTypdef;


/**
 *  @brief LCD_OrientationTypeDef
 *  Possible values of Display Orientation
 */
typedef enum
{
  LCD_ORIENTATION_PORTRAIT  = 0x00, /*!< Portrait orientation choice of LCD screen  */
  LCD_ORIENTATION_LANDSCAPE = 0x01, /*!< Landscape orientation choice of LCD screen */
  LCD_ORIENTATION_INVALID   = 0x02  /*!< Invalid orientation choice of LCD screen   */
} LCD_OrientationTypeDef;

void __CopyBuffer(const uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize);
uint8_t  BSP_LCD_Init(void);

uint32_t BSP_LCD_GetXSize(void);
uint32_t BSP_LCD_GetYSize(void);
void     BSP_LCD_SetXSize(uint32_t imageWidthPixels);
void     BSP_LCD_SetYSize(uint32_t imageHeightPixels);

void     BSP_LCD_LayerDefaultInit(uint16_t LayerIndex, uint32_t FB_Address);
void     BSP_LCD_SetTransparency(uint32_t LayerIndex, uint8_t Transparency);
void     BSP_LCD_SetLayerAddress(uint32_t LayerIndex, uint32_t Address);
void     BSP_LCD_SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue);
void     BSP_LCD_ResetColorKeying(uint32_t LayerIndex);
void     BSP_LCD_SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);

void     BSP_LCD_SelectLayer(uint32_t LayerIndex);
void     BSP_LCD_SetLayerVisible(uint32_t LayerIndex, FunctionalState State);

void     BSP_LCD_SetTextColor(uint32_t Color);

void     BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t pixel);

void     BSP_LCD_Clear(uint32_t Color);
void     BSP_LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);
void     BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_DisplayOn(void);
void     BSP_LCD_DisplayOff(void);
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif // __STM32F767_FIRE_LCD_H