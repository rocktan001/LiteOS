/**
  *******************************************************************************************************
  * @file    fm33lc0xx_ll_dma.c
  * @author  FMSH Application Team
  * @brief   Src file of DMA LL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2019] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under the Mulan PSL v1.
  * can use this software according to the terms and conditions of the Mulan PSL v1.
  * You may obtain a copy of Mulan PSL v1 at:
  * http://license.coscl.org.cn/MulanPSL
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
  * PURPOSE.
  * See the Mulan PSL v1 for more details.
  *
  *******************************************************************************************************
  */
#include "fm33lc0xx_ll_rcc.h"
#include "fm33lc0xx_ll_rmu.h"
#include "fm33lc0xx_ll_dma.h"
#include "fm33_assert.h"
    
/** @addtogroup FM33LC0xx_LL_Driver_DMA
  * @{
  */
/** @addtogroup Private_Macros
  * @{
  */
#define         IS_LL_DMA_INSTANCE(INTANCE)                         ((INTANCE) == DMA)

#define         IS_LL_DMA_PRIORITY(__VALUE__)                       (((__VALUE__) == LL_DMA_CHANNEL_PRIORITY_LOW)||\
                                                                     ((__VALUE__) == LL_DMA_CHANNEL_PRIORITY_MEDIUM)||\
                                                                     ((__VALUE__) == LL_DMA_CHANNEL_PRIORITY_HIGH)||\
                                                                     ((__VALUE__) == LL_DMA_CHANNEL_PRIORITY_VERYHIGH))

#define         IS_LL_DMA_CIRC_MODE(__VALUE__)                      (((__VALUE__) == DISABLE)||\
                                                                     ((__VALUE__) == ENABLE))


#define         IS_LL_DMA_DIRECION(__VALUE__)                       (((__VALUE__) == LL_DMA_DIR_PERIPHERAL_TO_RAM)||\
                                                                     ((__VALUE__) == LL_DMA_DIR_FLASH_TO_RAM)||\
                                                                     ((__VALUE__) == LL_DMA_DIR_RAM_TO_FLASH)||\
                                                                    ((__VALUE__) == LL_DMA_DIR_RAM_TO_PERIPHERAL))

                                                                    
#define         IS_LL_DMA_DATA_SIZE(__VALUE__)                      (((__VALUE__) == LL_DMA_BAND_WIDTH_BYTE)||\
                                                                    ((__VALUE__) == LL_DMA_BAND_WIDTH_WORD)||\
                                                                    ((__VALUE__) == LL_DMA_BAND_WIDTH_HALF_WORD))

#define         IS_LL_DMA_INCMODE(__VALUE__)                       (((__VALUE__) == LL_DMA_INCREMENTAL_INCREASE)||\
                                                                    ((__VALUE__) == LL_DMA_INCREMENTAL_REDUCE) ||\
                                                                    ((__VALUE__) == LL_DMA_CH7_RAM_ADDR_INCREASE)||\
                                                                    ((__VALUE__) == LL_DMA_CH7_RAM_ADDR_REDUCE))
                                                                    
#define         IS_LL_DMA_PERIPH(__VALUE__)                        (((__VALUE__) == LL_DMA_PERIPHERAL_FUNCTION1)||\
                                                                    ((__VALUE__) == LL_DMA_PERIPHERAL_FUNCTION2)||\
                                                                    ((__VALUE__) == LL_DMA_PERIPHERAL_FUNCTION3)||\
                                                                    ((__VALUE__) == LL_DMA_PERIPHERAL_FUNCTION4)||\
                                                                    ((__VALUE__) == LL_DMA_PERIPHERAL_FUNCTION5)||\
                                                                    ((__VALUE__) == LL_DMA_PERIPHERAL_FUNCTION6)||\
                                                                    ((__VALUE__) == LL_DMA_PERIPHERAL_FUNCTION7)||\
                                                                    ((__VALUE__) == LL_DMA_PERIPHERAL_FUNCTION8))
/**
  * @}
  */ 
  
/** @addtogroup DMA_LL_EF_Init
  * @{
  */
  
