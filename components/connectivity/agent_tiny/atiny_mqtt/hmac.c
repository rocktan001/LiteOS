/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2021. All rights reserved.
 * Description: Hmac
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

#include "hmac.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/platform.h"
#include "md_wrap.h"
#include "mbedtls/md.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

int mbedtls_hmac_calc(mbedtls_hmac_t *hmac_info)
{
    int ret;

    mbedtls_md_context_t mbedtls_md_ctx;
    const mbedtls_md_info_t *md_info;

    if ((hmac_info == NULL) || (hmac_info->secret == NULL) || (hmac_info->input == NULL)
        || (hmac_info->secret_len <= 0) || (hmac_info->input_len <= 0)
        || (hmac_info->digest_len <= 0)) {
        return MBEDTLS_ERR_MD_BAD_INPUT_DATA;
    }

    md_info = mbedtls_md_info_from_type(hmac_info->hmac_type);
    if ((md_info == NULL) || (md_info->size > hmac_info->digest_len)) {
        return MBEDTLS_ERR_MD_BAD_INPUT_DATA;
    }

    mbedtls_md_init(&mbedtls_md_ctx);
    memset(hmac_info->digest, 0x00, hmac_info->digest_len);

    ret = mbedtls_md_setup(&mbedtls_md_ctx, md_info, 1);
    if (ret != 0) {
        printf("mbedtls_md_setup() returned -0x%04x\n", -ret);
        mbedtls_md_free(&mbedtls_md_ctx);
        return ret;
    }

    (void)mbedtls_md_hmac_starts(&mbedtls_md_ctx, hmac_info->secret, hmac_info->secret_len);
    (void)mbedtls_md_hmac_update(&mbedtls_md_ctx, hmac_info->input, hmac_info->input_len);
    (void)mbedtls_md_hmac_finish(&mbedtls_md_ctx, hmac_info->digest);

    mbedtls_md_free(&mbedtls_md_ctx);
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
