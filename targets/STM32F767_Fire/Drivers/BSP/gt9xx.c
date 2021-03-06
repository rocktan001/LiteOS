/**
  ******************************************************************************
  * @file    gt9xx.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   i2c??????????????gt9157оƬ
  ******************************************************************************
  * @attention
  *
  * ʵ??ƽ̨:Ұ?? STM32F767 ?????? 
  * ??̳    :http://www.firebbs.cn
  * ?Ա?    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
#include <stdio.h>
#include <string.h>
#include "stm32f7xx.h"
#include "gt9xx.h"
#include "stm32f767_fire_ts.h"

/*?жϷ???????*/
// #define GTP_IRQHandler                   EXTI15_10_IRQHandler

void GTP_IRQHandler(void);

extern uint32_t I2C_ReadBytes(uint8_t ClientAddr,uint8_t* pBuffer, uint16_t NumByteToRead);
extern uint32_t I2C_WriteBytes(uint8_t ClientAddr,uint8_t* pBuffer,  uint8_t NumByteToWrite);
extern void I2C_GTP_IRQDisable(void);
extern void I2C_GTP_IRQEnable(void);
extern void I2C_ResetChip(void);
extern void I2C_Touch_Init(void);

// 5????GT9157????????
uint8_t CTP_CFG_GT9157[] ={ 
	0x00,0x20,0x03,0xE0,0x01,0x05,0x3C,0x00,0x01,0x08,
	0x28,0x0C,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x17,0x19,0x1E,0x14,0x8B,0x2B,0x0D,
	0x33,0x35,0x0C,0x08,0x00,0x00,0x00,0x9A,0x03,0x11,
	0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x32,0x00,0x00,
	0x00,0x20,0x58,0x94,0xC5,0x02,0x00,0x00,0x00,0x04,
	0xB0,0x23,0x00,0x93,0x2B,0x00,0x7B,0x35,0x00,0x69,
	0x41,0x00,0x5B,0x4F,0x00,0x5B,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10,
	0x12,0x14,0x16,0x18,0x1A,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0F,
	0x10,0x12,0x13,0x16,0x18,0x1C,0x1D,0x1E,0x1F,0x20,
	0x21,0x22,0x24,0x26,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
	0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0x48,0x01
};

// 7????GT911???????ã?Ĭ??ʹ?õ?һ???????ļ?????????Ļ?쳣???ɳ???ʹ?õڶ???
#if  1 
const uint8_t CTP_CFG_GT911[] =  {
0x41,0x20,0x03,0xE0,0x01,0x05,0x3D,0x00,0x01,0x08,
0x1E,0x05,0x3C,0x3C,0x03,0x05,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1A,0x1C,0x1E,0x14,0x8A,0x2A,0x0C,
0x2A,0x28,0xEB,0x04,0x00,0x00,0x01,0x61,0x03,0x2C,
0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x14,0x3C,0x94,0xC5,0x02,0x08,0x00,0x00,0x04,
0xB7,0x16,0x00,0x9F,0x1B,0x00,0x8B,0x22,0x00,0x7B,
0x2B,0x00,0x70,0x36,0x00,0x70,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x16,0x14,0x12,0x10,0x0E,0x0C,0x0A,
0x08,0x06,0x04,0x02,0xFF,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x24,0x22,0x21,0x20,0x1F,0x1E,0x1D,0x1C,
0x18,0x16,0x13,0x12,0x10,0x0F,0x0A,0x08,0x06,0x04,
0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0A,0x00
};
#else 
const uint8_t CTP_CFG_GT911[] =  {
  0x00,0x20,0x03,0xE0,0x01,0x05,0x0D,0x00,0x01,0x08,
  0x28,0x0F,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8A,0x2A,0x0C,
  0x45,0x47,0x0C,0x08,0x00,0x00,0x00,0x02,0x02,0x2D,
  0x00,0x00,0x00,0x00,0x00,0x03,0x64,0x32,0x00,0x00,
  0x00,0x28,0x64,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
  0x9C,0x2C,0x00,0x8F,0x34,0x00,0x84,0x3F,0x00,0x7C,
  0x4C,0x00,0x77,0x5B,0x00,0x77,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x18,0x16,0x14,0x12,0x10,0x0E,0x0C,0x0A,
  0x08,0x06,0x04,0x02,0xFF,0xFF,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x16,0x18,0x1C,0x1D,0x1E,0x1F,0x20,0x21,
  0x22,0x24,0x13,0x12,0x10,0x0F,0x0A,0x08,0x06,0x04,
  0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x24,0x01	
};
#endif