/**
  * @brief  ????????????DMA?????????.
  * @param  DMAx 
  * @retval ErrorStatus?????????:
  *       	-PASS ?????????????????????????????????
  *       	-FAIL ???????????????
  */
ErrorStatus LL_DMA_DeInit(DMA_Type *DMAx)
{
    
    assert_param(IS_LL_DMA_INSTANCE(DMAx));
    
    /* ?????????????????? */
    LL_RCC_EnablePeripheralReset();
    /* ????????????????????? */
    LL_RCC_EnableResetAHBPeripheral(LL_RCC_AHB_PERIPHERAL_RST_DMA);
    LL_RCC_DisableResetAHBPeripheral(LL_RCC_AHB_PERIPHERAL_RST_DMA);
    /* ?????????????????????????????????????????? */
    LL_RCC_Group2_DisableBusClock(LL_RCC_BUS2_CLOCK_DMA);
    /* ?????????????????? */
    LL_RCC_DisablePeripheralReset();
    return PASS;
}
/**
  * @brief  ?????? DMA_InitStruct ???????????????????????????????????????????????????????????????.
  * @param  DMAx DMAx 
  * @param  DMA_InitStruct ???????????? @ref LL_DMA_InitTypeDef ?????????
  *         ??????????????????????????????????????????.
  * @param  Channel This parameter can be one of the following values:
  *           @arg @ref LL_DMA_CHANNEL_0
  *           @arg @ref LL_DMA_CHANNEL_1
  *           @arg @ref LL_DMA_CHANNEL_2
  *           @arg @ref LL_DMA_CHANNEL_3
  *           @arg @ref LL_DMA_CHANNEL_4
  *           @arg @ref LL_DMA_CHANNEL_5
  *           @arg @ref LL_DMA_CHANNEL_6
  *           @arg @ref LL_DMA_CHANNEL_7
  * @retval ErrorStatus?????????	
  *			-FAIL ????????????????????????        
  *			-PASS ????????????  
  */
ErrorStatus LL_DMA_Init(DMA_Type *DMAx,LL_DMA_InitTypeDef *DMA_InitStruct,uint32_t Channel)
{
    /* ???????????? */
    assert_param(IS_LL_DMA_INSTANCE(DMAx));
    assert_param(IS_LL_DMA_PRIORITY(DMA_InitStruct->Priority));
    assert_param(IS_LL_DMA_CIRC_MODE (DMA_InitStruct->CircMode));
    assert_param(IS_LL_DMA_DIRECION(DMA_InitStruct->Direction));  
    assert_param(IS_LL_DMA_DATA_SIZE(DMA_InitStruct->DataSize)); 
    assert_param(IS_LL_DMA_INCMODE (DMA_InitStruct->MemoryAddressIncMode));
    /* ???????????? */
    LL_RCC_Group2_EnableBusClock(LL_RCC_BUS2_CLOCK_DMA);
    /* ????????????????????? */
    LL_DMA_SetChannelPriority(DMAx,DMA_InitStruct->Priority,Channel);
    /* RAM???????????? */
    LL_DMA_SetChannelAddrIncremental(DMAx,DMA_InitStruct->MemoryAddressIncMode,Channel);
    /* ???????????? */
    LL_DMA_SetChannelTransDirection(DMAx,DMA_InitStruct->Direction,Channel);
    /* ???????????? */
    LL_DMA_SetChannelBandWidth(DMAx,DMA_InitStruct->DataSize,Channel);
    /* ???????????? */
    if(DMA_InitStruct->CircMode == ENABLE)
    {
        LL_DMA_Enable_CircularMode(DMAx,Channel);
        if(Channel == LL_DMA_CHANNEL_7)
        {
            return FAIL;
        }
    }
    else
    {
        LL_DMA_Disable_CircularMode(DMAx,Channel);
    }
    
    /* ?????????????????? */
    LL_DMA_SetTransmissionSize(DMAx,DMA_InitStruct->NbData,Channel);
    
    /* ???????????????7 ????????????????????????FLASH?????????????????????????????????7?????????????????? */
    if(Channel != LL_DMA_CHANNEL_7)
    {
        assert_param(IS_LL_DMA_PERIPH(DMA_InitStruct->PeriphAddress));
        LL_DMA_SetChannelPeripheralMap(DMAx,DMA_InitStruct->PeriphAddress,Channel);
    }
    else
    {
        LL_DMA_SetChannelFlashAddr(DMAx,DMA_InitStruct->PeriphAddress,Channel);
        LL_DMA_SetFlash_AddrIncremental (DMAx,DMA_InitStruct->FlashAddressIncMode);
    }   
    LL_DMA_SetChannelMemAddr(DMAx,DMA_InitStruct->MemoryAddress,Channel);
    
    return PASS;
}  
/**
  * @brief	?????? CRC_InitStruct ???????????????
  * @param 	CRC_InitStruct ??????????????????????????????????????????????????? @ref LL_CRC_InitTypeDef ?????????  
  *         
  * @retval	None
  */

