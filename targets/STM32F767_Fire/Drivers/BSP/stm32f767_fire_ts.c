
#include "stm32f767_fire_ts.h"


/* STM32 I2C 快速模式 */
#define I2C_Speed              400000

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define I2C_OWN_ADDRESS7      0x0A

I2C_HandleTypeDef  I2C_Handle; 
#if 1
static void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
#endif


 /**
  * @brief  配置 PB7 为线中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void I2C_GTP_IRQEnable(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 

    /*开启按键GPIO口的时钟*/
    GTP_INT_GPIO_CLK_ENABLE();

    /* 选择中断引脚 */ 
    GPIO_InitStructure.Pin = GTP_INT_GPIO_PIN;
    /* 设置引脚为输入模式 */ 
    GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;	    		
    /* 设置引脚不上拉也不下拉 */
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    /* 使用上面的结构体初始化按键 */
    HAL_GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure); 
    /* 配置中断优先级 */
    HAL_NVIC_SetPriority(GTP_INT_EXTI_IRQ, 1, 1);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(GTP_INT_EXTI_IRQ);

}
/**
  * @brief  关闭触摸屏中断
  * @param  无
  * @retval 无
  */
void I2C_GTP_IRQDisable(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 

    /*开启按键GPIO口的时钟*/
    GTP_INT_GPIO_CLK_ENABLE();

    /* 选择中断引脚 */ 
    GPIO_InitStructure.Pin = GTP_INT_GPIO_PIN;
    /* 设置引脚为输入模式 */ 
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;	    		
    /* 设置引脚不上拉也不下拉 */
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    /* 使用上面的结构体初始化按键 */
    HAL_GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure); 
    /* 配置中断优先级 */
    HAL_NVIC_SetPriority(GTP_INT_EXTI_IRQ, 0, 0);
    /* 使能中断 */
    HAL_NVIC_DisableIRQ(GTP_INT_EXTI_IRQ);

}
/**
  * @brief  触摸屏 I/O配置
  * @param  无
  * @retval 无
  */
static void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;  
   
  /*使能I2C时钟 */
  GTP_I2C_CLK_ENABLE();
  
  /*使能触摸屏使用的引脚的时钟*/
  GTP_I2C_SCL_GPIO_CLK_ENABLE();
  GTP_I2C_SDA_GPIO_CLK_ENABLE(); 
  GTP_RST_GPIO_CLK_ENABLE();
  GTP_INT_GPIO_CLK_ENABLE();

  /*配置SDA引脚 */  

  GPIO_InitStructure.Pin = GTP_I2C_SCL_PIN;

  GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;

  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStructure.Pull  = GPIO_NOPULL;

  GPIO_InitStructure.Alternate = GTP_I2C_SCL_AF;

  HAL_GPIO_Init(GTP_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /*配置SCL引脚 */
  GPIO_InitStructure.Pin = GTP_I2C_SDA_PIN;
  HAL_GPIO_Init(GTP_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);


 
  /*配置RST引脚，下拉推挽输出 */   
  GPIO_InitStructure.Pin = GTP_RST_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStructure.Pull  = GPIO_PULLDOWN;
  HAL_GPIO_Init(GTP_RST_GPIO_PORT, &GPIO_InitStructure);
  
  /*配置 INT引脚，下拉推挽输出，方便初始化 */   
  GPIO_InitStructure.Pin =  GTP_INT_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	//设置为下拉，方便初始化
  GPIO_InitStructure.Pull  = GPIO_PULLDOWN;
  HAL_GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure);
}
/**
  * @brief  I2C 工作模式配置
  * @param  无
  * @retval 无
  */
static void I2C_Mode_Config(void)
{
    /* I2C 配置 */

    I2C_Handle.Instance = GTP_I2C;

    I2C_Handle.Init.Timing           = 0x90913232;//50KHz

    I2C_Handle.Init.OwnAddress1      = 0;

    I2C_Handle.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;

    I2C_Handle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;

    I2C_Handle.Init.OwnAddress2      = 0;

    I2C_Handle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;

    I2C_Handle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;

    I2C_Handle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

    /* Init the I2C */

    HAL_I2C_Init(&I2C_Handle);	
    HAL_I2CEx_AnalogFilter_Config(&I2C_Handle, I2C_ANALOGFILTER_ENABLE); 
}

/**
  * @brief  对GT91xx芯片进行复位
  * @param  无
  * @retval 无
  */
void I2C_ResetChip(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*配置 INT引脚，下拉推挽输出，方便初始化 */   
	GPIO_InitStructure.Pin = GTP_INT_GPIO_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull  = GPIO_PULLDOWN;       //设置为下拉，方便初始化
	HAL_GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure);

	/*初始化GT9157,rst为高电平，int为低电平，则gt9157的设备地址被配置为0xBA*/

	/*复位为低电平，为初始化做准备*/
	HAL_GPIO_WritePin (GTP_RST_GPIO_PORT,GTP_RST_GPIO_PIN,GPIO_PIN_RESET);
	Delay(0x0FFFFF);

	/*拉高一段时间，进行初始化*/
	HAL_GPIO_WritePin (GTP_RST_GPIO_PORT,GTP_RST_GPIO_PIN,GPIO_PIN_SET);
	Delay(0x0FFFFF);

	  /*初始化GT9157,rst为高电平，int为低电平，则gt9157的设备地址被配置为0xBA*/

	/*复位为低电平，为初始化做准备*/
	HAL_GPIO_WritePin (GTP_RST_GPIO_PORT,GTP_RST_GPIO_PIN,GPIO_PIN_RESET);
	Delay(0x0FFFFF);

	/*拉高一段时间，进行初始化*/
	HAL_GPIO_WritePin (GTP_RST_GPIO_PORT,GTP_RST_GPIO_PIN,GPIO_PIN_SET);
	Delay(0x0FFFFF);

	/*把INT引脚设置为浮空输入模式，以便接收触摸中断信号*/
	GPIO_InitStructure.Pin = GTP_INT_GPIO_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure);
}
/**
  * @brief  I2C 外设(GT91xx)初始化
  * @param  无
  * @retval 无
  */
void I2C_Touch_Init(void)
{
	I2C_GPIO_Config(); 
	I2C_Mode_Config();
	I2C_ResetChip();
	I2C_GTP_IRQEnable();
}
/**
  * @brief   使用IIC读取数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:存放由从机读取的数据的缓冲区指针
  *		@arg NumByteToRead:读取的数据长度
  * @retval  无
  */
uint32_t I2C_ReadBytes(uint8_t ClientAddr,uint8_t* pBuffer, uint16_t NumByteToRead)
{
  HAL_I2C_Master_Receive(&I2C_Handle,ClientAddr,pBuffer,NumByteToRead,1000);    
  return 0;
}
/**
  * @brief   使用IIC写入数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:缓冲区指针
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_WriteBytes(uint8_t ClientAddr,uint8_t* pBuffer,  uint8_t NumByteToWrite)
{
  HAL_I2C_Master_Transmit(&I2C_Handle,ClientAddr,pBuffer,NumByteToWrite,1000);
  return 0;  

}
/**
  * @brief  Initializes and configures the touch screen functionalities and
  *         configures all necessary hardware resources (GPIOs, I2C, clocks..).
  * @param  ts_SizeX : Maximum X size of the TS area on LCD
  * @param  ts_SizeY : Maximum Y size of the TS area on LCD
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_Init(uint16_t ts_SizeX, uint16_t ts_SizeY)
{
	return 0;
}
/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TS_State: Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_GetState(TS_StateTypeDef *TS_State)
{
	return 0;
}