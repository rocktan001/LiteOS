/*!
 * @file        apm32f10x_iwdt.c
 *
 * @brief       This file provides all the IWDT firmware functions
 *
 * @version     V1.0.1
 *
 * @date        2021-03-23
 *
 */

#include "apm32f10x_iwdt.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup IWDT_Driver IWDT Driver
  @{
*/

/** @addtogroup IWDT_Fuctions Fuctions
  @{
*/

/*!
 * @brief        Enable IWDT
 *
 * @param        None
 *
 * @retval       None
 */
void IWDT_Enable(void)
{
    IWDT->KEY = IWDT_KEYWORD_ENABLE;
}

/*!
 * @brief        Reload the IWDT counter with value
 *
 * @param        None
 *
 * @retval       None
 */
void IWDT_Refresh(void)
{
    IWDT->KEY = IWDT_KEYWORD_RELOAD;
}

/*!
 * @brief        Set IWDT count reload values
 *
 * @param        reload: IWDT count reload values
 *
 * @retval       None
 */
void IWDT_ConfigReload(uint16_t reload)
{
    IWDT->CNTRLD = reload;
}

/*!
 * @brief        Enable the IWDT write access
 *
 * @param        None
 *
 * @retval       None
 */
void IWDT_EnableWriteAccess(void)
{
    IWDT->KEY_B.KEY = IWDT_WRITEACCESS_ENABLE;
}

/*!
 * @brief        Disable the IWDT write access
 *
 * @param        None
 *
 * @retval       None
 */
void IWDT_DisableWriteAccess(void)
{
    IWDT->KEY_B.KEY = IWDT_WRITEACCESS_DISABLE;
}

/*!
 * @brief        Set IWDT frequency divider values
 *
 * @param        div: IWDT frequency divider values
 *                    This parameter can be one of the following values:
 *                    @arg IWDT_DIVIDER_4  : prescaler divider equal to 4
 *                    @arg IWDT_DIVIDER_8  : prescaler divider equal to 8
 *                    @arg IWDT_DIVIDER_16 : prescaler divider equal to 16
 *                    @arg IWDT_DIVIDER_32 : prescaler divider equal to 32
 *                    @arg IWDT_DIVIDER_64 : prescaler divider equal to 64
 *                    @arg IWDT_DIVIDER_128: prescaler divider equal to 128
 *                    @arg IWDT_DIVIDER_256: prescaler divider equal to 256
 *
 * @retval       None
 */
void IWDT_ConfigDivider(uint8_t div)
{
    IWDT->PSC = div;
}

/*!
 * @brief        Read the specified IWDT flag
 *
 * @param        flag: specifies the flag to read
 *                     This parameter can be one of the following values:
 *                     @arg IWDT_FLAG_PSCU : Watchdog Prescaler Factor Update flag
 *                     @arg IWDT_FLAG_CNTU : Watchdog Counter Reload Value Update flag
 *
 * @retval       status of IWDT_FLAG (SET or RESET)
 *
 * @note
 */
uint8_t IWDT_ReadStatusFlag(uint16_t flag)
{
    uint8_t bitStatus = RESET;

    if((IWDT->STS & flag) != (uint32_t)RESET)
    {
        bitStatus = SET;
    }
    else
    {
        bitStatus = RESET;
    }
    return bitStatus;
}

/**@} end of group IWDT_Fuctions*/
/**@} end of group IWDT_Driver */
/**@} end of group Peripherals_Library*/
