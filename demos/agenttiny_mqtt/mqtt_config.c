/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Mqtt Config Implementation
 * Author: Huawei LiteOS Team
 * Create: 2021-09-10
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

#include "mqtt_config.h"
#include <string.h>
#include "agent_tiny_mqtt_demo.h"
#include "mqtt_client.h"

#ifdef LOSCFG_COMPONENTS_SECURITY_MBEDTLS
#ifdef LOSCFG_DTLS_PSK_ENCRYPT
static char *g_serverPort = "8883";
#define AGENT_TINY_DEMO_PSK_LEN (3)
static char *g_pskId = "testID";
uint8_t g_psk[AGENT_TINY_DEMO_PSK_LEN] = {0xab, 0xcd, 0xef};

#elif defined(LOSCFG_DTLS_CERT_ENCRYPT)

static char *g_serverPort = "8883";
static char g_deviceCert[] =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\r\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\r\n"
"QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\r\n"
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\r\n"
"b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\r\n"
"9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\r\n"
"CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\r\n"
"nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\r\n"
"43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\r\n"
"T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\r\n"
"gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\r\n"
"BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\r\n"
"TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\r\n"
"DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\r\n"
"hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\r\n"
"06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\r\n"
"PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\r\n"
"YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\r\n"
"CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\r\n"
"-----END CERTIFICATE-----\r\n";
#else /* MQTT_DEMO_USE_PSK */
static char *g_serverPort = "1883";
#endif /* NO_USE_CERT_OR_PSK */
#else 
static char *g_serverPort = "1883";
#endif /* LOSCFG_COMPONENTS_SECURITY_MBEDTLS */

static char *g_serverIp = "121.36.42.100";

static char *g_secret = "c6f16270c5bbf00063ab";
static char *g_productId = "60d32ce25f880902bcb28a40";
static char *g_deviceId = "60d32ce25f880902bcb28a40_testID1";
static char *g_nodeId = "testID1";
static char *g_time = "2021090703";

uint8_t MQTT_GetConnectType(void)
{
    return MQTT_STATIC_CONNECT;
}

uint8_t MQTT_GetSecureType(void)
{
    return MQTT_STATIC_CONNECT;
}

void MQTT_GetServerIp(char **serverIp, uint8_t *serverIpLen)
{
   *serverIp = g_serverIp;
   *serverIpLen = sizeof(g_serverIp);
}

void MQTT_GetServerPort(char **serverPort, uint8_t *serverPortLen)
{
   *serverPort = g_serverPort;
   *serverPortLen = sizeof(g_serverPort);
}

void MQTT_GetConnectDeviceId(char **deviceId, uint16_t *deviceIdLen)
{
    *deviceId = g_deviceId;
    *deviceIdLen = strlen(g_deviceId);
}

void MQTT_GetConnectProductId(char **productId, uint16_t *productIdLen)
{
    *productId = g_productId;
    *productIdLen = strlen(g_productId);
}

void MQTT_GetConnectNodeId(char **nodeId, uint16_t *nodeIdLen)
{
    *nodeId = g_nodeId;
    *nodeIdLen = strlen(g_nodeId);
}

void MQTT_GetConnectPwd(char **pwd, uint16_t *pwdLen)
{
    *pwd = g_secret;
    *pwdLen = strlen(g_secret);
}

void MQTT_GetCurrentRealTime(char **time, uint16_t *timeLen)
{
    *time = g_time;
    *timeLen = strlen(g_time);
}

#if defined (LOSCFG_DTLS_CERT_ENCRYPT)
void MQTT_GetConnectSecureCaCrt(char **ca, uint32_t *caLen)
{
    *ca = g_deviceCert;
    *caLen = sizeof(g_deviceCert); // ca length: sizeof(g_mqttCaCrt)
}
#endif /* LOSCFG_DTLS_CERT_ENCRYPT */

#if defined (LOSCFG_DTLS_PSK_ENCRYPT)
void MQTT_GeConnectSecurePsk(uint8_t **pskId, uint32_t *pskIdLen, uint8_t **psk, uint32_t *pskLen)
{
    *pskId = g_pskId;
    *pskIdLen = strlen(pskId);
    *psk = g_psk;
    pskLen = strlen(psk); 
}
#endif /* LOSCFG_DTLS_PSK_ENCRYPT */