// 4.3????GT5688????????,ע??gt5688??һ??????Ҫд??0x97?Ż?????????
uint8_t CTP_CFG_GT5688[] =  {
0x97,0xE0,0x01,0x10,0x01,0x05,0x0D,0x00,0x01,0x00,
0x00,0x05,0x5A,0x46,0x53,0x11,0x00,0x00,0x11,0x11,
0x14,0x14,0x14,0x22,0x0A,0x04,0x00,0x00,0x00,0x00,
0x00,0x00,0x53,0x00,0x14,0x00,0x00,0x84,0x00,0x00,
0x3C,0x00,0x00,0x64,0x1E,0x28,0x87,0x27,0x08,0x32,
0x34,0x05,0x0D,0x20,0x33,0x60,0x11,0x02,0x24,0x00,
0x00,0x64,0x80,0x80,0x14,0x02,0x00,0x00,0x54,0x89,
0x68,0x85,0x6D,0x82,0x72,0x80,0x76,0x7D,0x7B,0x7B,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x50,0x3C,
0xFF,0xFF,0x07,0x00,0x00,0x00,0x02,0x14,0x14,0x03,
0x04,0x00,0x21,0x64,0x0A,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x32,0x20,0x50,0x3C,0x3C,0x00,0x00,0x00,0x00,0x00,
0x0D,0x06,0x0C,0x05,0x0B,0x04,0x0A,0x03,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x00,0x01,0x02,0x03,0x04,0x05,
0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3C,0x00,0x05,0x1E,0x00,0x02,
0x2A,0x1E,0x19,0x14,0x02,0x00,0x03,0x0A,0x05,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x86,
0x22,0x03,0x00,0x00,0x33,0x00,0x0F,0x00,0x00,0x00,
0x50,0x3C,0x50,0x00,0x00,0x00,0x00,0x2A,0x01
};
//5????GT917S????????
uint8_t CTP_CFG_GT917S[] ={ 
  0x97,0x20,0x03,0xE0,0x01,0x0A,0x35,0x04,0x00,0x69,
  0x09,0x0F,0x50,0x32,0x33,0x11,0x00,0x32,0x11,0x11,
  0x28,0x8C,0xAA,0xDC,0x58,0x04,0x00,0x00,0x1E,0x3C,
  0x00,0x00,0x00,0x31,0x00,0x00,0x00,0x00,0x00,0x40,
  0x32,0x00,0x00,0x50,0x38,0x00,0x8D,0x20,0x16,0x4E,
  0x4C,0x7C,0x05,0x28,0x3E,0x28,0x0D,0x43,0x24,0x00,
  0x01,0x39,0x6B,0xC0,0x94,0x84,0x2D,0x00,0x54,0xB0,
  0x41,0x9D,0x49,0x8D,0x52,0x7F,0x5A,0x75,0x62,0x6C,
  0x42,0x50,0x14,0x00,0x00,0x00,0x00,0xF0,0x50,0x3C,
  0x88,0x88,0x27,0x50,0x3C,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x00,0x02,0x78,
  0x0A,0x50,0xFF,0xE4,0x04,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x3C,0xB0,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x56,0xA2,0x07,0x50,0x1E,
  0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
  0x0F,0x10,0x12,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,
  0x1D,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0x1F,0x1E,0x1D,0x1C,0x1B,0x1A,0x19,0x18,
  0x17,0x15,0x14,0x13,0x12,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0x00,0x30,0x7F,0x7F,0x7F,0xFF,
  0x54,0x64,0x00,0x80,0x46,0x07,0x50,0x3C,0x32,0x14,
  0x0A,0x64,0x32,0x00,0x00,0x00,0x00,0x11,0x02,0x62,
  0x32,0x03,0x14,0x50,0x0C,0xE2,0x14,0x50,0x00,0x54,
  0x10,0x00,0x32,0xA2,0x07,0x64,0xA4,0xB6,0x01
};