void LL_DMA_StructInit(LL_DMA_InitTypeDef *InitStruct)
{
    
    InitStruct->CircMode                = DISABLE;
    InitStruct->DataSize                = LL_DMA_BAND_WIDTH_BYTE;
    InitStruct->Direction               = LL_DMA_DIR_PERIPHERAL_TO_RAM;
    InitStruct->PeriphAddress           = LL_DMA_PERIPHERAL_FUNCTION1;
    InitStruct->NbData                  = 0;
    InitStruct->Priority                = LL_DMA_CHANNEL_PRIORITY_LOW;
    InitStruct->MemoryAddress           = 0x0U;
    InitStruct->MemoryAddressIncMode    = LL_DMA_INCREMENTAL_REDUCE;
    
}

/**
  * @brief  ????????????DMA??????.
  * @param  DMAx DMAx 
  * @param  DMA_InitStruct ???????????? @ref LL_DMA_InitTypeDef ?????????
  *         ??????????????????????????????????????????.
  * @param  Channel This parameter can be one of the following values:
  *           @arg @ref LL_DMA_CHANNEL_0
  *           @arg @ref LL_DMA_CHANNEL_1
  *           @arg @ref LL_DMA_CHANNEL_2
  *           @arg @ref LL_DMA_CHANNEL_3
  *           @arg @ref LL_DMA_CHANNEL_4
  *           @arg @ref LL_DMA_CHANNEL_5
  *           @arg @ref LL_DMA_CHANNEL_6
  *           @arg @ref LL_DMA_CHANNEL_7
  * @retval ErrorStatus?????????	
  *			-FAIL ?????????????????????????????????????????????????????????        
  *			-PASS ??????  
  */
ErrorStatus LL_StartOnceDMATransmion(DMA_Type *DMAx,LL_DMA_InitTypeDef *DMA_InitStruct ,uint32_t Channel)
{
    uint32_t   TimeOut = 0xFFFF;
   
    /* ?????????????????????????????????????????????DMA */
    LL_DMA_Init(DMAx,DMA_InitStruct,Channel);
    /* ??????DMA??????????????? */
    LL_DMA_Enable_DMA(DMAx);
    /* ??????DMA?????????????????? */
    LL_DMA_Enable_Channel(DMAx,Channel);
    while(1)
    {
        TimeOut--;
        if(TimeOut == 0 || LL_DMA_IsActiveFlag_Finished(DMAx,Channel)||\
             LL_DMA_IsActiveFlag_ADDRERR(DMAx))
        {
            /* ????????????????????? */
            break;
        }    
    }
    /* ??????DMA??????????????? */
    LL_DMA_Disable_DMA(DMAx);
    /* ??????DMA?????????????????? */
    LL_DMA_Disable_Channel(DMAx,Channel);
    if(!TimeOut)
    {
        /* ???????????? */
        return FAIL;
    }
    if(LL_DMA_IsActiveFlag_ADDRERR(DMAx))
    {
        /* ?????????????????? */
        return FAIL;
    }
    LL_DMA_ClearFlag_Finished(DMAx,Channel);
    return PASS;
}  
/**
  * @}
  */
/**
  * @}
  */

/**************************Py_Code_Generator Version: 0.1-0.5-0.1 @ 2019-10-25**************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
