/*----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Board HeadFile
 * Author: Huawei LiteOS Team
 * Create: 2013-01-01
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

#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

// error code
#define OTA_ERRNO_OK                0
#define OTA_ERRNO_ILEGAL_PARAM      (-1)
#define OTA_ERRNO_INTEGRITY_CHECK   (-2)
#define OTA_ERRNO_SPI_FLASH_READ    (-3)
#define OTA_ERRNO_SPI_FLASH_WRITE   (-4)
#define OTA_ERRNO_INNER_FLASH_READ  (-5)
#define OTA_ERRNO_INNER_FLASH_WRITE (-6)
#define OTA_ERRNO_ILEGAL_PC         (-7)
#define OTA_ERRNO_ILEGAL_STACK      (-8)
#define OTA_ERRNO_INTERNEL          (-9)

// SPI flash address
#define OTA_FLAG_ADDR1                0x00000000
#define OTA_FLAG_ADDR2                0x00004000
#define MQTT_INFO_ADDR                0x00008000
#define MQTT_INFO_SIZE                0x00008000
#define OTA_IMAGE_DOWNLOAD_ADDR       (MQTT_INFO_ADDR + MQTT_INFO_SIZE)
#define OTA_IMAGE_DOWNLOAD_SIZE       0x00040000 // new image size: 256K
#define OTA_IMAGE_BCK_ADDR            (OTA_IMAGE_DOWNLOAD_ADDR + OTA_IMAGE_DOWNLOAD_SIZE) // backup firmware address
#define OTA_IMAGE_BCK_SIZE            0x00040000
#define OTA_IMAGE_DIFF_UPGRADE_ADDR   (OTA_IMAGE_BCK_ADDR + OTA_IMAGE_BCK_SIZE)
#define OTA_IMAGE_DIFF_UPGRADE_SIZE   0x00040000

// Built in flash address
#define OTA_DEFAULT_IMAGE_ADDR        0x08010000

int jumpToApp(uint32_t binSize);
int ImgUpdateCopy(int32_t old_image_len, int32_t new_image_len, uint32_t new_image_addr);
int ImgRollbackCopy(int32_t image_len);

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _BOARD_H */