// 7????GT615????????
const uint8_t CTP_CFG_GT615[] =  {
  0x6B,0x20,0x03,0xE0,0x01,0x05,0x0D,0x00,0x01,0x08,
  0x28,0x0F,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8A,0x2A,0x0C,
  0x45,0x47,0x0C,0x08,0x00,0x00,0x00,0x02,0x02,0x2D,
  0x00,0x00,0x00,0x00,0x00,0x03,0x64,0x32,0x00,0x00,
  0x00,0x28,0x64,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
  0x9C,0x2C,0x00,0x8F,0x34,0x00,0x84,0x3F,0x00,0x7C,
  0x4C,0x00,0x77,0x5B,0x00,0x77,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x18,0x16,0x14,0x12,0x10,0x0E,0x0C,0x0A,
  0x08,0x06,0x04,0x02,0xFF,0xFF,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x16,0x18,0x1C,0x1D,0x1E,0x1F,0x20,0x21,
  0x22,0x24,0x13,0x12,0x10,0x0F,0x0A,0x08,0x06,0x04,
  0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x19,0x01
};


//uint8_t config[GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH]
//                = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};

/* ????IC????Ĭ??Ϊ5??????ic */
TOUCH_IC touchIC = GT9157;								

const TOUCH_PARAM_TypeDef touch_param[TOUCH_TYPE_NUM] = 
{
  /* GT9157,5???? */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8047,
  },
  /* GT911,7???? */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8047,
  },
  /* GT5688,4.3???? */
  {
    .max_width = 480,
    .max_height = 272,
    .config_reg_addr = 0x8050,
  },
	 /* GT917S,5???? */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8050,
  },
  /* GT615,7???? */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8047, //????ʼ??ַ??GT911??һ??
  },
};

static int8_t GTP_I2C_Test(void);
//static void GT91xx_Config_Read_Proc(void);
#if 0
static void Delay(__IO uint32_t nCount)	 //?򵥵???ʱ????
{
	for(; nCount != 0; nCount--);
}
#endif

/**
  * @brief   ʹ??IIC???????ݴ???
  * @param
  *		@arg i2c_msg:???ݴ????ṹ??
  *		@arg num:???ݴ????ṹ???ĸ???
  * @retval  ???????ɵĴ????ṹ????????????????????0xff
  */
static int I2C_Transfer( struct i2c_msg *msgs,int num)
{
	int im = 0;
	int ret = 0;

	GTP_DEBUG_FUNC();

	for (im = 0; ret == 0 && im != num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//????flag?ж??Ƕ????ݻ???д????
		{
			ret = I2C_ReadBytes(msgs[im].addr, msgs[im].buf, msgs[im].len);		//IIC??ȡ????
		} else
		{
			ret = I2C_WriteBytes(msgs[im].addr,  msgs[im].buf, msgs[im].len);	//IICд??????
		}
	}

	if(ret)
		return ret;

	return im;   													//???????ɵĴ????ṹ????
}

/**
  * @brief   ??IIC?豸?ж?ȡ????
  * @param
  *		@arg client_addr:?豸??ַ
  *		@arg  buf[0~1]: ??ȡ???ݼĴ???????ʼ??ַ
  *		@arg buf[2~len-1]: ?洢?????????ݵĻ???buffer
  *		@arg len:    GTP_ADDR_LENGTH + read bytes count???Ĵ?????ַ????+??ȡ???????ֽ?????
  * @retval  i2c_msgs?????ṹ???ĸ?????2Ϊ?ɹ???????Ϊʧ??
  */
