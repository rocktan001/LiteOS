/*********************
 *      INCLUDES
 *********************/
#include "lv_core/lv_debug.h"
#include "lv_conf.h"
#include "lvgl.h"
#include <string.h>
#include "tft.h"
#include "stm32f767_fire_lcd.h"
#define LAYER0_ADDRESS               (LCD_FB_START_ADDRESS)
#define VDB_BUF1_ADDRESS             ((uint32_t)0xD0E00000)

static lv_disp_drv_t disp_drv;
/*For LittlevGL*/
static void tft_flush_cb(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p);

/* DMA2D */
static DMA2D_HandleTypeDef  hdma2d;
static void CopyBuffer(const uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize);

#if LV_COLOR_DEPTH == 16
static uint16_t * my_fb = (uint16_t *)LAYER0_ADDRESS;
#else
static uint32_t * my_fb = (uint32_t *)LAYER0_ADDRESS;
#endif

static volatile int32_t x1_flush;
static volatile int32_t y1_flush;
static volatile int32_t x2_flush;
static volatile int32_t y2_flush;
static volatile int32_t y_flush_act;
static volatile const lv_color_t * buf_to_flush;

static volatile bool refr_qry;
static volatile uint32_t t_last = 0;

static void LCD_Config(void)
{
    BSP_LCD_DisplayOn();
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(1);
    BSP_LCD_Clear(0);
    BSP_LCD_SelectLayer(0);
    BSP_LCD_Clear(0);
}
/**
 * Monitor refresh time
 * */
void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p)
{
    t_last = t;
}

/**
 * Initialize your display here
 */
void tft_init(void)
{
    static lv_color_t *buf = (lv_color_t *)VDB_BUF1_ADDRESS;
    memset(buf, 0, TFT_HOR_RES * TFT_VER_RES * sizeof(lv_color_t));
    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, buf, NULL, TFT_HOR_RES * TFT_VER_RES);

    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = tft_flush_cb;
    disp_drv.monitor_cb = monitor_cb;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);  
    LCD_Config();  
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
uint32_t t;
volatile uint32_t elapse;
static void tft_flush_cb(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
    SCB_CleanInvalidateDCache();

    /*Truncate the area to the screen*/
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > TFT_HOR_RES - 1 ? TFT_HOR_RES - 1 : area->x2;
    int32_t act_y2 = area->y2 > TFT_VER_RES - 1 ? TFT_VER_RES - 1 : area->y2;

    x1_flush = act_x1;
    y1_flush = act_y1;
    x2_flush = act_x2;
    y2_flush = act_y2;
    y_flush_act = act_y1;
    buf_to_flush = color_p;

    CopyBuffer((const uint32_t *)color_p, (uint32_t *)my_fb, area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
    lv_disp_flush_ready(drv);
    return;
}

static void CopyBuffer(const uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize)
{
#if LV_COLOR_DEPTH == 16
    uint32_t destination = (uint32_t)pDst + (y * TFT_HOR_RES + x) * 2;
    uint32_t source      = (uint32_t)pSrc;

    /*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
    hdma2d.Init.Mode         = DMA2D_M2M;
    hdma2d.Init.ColorMode    = DMA2D_OUTPUT_RGB565;
    hdma2d.Init.OutputOffset = TFT_HOR_RES - xsize;
    hdma2d.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/
    hdma2d.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */

    /*##-2- DMA2D Callbacks Configuration ######################################*/
    hdma2d.XferCpltCallback  = NULL;

    /*##-3- Foreground Configuration ###########################################*/
    hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d.LayerCfg[1].InputAlpha = 0xFF;
    hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
    hdma2d.LayerCfg[1].InputOffset = 0;
    hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */
    hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */

    hdma2d.Instance          = DMA2D;

    /* DMA2D Initialization */
    if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
    {
        if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
        {
            if (HAL_DMA2D_Start(&hdma2d, source, destination, xsize, ysize) == HAL_OK)
            {
                /* Polling For DMA transfer */
                HAL_DMA2D_PollForTransfer(&hdma2d, 100);
            }
        }
    }
#endif
#if LV_COLOR_DEPTH == 32
    uint32_t destination = (uint32_t)pDst + (y * TFT_HOR_RES + x) * 4;
    uint32_t source      = (uint32_t)pSrc;

    /*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
    hdma2d.Init.Mode         = DMA2D_M2M;
    hdma2d.Init.ColorMode    = DMA2D_INPUT_ARGB8888;
    hdma2d.Init.OutputOffset = TFT_HOR_RES - xsize;
    hdma2d.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/
    hdma2d.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */

    /*##-2- DMA2D Callbacks Configuration ######################################*/
    hdma2d.XferCpltCallback  = NULL;

    /*##-3- Foreground Configuration ###########################################*/
    hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d.LayerCfg[1].InputAlpha = 0xFF;
    hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
    hdma2d.LayerCfg[1].InputOffset = 0;
    hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */
    hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */

    hdma2d.Instance          = DMA2D;

    /* DMA2D Initialization */
    if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
    {
        if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
        {
            if (HAL_DMA2D_Start(&hdma2d, source, destination, xsize, ysize) == HAL_OK)
            {
                /* Polling For DMA transfer */
                HAL_DMA2D_PollForTransfer(&hdma2d, 100);
            }
        }
    }
#endif    
}


