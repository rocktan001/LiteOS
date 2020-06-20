/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Header file containing struct prototypes of sensor.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 * --------------------------------------------------------------------------- */
#ifndef _SENSORS_H
#define _SENSORS_H

#include "los_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define PDC_SIZE 28

typedef struct {
    UINT8 busType;
    UINT8 busNum;
    UINT8 i2cAddress;
    UINT8 axisMapX;     /* axis map{0,1,2} */
    UINT8 axisMapY;     /* axis map{0,1,2} */
    UINT8 axisMapZ;     /* axis map{0,1,2} */
    UINT8 negateX;      /* negate_map{0,1} */
    UINT8 negateY;      /* negate_map{0,1} */
    UINT8 negateZ;      /* negate_map{0,1} */
    UINT8 gpioInt;      /* INT GPIO number */
    UINT16 pollInterval;
    INT32 offsetX;      /* offset_x save */
    INT32 offsetY;      /* offset_y save */
    INT32 offsetZ;      /* offset_z save */
} AccSensorPlatformData;

typedef struct {
    UINT8 busType;
    UINT8 busNum;
    UINT8 exist;
    UINT8 i2cAddress;
    UINT8 axisMapX;  /* axis map{0,1,2} */
    UINT8 axisMapY;  /* axis map{0,1,2} */
    UINT8 axisMapZ;  /* axis map{0,1,2} */
    UINT8 negateX;   /* negate_map{0,1} */
    UINT8 negateY;   /* negate_map{0,1} */
    UINT8 negateZ;   /* negate_map{0,1} */
    UINT8 gpioInt1;  /* INT1 GPIO number */
    UINT8 gpioInt2;  /* INT2 GPIO number */
    UINT16 pollInterval;
    UINT16 reserved;
} GyroPlatformData;

typedef struct {
    UINT8 busType;
    UINT8 busNum;
    UINT8 i2cAddress;
    UINT8 axisMapX;          /* axis map{0,1,2} */
    UINT8 axisMapY;          /* axis map{0,1,2} */
    UINT8 axisMapZ;          /* axis map{0,1,2} */
    UINT8 negateX;           /* negate_map{0,1} */
    UINT8 negateY;           /* negate_map{0,1} */
    UINT8 negateZ;           /* negate_map{0,1} */
    UINT8 outBit;            /* outbit for akm8963.0-14bit,1--16bit */
    UINT8 gpioDrdy;          /* DRDY_INT GPIO number */
    UINT8 gpioRst;           /* reset GPIO number */
    UINT8 pdcData[PDC_SIZE]; /* PDC for soft magnetic calibration */
    UINT16 pollInterval;
    UINT16 reserved;
} CompassPlatformData;

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _SENSORS_H */