static int32_t GTP_I2C_Read(uint8_t client_addr, uint8_t *buf, int32_t len)
{
    struct i2c_msg msgs[2];
    int32_t ret=-1;
    int32_t retries = 0;

    GTP_DEBUG_FUNC();
    /*һ???????ݵĹ??̿??Է?Ϊ????????????:
     * 1. IIC  д?? Ҫ??ȡ?ļĴ?????ַ
     * 2. IIC  ??ȡ  ????
     * */

    msgs[0].flags = !I2C_M_RD;					//д??
    msgs[0].addr  = client_addr;					//IIC?豸??ַ
    msgs[0].len   = GTP_ADDR_LENGTH;	//?Ĵ?????ַΪ2?ֽ?(??д?????ֽڵ?????)
    msgs[0].buf   = &buf[0];						//buf[0~1]?洢????Ҫ??ȡ?ļĴ?????ַ
    
    msgs[1].flags = I2C_M_RD;					//??ȡ
    msgs[1].addr  = client_addr;					//IIC?豸??ַ
    msgs[1].len   = len - GTP_ADDR_LENGTH;	//Ҫ??ȡ?????ݳ???
    msgs[1].buf   = &buf[GTP_ADDR_LENGTH];	//buf[GTP_ADDR_LENGTH]֮???Ļ??????洢??????????

    while(retries < 5)
    {
        ret = I2C_Transfer( msgs, 2);					//????IIC???ݴ??????̺???????2??????????
        if(ret == 2)break;
        retries++;
    }
    if((retries >= 5))
    {
        GTP_ERROR("I2C Read: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);
    }
    return ret;
}



/**
  * @brief   ??IIC?豸д??????
  * @param
  *		@arg client_addr:?豸??ַ
  *		@arg  buf[0~1]: Ҫд???????ݼĴ???????ʼ??ַ
  *		@arg buf[2~len-1]: Ҫд????????
  *		@arg len:    GTP_ADDR_LENGTH + write bytes count???Ĵ?????ַ????+д?????????ֽ?????
  * @retval  i2c_msgs?????ṹ???ĸ?????1Ϊ?ɹ???????Ϊʧ??
  */
static int32_t GTP_I2C_Write(uint8_t client_addr,uint8_t *buf,int32_t len)
{
    struct i2c_msg msg;
    int32_t ret = -1;
    int32_t retries = 0;

    GTP_DEBUG_FUNC();
    /*һ??д???ݵĹ???ֻ??Ҫһ??????????:
     * 1. IIC???? д?? ???ݼĴ?????ַ??????
     * */
    msg.flags = !I2C_M_RD;			//д??
    msg.addr  = client_addr;			//???豸??ַ
    msg.len   = len;							//????ֱ?ӵ???(?Ĵ?????ַ????+д?????????ֽ???)
    msg.buf   = buf;						//ֱ??????д?뻺?????е?????(?????˼Ĵ?????ַ)

    while(retries < 5)
    {
        ret = I2C_Transfer(&msg, 1);	//????IIC???ݴ??????̺?????1??????????
        if (ret == 1)break;
        retries++;
    }
    if((retries >= 5))
    {

        GTP_ERROR("I2C Write: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);

    }
    return ret;
}



/**
  * @brief   ʹ??IIC??ȡ?ٴ????ݣ??????Ƿ?????
  * @param
  *		@arg client:?豸??ַ
  *		@arg  addr: ?Ĵ?????ַ
  *		@arg rxbuf: ?洢??????????
  *		@arg len:    ??ȡ???ֽ???
  * @retval
  * 	@arg FAIL
  * 	@arg SUCCESS
  */
 int32_t GTP_I2C_Read_dbl_check(uint8_t client_addr, uint16_t addr, uint8_t *rxbuf, int len)
{
    uint8_t buf[16] = {0};
    uint8_t confirm_buf[16] = {0};
    uint8_t retry = 0;
    
    GTP_DEBUG_FUNC();

    while (retry++ < 3)
    {
        memset(buf, 0xAA, 16);
        buf[0] = (uint8_t)(addr >> 8);
        buf[1] = (uint8_t)(addr & 0xFF);
        GTP_I2C_Read(client_addr, buf, len + 2);
        
        memset(confirm_buf, 0xAB, 16);
        confirm_buf[0] = (uint8_t)(addr >> 8);
        confirm_buf[1] = (uint8_t)(addr & 0xFF);
        GTP_I2C_Read(client_addr, confirm_buf, len + 2);

      
        if (!memcmp(buf, confirm_buf, len+2))
        {
            memcpy(rxbuf, confirm_buf+2, len);
            return SUCCESS;
        }
    }    
    GTP_ERROR("I2C read 0x%04X, %d bytes, double check failed!", addr, len);
    return FAIL;
}


/**
  * @brief   ?ر?GT91xx?ж?
  * @param ??
  * @retval ??
  */
void GTP_IRQ_Disable(void)
{

    GTP_DEBUG_FUNC();

    I2C_GTP_IRQDisable();
}

/**
  * @brief   ʹ??GT91xx?ж?
  * @param ??
  * @retval ??
  */
void GTP_IRQ_Enable(void)
{
	GTP_DEBUG_FUNC();
	I2C_GTP_IRQEnable();    
}


/**
  * @brief   ???ڴ????򱨸津?????⵽????
  * @param
  *    @arg     id: ????˳??trackID
  *    @arg     x:  ?????? x ????
  *    @arg     y:  ?????? y ????
  *    @arg     w:  ?????? ??С
  * @retval ??
  */
/*???ڼ?¼????????ʱ(????)????һ?δ???λ?ã?????ֵ??ʾ??һ???޴???????*/
static int16_t pre_x[GTP_MAX_TOUCH] ={-1,-1,-1,-1,-1};
static int16_t pre_y[GTP_MAX_TOUCH] ={-1,-1,-1,-1,-1};

static void GTP_Touch_Down(int32_t id,int32_t x,int32_t y,int32_t w)
{
  
	GTP_DEBUG_FUNC();

	/*ȡx??y??ʼֵ??????Ļ????ֵ*/
    GTP_DEBUG("ID:%d, X:%d, Y:%d, W:%d", id, x, y, w);
	
    /* ??????????ť?????ڴ??????? */
   // Touch_Button_Down(x,y); 	

    /*?????????켣?????ڴ??????? */
   // Draw_Trail(pre_x[id],pre_y[id],x,y,&brush);
	
	/************************************/
	/*?ڴ˴??????Լ??Ĵ????㰴??ʱ???????̼???*/
	/* (x,y) ??Ϊ???µĴ????? *************/
	/************************************/
	/*prex,prey?????洢??һ?δ?????λ?ã?idΪ?켣????(???㴥??ʱ?ж??켣)*/
    pre_x[id] = x; pre_y[id] =y;
	
}


/**
  * @brief   ???ڴ????򱨸津???ͷ?
  * @param ?ͷŵ???id??
  * @retval ??
  */
static void GTP_Touch_Up( int32_t id)
{
	
    /*?????????ͷ?,???ڴ???????*/
   // Touch_Button_Up(pre_x[id],pre_y[id]);
	/*****************************************/
	/*?ڴ˴??????Լ??Ĵ??????ͷ?ʱ?Ĵ??????̼???*/
	/* pre_x[id],pre_y[id] ??Ϊ???µ??ͷŵ? ****/
	/*******************************************/	
	/***idΪ?켣????(???㴥??ʱ?ж??켣)********/	
    /*?????ͷţ???pre xy ????Ϊ??*/
	  pre_x[id] = -1;
	  pre_y[id] = -1;		
  
    GTP_DEBUG("Touch id[%2d] release!", id);
}


/**
  * @brief   ????????????????ѯ?????ڴ????жϵ???
  * @param ??
  * @retval ??
  */
static void Goodix_TS_Work_Func(void)
{
    uint8_t  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
    uint8_t  point_data[2 + 1 + 8 * GTP_MAX_TOUCH + 1]={GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
    uint8_t  touch_num = 0;
    uint8_t  finger = 0;
    static uint16_t pre_touch = 0;
    static uint8_t pre_id[GTP_MAX_TOUCH] = {0};

    uint8_t client_addr=GTP_ADDRESS;
    uint8_t* coor_data = NULL;
    int32_t input_x = 0;
    int32_t input_y = 0;
    int32_t input_w = 0;
    uint8_t id = 0;
 
    int32_t i  = 0;
    int32_t ret = -1;

    GTP_DEBUG_FUNC();

    ret = GTP_I2C_Read(client_addr, point_data, 12);//10?ֽڼĴ?????2?ֽڵ?ַ
    if (ret < 0)
    {
        GTP_ERROR("I2C transfer error. errno:%d\n ", ret);

        return;
    }
    
    finger = point_data[GTP_ADDR_LENGTH];//״̬?Ĵ???????

    if (finger == 0x00)		//û?????ݣ??˳?
    {
        return;
    }

    if((finger & 0x80) == 0)//?ж?buffer statusλ
    {
        goto exit_work_func;//????δ????????????Ч
    }

    touch_num = finger & 0x0f;//????????
    if (touch_num > GTP_MAX_TOUCH)
    {
        goto exit_work_func;//????????֧?ֵ??????????˳?
    }

    if (touch_num > 1)//??ֹһ????
    {
        uint8_t buf[8 * GTP_MAX_TOUCH] = {(GTP_READ_COOR_ADDR + 10) >> 8, (GTP_READ_COOR_ADDR + 10) & 0xff};

        ret = GTP_I2C_Read(client_addr, buf, 2 + 8 * (touch_num - 1));
        memcpy(&point_data[12], &buf[2], 8 * (touch_num - 1));			//?????????????????ݵ?point_data
    }

    
    
    if (pre_touch>touch_num)				//pre_touch>touch_num,??ʾ?еĵ??ͷ???
    {
        for (i = 0; i < pre_touch; i++)						//һ????һ???㴦??
         {
            uint8_t j;
           for(j=0; j<touch_num; j++)
           {
               coor_data = &point_data[j * 8 + 3];
               id = coor_data[0] & 0x0F;									//track id
              if(pre_id[i] == id)
                break;

              if(j >= touch_num-1)											//??????ǰ????id???Ҳ???pre_id[i]????ʾ???ͷ?
              {
                 GTP_Touch_Up( pre_id[i]);
              }
           }
       }
    }


    if (touch_num)
    {
        for (i = 0; i < touch_num; i++)						//һ????һ???㴦??
        {
            coor_data = &point_data[i * 8 + 3];

            id = coor_data[0] & 0x0F;									//track id
            pre_id[i] = id;

            input_x  = coor_data[1] | (coor_data[2] << 8);	//x????
            input_y  = coor_data[3] | (coor_data[4] << 8);	//y????
            input_w  = coor_data[5] | (coor_data[6] << 8);	//size
        
            {
                GTP_Touch_Down( id, input_x, input_y, input_w);//???ݴ???
            }
        }
    }
    else if (pre_touch)		//touch_ num=0 ??pre_touch??=0
    {
      for(i=0;i<pre_touch;i++)
      {
          GTP_Touch_Up(pre_id[i]);
      }
    }


    pre_touch = touch_num;


exit_work_func:
    {
        ret = GTP_I2C_Write(client_addr, end_cmd, 3);
        if (ret < 0)
        {
            GTP_INFO("I2C write end_cmd error!");
        }
    }

}


/**
  * @brief   ??????оƬ???¸?λ
  * @param ??
  * @retval ??
  */
 int8_t GTP_Reset_Guitar(void)
{
    GTP_DEBUG_FUNC();
#if 1
    I2C_ResetChip();
    return 0;
#else 		//??????λ
    int8_t ret = -1;
    int8_t retry = 0;
    uint8_t reset_command[3]={(uint8_t)GTP_REG_COMMAND>>8,(uint8_t)GTP_REG_COMMAND&0xFF,2};

    //д?븴λ????
    while(retry++ < 5)
    {
        ret = GTP_I2C_Write(GTP_ADDRESS, reset_command, 3);
        if (ret > 0)
        {
            GTP_INFO("GTP enter sleep!");

            return ret;
        }

    }
    GTP_ERROR("GTP send sleep cmd failed.");
    return ret;
#endif

}



 /**
   * @brief   ????˯??ģʽ
   * @param ??
   * @retval 1Ϊ?ɹ???????Ϊʧ??
   */
//int8_t GTP_Enter_Sleep(void)
//{
//    int8_t ret = -1;
//    int8_t retry = 0;
//    uint8_t reset_comment[3] = {(uint8_t)(GTP_REG_COMMENT >> 8), (uint8_t)GTP_REG_COMMENT&0xFF, 5};//5
//
//    GTP_DEBUG_FUNC();
//
//    while(retry++ < 5)
//    {
//        ret = GTP_I2C_Write(GTP_ADDRESS, reset_comment, 3);
//        if (ret > 0)
//        {
//            GTP_INFO("GTP enter sleep!");
//
//            return ret;
//        }
//
//    }
//    GTP_ERROR("GTP send sleep cmd failed.");
//    return ret;
//}


int8_t GTP_Send_Command(uint8_t command)
{
    int8_t ret = -1;
    int8_t retry = 0;
    uint8_t command_buf[3] = {(uint8_t)(GTP_REG_COMMAND >> 8), (uint8_t)GTP_REG_COMMAND&0xFF, GTP_COMMAND_READSTATUS};

    GTP_DEBUG_FUNC();

    while(retry++ < 5)
    {
        ret = GTP_I2C_Write(GTP_ADDRESS, command_buf, 3);
        if (ret > 0)
        {
            GTP_INFO("send command success!");

            return ret;
        }

    }
    GTP_ERROR("send command fail!");
    return ret;
}

/**
  * @brief   ???Ѵ?????
  * @param ??
  * @retval 0Ϊ?ɹ???????Ϊʧ??
  */
int8_t GTP_WakeUp_Sleep(void)
{
    uint8_t retry = 0;
    int8_t ret = -1;

    GTP_DEBUG_FUNC();

    while(retry++ < 10)
    {
        ret = GTP_I2C_Test();
        if (ret > 0)
        {
            GTP_INFO("GTP wakeup sleep.");
            return ret;
        }
        GTP_Reset_Guitar();
    }

    GTP_ERROR("GTP wakeup sleep failed.");
    return ret;
}

static int32_t GTP_Get_Info(void)
{
    uint8_t opr_buf[6] = {0};
    int32_t ret = 0;

    uint16_t abs_x_max = GTP_MAX_WIDTH;
    uint16_t abs_y_max = GTP_MAX_HEIGHT;
    uint8_t int_trigger_type = GTP_INT_TRIGGER;
        
    opr_buf[0] = (uint8_t)((GTP_REG_CONFIG_DATA+1) >> 8);
    opr_buf[1] = (uint8_t)((GTP_REG_CONFIG_DATA+1) & 0xFF);
    
    ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 6);
    if (ret < 0)
    {
        return FAIL;
    }
    
    abs_x_max = (opr_buf[3] << 8) + opr_buf[2];
    abs_y_max = (opr_buf[5] << 8) + opr_buf[4];
    
    opr_buf[0] = (uint8_t)((GTP_REG_CONFIG_DATA+6) >> 8);
    opr_buf[1] = (uint8_t)((GTP_REG_CONFIG_DATA+6) & 0xFF);
    
    ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 3);
    if (ret < 0)
    {
        return FAIL;
    }
    int_trigger_type = opr_buf[2] & 0x03;
    
    GTP_INFO("X_MAX = %d, Y_MAX = %d, TRIGGER = 0x%02x",
            abs_x_max,abs_y_max,int_trigger_type);
    
    return SUCCESS;    
}

/*******************************************************
Function:
    Initialize gtp.
Input:
    ts: goodix private data
Output:
    Executive outcomes.
        0: succeed, otherwise: failed
*******************************************************/
 int32_t GTP_Init_Panel(void)
{
    int32_t ret = -1;

    GTP_DEBUG_FUNC();


    I2C_Touch_Init();

    ret = GTP_I2C_Test();
    if (ret < 0)
    {
        GTP_ERROR("I2C communication ERROR!");
				return ret;
    } 
		
		//??ȡ????IC???ͺ?
    GTP_Read_Version(); 

		
	 /*ʹ???жϣ????????ܼ??ⴥ??????*/

    ret = LOS_HwiCreate(TP_IRQ, 0, 0, GTP_IRQHandler, 0);
    if (ret != 0) {
        printf("ret of TP_IRQ LOS_HwiCreate = %#x\n", ret);
        return 0;
    }else{
        printf("TP_IRQ LOS_HwiCreate  ok");
    }
	I2C_GTP_IRQEnable();
	
    GTP_Get_Info();

    return 0;
}


/*******************************************************
Function:
    Read chip version.
Input:
    client:  i2c device
    version: buffer to keep ic firmware version
Output:
    read operation return.
        2: succeed, otherwise: failed
*******************************************************/
int32_t GTP_Read_Version(void)
{
    int32_t ret = -1;
    uint8_t buf[8] = {GTP_REG_VERSION >> 8, GTP_REG_VERSION & 0xff};    //?Ĵ?????ַ

    GTP_DEBUG_FUNC();

    ret = GTP_I2C_Read(GTP_ADDRESS, buf, sizeof(buf));
    if (ret < 0)
    {
        GTP_ERROR("GTP read version failed");
        return ret;
    }

    if (buf[4] == '1')
    {				
				//GT911оƬ
				if(buf[2] == '9' && buf[3] == '1' && buf[4] == '1')
        {
          GTP_INFO("IC1 Version: %c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[7], buf[6]);

					touchIC = GT911;
          /* ???õ?ǰ??Һ???????? */
          // cur_lcd = INCH_7;
        }
        //GT9157оƬ
        else
           GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
		}
		else if (buf[4] == '5')
		{
			if( buf[2] == '9' && buf[3] == '1' && buf[4] == '5' && buf[5] == '7')
        {
          GTP_INFO("IC2 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);

					touchIC = GT9157;
          /* ???õ?ǰ??Һ???????? */
          // cur_lcd = INCH_5;
        }
        //GT615оƬ
        else if( buf[2] == '6' && buf[3] == '1' && buf[4] == '5')
        {
          GTP_INFO("IC3 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);

					touchIC = GT615;
          /* ???õ?ǰ??Һ???????? */
          // cur_lcd = INCH_7;
        }
        else
           GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);

    }    
    else if (buf[4] == '8')
    {	
				//GT5688оƬ
				if(buf[2] == '5' && buf[3] == '6' && buf[4] == '8' && buf[5] == '8')
        {
          GTP_INFO("IC4 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);

					touchIC = GT5688;
          /* ???õ?ǰ??Һ???????? */
          // cur_lcd = INCH_4_3;
        }
        else
           GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);

    }
		else if(buf[4] == '7')
    {
			  //GT917SоƬ
         GTP_INFO("IC5 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
				
				if(buf[2] == '9' && buf[3] == '1' && buf[4] == '7' && buf[5] == 'S')
				{	
					touchIC = GT917S; 
					/* ???õ?ǰ??Һ???????? */
          // cur_lcd = INCH_5;	
				}					
    }
    else 
       GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);

    return ret;
}

/*******************************************************
Function:
    I2c test Function.
Input:
    client:i2c client.
Output:
    Executive outcomes.
        2: succeed, otherwise failed.
*******************************************************/
static int8_t GTP_I2C_Test( void)
{
    uint8_t test[3] = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};
    uint8_t retry = 0;
    int8_t ret = -1;

    GTP_DEBUG_FUNC();
  
    while(retry++ < 5)
    {
        ret = GTP_I2C_Read(GTP_ADDRESS, test, 3);
        if (ret > 0)
        {
            return ret;
        }
        GTP_ERROR("GTP i2c test failed time %d.",retry);
    }
    return ret;
}

//???⵽?????ж?ʱ???ã?
void GTP_TouchProcess(void)
{
  GTP_DEBUG_FUNC();
  Goodix_TS_Work_Func();

}


void GTP_IRQHandler(void)
{
    printf("GTP_IRQHandler enter\n");
    if(__HAL_GPIO_EXTI_GET_IT(GTP_INT_GPIO_PIN) != RESET) //ȷ???Ƿ???????EXTI Line?ж?
    {
        // LED2_TOGGLE;
        GTP_TouchProcess();    
        __HAL_GPIO_EXTI_CLEAR_IT(GTP_INT_GPIO_PIN);     //?????жϱ?־λ
    }  
    printf("GTP_IRQHandler exit\n");
}