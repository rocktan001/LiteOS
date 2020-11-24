# NB IOT

LiteOS提供一套NB IOT的组件和例程。目前支持通过AT指令控制BC95 NB IOT模块连接云服务。

## 接口介绍

### NB IOT初始化函数
```
int los_nb_init(const int8_t *host, const int8_t *port, sec_param_s *psk);
```
- host：服务器IP地址
- port：服务器端口
- psk：加密所用的证书或秘钥，如不加密则为空。

### NB IOT发送函数
```
int los_nb_report(const char *buf, int buflen);
```
- buf：待上报数据指针
- buflen：待上报数据长度

### NB IOT注册函数
```
int los_nb_notify(char *featurestr, int cmdlen, oob_callback callback, oob_cmd_match cmd_match);
```
- featurestr：要注册的AT命令
- cmdlen：要注册的AT命令长度
- callback：设备回调函数
- cmd_match：命令处理函数

### NB IOT取消注册函数
```
int los_nb_deinit(void);
```

### NB IOT DEMO
```
void demo_nbiot_only(void);
```

## NB IOT DEMO的配置
- 在demos/nbiot_without_atiny/nb_demo.c中有如下配置
```
#define TELECON_IP          "119.3.250.80"
#define SECURITY_PORT       "5684"
#define NON_SECURITY_PORT   "5683"
#define DEV_PSKID           "868744031131026"
#define DEV_PSK             "d1e1be0c05ac5b8c78ce196412f0cdb0"
```
- TELECON_IP：NBIOT服务器IP地址
- SECURITY_PORT：加密端口
- NON_SECURITY_PORT：非加密端口
- DEV_PSKID：预共享秘钥ID
- DEV_PSK：预共享秘钥

**注意**

-  在使用demo时需要将以上配置修改为自己的服务器信息，并在云端绑定设备。

-  需要将BC95模块插入支持NBIOT的物联网卡，并连接到对应的串口上。

-  需要在`menuconfig`中打开相应配置
```
Demos --> NBIOT Demo Without Atiny --> Enable NBIOT Demo
```
-  如需加密则打开
```
Demos --> NBIOT Demo Without Atiny --> Enable NBIOT at dtls
```
-  同时在at设备中选择
```
Components --> Network --> Enable Network --> Enable AT --> Choose AT Device --> Enable bc95
```