

## LiteOS代码入口

LiteOS入口在工程对应的main.c中，基本流程如下：
```c
INT32 main(VOID)
{
    BoardConfig();
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

首先进行内存结束地址配置BoardConfig()，硬件初始化HardwareInit()，然后打印Huawei LiteOS的版本信息；

接着执行OsMain()初始化Huawei LiteOS内核及例程，在OsMain()函数中会创建用户任务，其任务处理函数为app_init()；

最后调用OsStart()开始任务调度，Huawei LiteOS开始正常工作。


## LiteOS的代码目录结构说明

关于代码树中各个目录存放的源代码的相关内容简介如下：

| 一级目录   | 二级目录                 | 三级目录              | 说明                                                         |
| ---------- | ------------------------ | --------------------- | ------------------------------------------------------------ |
| arch       | arm                      | cortex_a_r            | A核架构支持                                                  |
|            |                          | cortex_m              | M核架构支持                                                  |
|            | arm64                    |                       | arm64架构支持                                                |
|            | csky                     | cskyv2                | cskyv2架构支持                                                |
|            | riscv                    | rvm32                 | riscv架构支持                                                |
| build      |                          |                       | LiteOS编译系统需要的配置及脚本                               |
| compat     | cmsis                    |                       | liteos提供的CMSIS-RTOS 1.0和2.0接口                          |
| components | ai                       |                       | ai(基于mindspore)算子库实现                                  |
|            | connectivity             | agent_tiny            | agent_tiny端云互通组件，包括公共头文件、示例代码、客户端实现代码、操作系统适配层代码 |
|            |                          | lwm2m                 | lwm2m协议实现                                                |
|            |                          | mqtt                  | MQTT开源协议实现                                             |
|            |                          | nb_iot                | LiteOS NB-IoT API                                            |
|            | fs                       | devfs                 | devfs文件系统                                                 |
|            |                          | fatfs                 | fatfs文件系统                                                 |
|            |                          | kifs                  | kifs文件系统                                                  |
|            |                          | littlefs              | littlefs文件系统                                              |
|            |                          | ramfs                 | ramfs文件系统                                                 |
|            |                          | spiffs                | spiffs文件系统                                                |
|            |                          | vfs                   | 虚拟文件系统                                                  |
|            | gui                      |                       | 开源LittlevGL图形库                                          |
|            | language                 |                       | 语言相关组件，含lua                                             |
|            | lib                      | cjson                 | c语言json库                                                  |
|            | log                      |                       | 日志等级控制                                                 |
|            | media                    |                       | 媒体相关组件，含libpng、openexif、opus、upup、                   |
|            | net                      | at_device             | AT设备适配层                                                 |
|            |                          | at_frame              | LiteOS AT框架API                                             |
|            |                          | ifconfig              | ifconfig shell命令实现                                         |
|            |                          | los_iperf             | 网络带宽测试工具                                                |
|            |                          | lwip/lwip_port        | lwip驱动及OS适配代码                                         |
|            |                          | lwip/lwip-2.1.2       | lwip协议实现                                                 |
|            |                          | lwip/ppp_port         | lwip协议ppp端口支持                                          |
|            |                          | pcap                  | 网络抓包工具                                                 |
|            |                          | ping                  | ping shell命令实现                                           |
|            |                          | sal                   | socket通讯支持                                               |
|            |                          | tftp_server           | tftp服务                                                    |
|            | ota                      |                       | 固件升级代码                                                 |
|            | security                 | mbedtls/mbedtls_port  | mbed TLS的OS适配代码                                         |
|            |                          | mbedtls/mbedtl-2.16.8 | mbed TLS协议实现                                             |
|            |                          | openssl               | openssl协议                                                 |
|            | sensorhub                | include               | sensor manager头文件                                         |
|            |                          | src                   | sensor manager的源码实现                                     |
|            | utility                  |                       | 解析工具，含bidireference、curl、fastlz、freetype、harfbuzz、iconv、iniparser、json-c、jsoncpp、libxml2、sqlite、thttpd、tinyxml2  |
| demos      | agenttiny_lwm2m          |                       | lwm2m协议 demo                                               |
|            | agenttiny_mqtt           |                       | mqtt 协议demo                                                |
|            | ai                       |                       | ai的demo                                                     |
|            | dtls_server              |                       | dtls协议demo                                                 |
|            | fs                       |                       | 文件系统demo                                                 |
|            | gui                      |                       | gui的demo                                                    |
|            | ipv6_client              |                       | Ipv6协议demo                                                 |
|            | kernel                   | api                   | 供开发者测试LiteOS内核的demo示例代码                         |
|            |                          | include               | API功能头文件存放目录                                        |
|            | language                 |                       | 语言相关组件的demo                                               |
|            | lms                      |                       | LMS的demo                                                    |
|            | media                    |                       | 媒体相关组件的demo                                                   |
|            | nbiot_without_atiny      |                       | NB-IoT demo                                                  |
|            | sensorhub                | gyro                  | 基于sensorhub传感框架定时读取MPU6050陀螺仪原始数据的demo     |
|            | trace                    |                       | Trace的demo                                                  |
|            | utility                  |                       | 解析工具的demo                                               |
| doc        |                          |                       | 此目录存放的是LiteOS的使用文档和API说明等文档                |
| driver     | base                     |                       | LiteOS驱动框架                                              |
|            | interrupt                |                       | LiteOS系统中断接口                                           |
|            | timer                    |                       | LiteOS系统定时器接口                                          |
|            | uart                     |                       | LiteOS系统串口接口                                             |
| include    |                          |                       | components各个模块所依赖的头文件                             |
| kernel     | base                     |                       | LiteOS基础内核代码，包括任务、中断、软件定时器、队列、事件、信号量、互斥锁、tick等功能 |
|            |                          | debug                 | LiteOS内核调测代码，包括队列、信号量、互斥锁及任务调度的调测 |
|            |                          | include               | LiteOS基础内核内部使用的头文件                               |
|            |                          | mem                   | LiteOS中的内存管理相关代码                                   |
|            |                          | sched                 | 任务调度支持，包括对多核的调度支持                           |
|            |                          | shellcmd              | LiteOS中与基础内核相关的shell命令，包括memcheck、task、systeminfo、swtmr等 |
|            | extended                 | cppsupport            | C++兼容适配层底层接口                                        |
|            |                          | cpup                  | CPU占用率统计接口                                            |
|            |                          | include               | extended目录所需的头文件                                     |
|            |                          | lms                   | LMS（实时检测内存操作合法性算法）的库文件                    |
|            |                          | lowpower              | 低功耗框架相关代码                                           |
|            |                          | trace                 | trace事件跟踪，用于实时记录系统运行轨迹                      |
|            | include                  |                       | LiteOS开源内核头文件                                         |
|            | init                     |                       | LiteOS内核初始化相关代码                                     |
| lib        | huawei_libc              |                       | LiteOS自研libc库和适配的posix接口                            |
|            | libc                     |                       | LiteOS适配的musl libc库                                      |
|            | libsec                   |                       | 华为安全函数库                                               |
|            | zlib                     |                       | 开源zlib库                                                   |
| osdepends  | liteos                   |                       | LiteOS提供的部分OS适配接口                                   |
| shell      |                          | src                   | 实现shell命令的代码，支持基本调试功能                          |
|            |                          | include               | shell头文件                                                  |
| targets    | bsp                      |                       | 通用板级支持包                                               |
|            | CB2201                   |                       | CB2201（ck802）开发板的开发工程源码包                         |
|            | Cloud_STM32F429IGTx_FIRE |                       | 野火STM32F429（ARM Cortex M4）开发板的开发工程源码包           |
|            | GD32E103C_START          |                       | GD32E103C_START（ARM Cortex M4）开发板的开发工程源码包        |
|            | GD32F303RGT6_BearPi      |                       | GD32F303RGT6_BearPi（ARM Cortex M4）开发板的开发工程源码包    |
|            | GD32VF103V_EVAL          |                       | GD32VF103V_EVAL（riscv）开发板的开发工程源码包                |
|            | HiFive1_Rev1_B01         |                       | HiFive1_Rev1_B01（riscv）开发板的开发工程源码包                |
|            | qemu-virt-a53            |                       | Coretex A53的qemu开发工程源码包                              |
|            | realview-pbx-a9          |                       | Coretex A9的qemu开发工程源码包                               |
|            | STM32F072_Nucleo         |                       | STM32F072_Nucleo（ARM Cortex M0）开发板的开发工程源码包        |
|            | STM32F103_FIRE_Arbitrary |                       | 野火STM32F103（ARM Cortex M3）霸道开发板的开发工程源码包       |
|            | STM32F407_ATK_Explorer   |                       | 正点原子STM32F407（ARM Cortex M4）探索者开发板的开发工程源码包  |
|            | STM32F769IDISCOVERY      |                       | STM32F769IDISCOVERY（ARM Cortex M7）开发板的开发工程源码包     |
|            | STM32L4R9I_Discovery     |                       | STM32L4R9IDISCOVERY（ARM Cortex M4）开发板的开发工程源码包     |
|            | STM32L073_Nucleo         |                       | STM32L073_Nucleo（ARM Cortex M0+）开发板的开发工程源码包       |
|            | STM32L431_BearPi         |                       | 小熊派STM32L431（ARM Cortex M4）开发板的开发工程源码包          |
|            | STM32L476_NB476          |                       | 深创客STM32L476（ARM Cortex M4）开发板的开发工程源码包         |
|            | STM32L496_Nucleo         |                       | STM32L496 NUCLEO-144（ARM Cortex M4）开发板的开发工程源码包    |
|            | STM32L552_Nucleo         |                       | STM32L552 Nucleo（ARM Cortex M33）开发板的开发工程源码包       |
| tools      | build                    |                       | LiteOS支持的开发板编译配置文件                                |
|            | menuconfig               |                       | LiteOS编译所需的menuconfig脚本                               |
| Makefile   |                          |                       | LiteOS Makefile                                             |
| .config    |                          |                       | 开发板的配置文件，如果用户不重新选择开发板，默认为野火挑战者STM32F429开发板的配置文件 |



