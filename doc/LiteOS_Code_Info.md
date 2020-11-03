

## LiteOS代码入口

LiteOS入口在工程对应的main.c中，基本流程如下：
```
INT32 main(VOID)
{
    HardwareInit();

    PRINT_RELEASE("\n********Hello Huawei LiteOS********\n"
                  "\nLiteOS Kernel Version : %s\n"
                  "build data : %s %s\n\n"
                  "**********************************\n",
                  HW_LITEOS_KERNEL_VERSION_STRING, __DATE__, __TIME__);

    UINT32 ret = OsMain();
    if (ret != LOS_OK) {
        return LOS_NOK;
    }

    OsStart();

    return 0;
}
```

首先进行硬件初始化：HardwareInit();

然后调用PRINT_RELEASE打印LiteOS内核版本号及编译时间信息;

接着初始化LiteOS内核及例程：OsMain();

最后调用OsStart()开始task调度，LiteOS开始正常工作。


## LiteOS的代码目录结构说明

关于代码树中各个目录存放的源代码的相关内容简介如下：

| 一级目录   | 二级目录                 | 三级目录             | 说明                                                          |
| ---------- | ------------------------ | -------------------- | ------------------------------------------------------------  |
| arch       | arm                      | cortex_a_r           | A核架构支持                                                   |
|            |                          | cortex_m             | M核架构支持                                                   |
|            | arm64                    |                      | arm64架构支持                                                 |
|            | msp430                   |                      | msp430架构中断、调度、tick相关代码                            |
| build      |                          |                      | LiteOS编译系统需要的配置及脚本                                |
| compat     | cmsis                    |                      | liteos提供的CMSIS-RTOS 1.0和2.0接口                           |
| components | connectivity             | agent_tiny           | agent_tiny端云互通组件，包括公共头文件、示例代码、客户端实现代码、操作系统适配层代码 |
|            |                          | lwm2m                | lwm2m协议实现                                                |
|            |                          | mqtt                 | MQTT开源协议实现                                             |
|            |                          | nb_iot               | LiteOS NB-IoT API                                            |
|            | fs                       |                      | 文件系统，含VFS、spiffs、ramfs、kifs、fatfs、devfs           |
|            | gui                      | lvgl                 | 开源LittlevGL的源码                                          |
|            | lib                      | cJSON                | c语言json库                                                  |
|            | log                      |                      | 日志等级控制                                                 |
|            | net                      | at_device            | AT设备适配层                                                 |
|            |                          | at_frame             | LiteOS AT框架API                                             |
|            |                          | lwip/lwip_port       | lwip驱动及OS适配代码                                         |
|            |                          | lwip/lwip-2.0.3      | lwip协议实现                                                 |
|            |                          | lwip/ppp_port        | lwip协议ppp端口支持                                          |
|            |                          | sal                  | socket通讯支持                                               |
|            | ota                      |                      | 固件升级代码                                                 |
|            | security                 | mbedtls/mbedtls_port | mbed TLS的OS适配代码                                         |
|            |                          | mbedtls/mbedtl-2.6.0 | mbed TLS协议实现                                             |
|            | sensorhub                | include              | sensor manager头文件                                         |
|            |                          | src                  | sensor manager的源码实现                                     |
| demos      | agenttiny_lwm2m          |                      | lwm2m协议 demo                                               |
|            | agenttiny_mqtt           |                      | mqtt 协议demo                                                |
|            | dtls_server              |                      | dtls协议demo                                                 |
|            | fs                       |                      | 文件系统demo                                                 |
|            | gui                      |                      | gui的demo                                                    |
|            | ipv6_client              |                      | Ipv6协议demo                                                 |
|            | kernel                   | api                  | 供开发者测试LiteOS内核的demo示例代码                           |
|            |                          | include              | API功能头文件存放目录                                        |
|            | nbiot_without_atiny      |                      | NB_IoT demo                                                  |
|            | sensorhub                | gyro                 | 基于sensorhub传感框架定时读取MPU6050陀螺仪原始数据的demo           |
| doc        |                          |                      | 此目录存放的是LiteOS的使用文档和API说明等文档                |
| include    |                          |                      | components各个模块所依赖的头文件                             |
| kernel     | base                     |                      | LiteOS基础内核代码，包括任务、中断、软件定时器、队列、事件、信号量、互斥锁、tick等功能 |
|            |                          | debug                | LiteOS内核调测代码，包括队列、信号量、互斥锁及任务调度的调测 |
|            |                          | include              | LiteOS基础内核内部使用的头文件                               |
|            |                          | mem                  | LiteOS中的内存管理相关代码                                   |
|            |                          | sched                | 任务调度支持                                                 |
|            |                          | shellcmd             | LiteOS中与基础内核相关的shell命令，包括memcheck、task、systeminfo、swtmr等 |
|            | extended                 | cppsupport           | C++兼容适配层底层接口                                        |
|            |                          | cpup                 | CPU占用率统计接口                                            |
|            |                          | include              | extended目录所需的头文件                                     |
|            |                          | tickless             | tickless定时机制实现                                         |
|            |                          | trace                | trace事件跟踪，用于实时记录系统运行轨迹                      |
|            | include                  |                      | LiteOS开源内核头文件                                         |
| lib        | huawei_libc              |                      | LiteOS自研libc库和适配的posix接口                            |
|            | libc                     |                      | LiteOS适配的musl libc库                                      |
|            | libsec                   |                      | 华为安全函数库                                               |
|            | zlib                     |                      | 开源zlib库                                                   |
| osdepends  | liteos                   |                      | LiteOS提供的部分OS适配接口                                   |
| targets    | bsp                      |                      | 通用板级支持包                                               |
|            | Cloud_STM32F429IGTx_FIRE |                      | 野火STM32F429（ARM Cortex M4）开发板的开发工程源码包         |
|            | STM32F769IDISCOVERY      |                      | STM32F769IDISCOVERY（ARM Cortex M7）开发板的开发工程源码包    |
|            | STM32L431_BearPi         |                      | 小熊派STM32L431（ARM Cortex M4）开发板的开发工程源码包        |
| tests      |                          |                      | 内核及系统库的参考测试代码                                    |
| tools      | build                    |                      | LiteOS支持的开发板编译配置文件                                |
|            | menuconfig               |                      | LiteOS编译所需的menuconfig脚本                               |
|            | stackusage               |                      | LiteOS栈使用估算工具                                         |
| Makefile   |                          |                      | LiteOS Makefile                                             |
| .config    |                          |                      | 开发板的配置文件，如果用户不重新选择开发板，默认为野火挑战者STM32F429开发板的配置文件 |
