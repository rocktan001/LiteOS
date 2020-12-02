# CORTEX A9在QEMU下运行LiteOS
## QEMU
### QEMU的安装
- QEMU是一个开源工具，有关QEMU的介绍可参考:<a href="https://github.com/qemu/qemu" target="_blank">https://github.com/qemu/qemu</a>

- 以Ubuntu Linux环境为例，如果未安装QEMU工具，可使用如下命令下载安装:
    ```
    $ apt-get install qemu
    $ apt-get install qemu-system
    ```

## Linux环境下以多核编译PBX A9
- 修改编译需要的`.config`文件为PBX A9的默认配置文件

    ```
    $ cp tools/build/config/realview-pbx-a9.config .config
    ```
- 使用`make`编译，默认配置开启了KERNEL SMP

    ```
    $ make clean; make -j
    ```

- 通过QEMU运行LiteOS

    ```
    $ qemu-system-arm -machine realview-pbx-a9 -smp 4 -m 512M out/realview-pbx-a9/Huawei_LiteOS.bin -nographic
    ```
### QEMU的参数说明
- 上面是启动guest虚拟机的命令，qemu命令行参数含义可以通过qemu-system-arm --help查看，其中常用参数含义如下：
    |参数|说明|
    |:---:|---|
    |-machine|表示qemu要仿真的虚拟机类型|
    |-smp|表示guest虚拟机的cpu的个数|
    |-m|为此guest虚拟机预留的内存大小，如果不指定，默认大小是128M|
    |-nographic|表示启动的是非图形界面|

- 开启KERNEL SMP后LiteOS启动打印信息如下所示：

    ```
    ********Hello Huawei LiteOS********

    Processor   : Cortex-A9 * 4
    Run Mode    : SMP
    GIC Rev     : unknown
    build time  : Dec  1 2020 04:17:44

    **********************************

    main core booting up...
    osAppInit
    releasing 3 secondary cores
    cpu 0 entering scheduler
    cpu 1 entering scheduler
    cpu 3 entering scheduler
    cpu 2 entering scheduler
    app_init

    Huawei LiteOS #
    ```

## Linux环境下以单核编译PBX A9

- 默认的配置开启了KERNEL SMP，如需关闭SMP则需在`make menuconfig`中关闭
    ```
    Kernel --> Enable Kernel SMP
    ```
- 编译后运行QEMU需要使用如下命令
    ```
    $ qemu-system-arm -machine realview-pbx-a9 -kernel out/realview-pbx-a9/Huawei_LiteOS.bin -nographic
    ```
- 关闭KERNEL SMP后LiteOS启动打印信息如下所示：
    ```
    ********Hello Huawei LiteOS********

    Processor   : Cortex-A9
    Run Mode    : UP
    GIC Rev     : unknown
    build time  : Dec  1 2020 04:26:08

    **********************************

    main core booting up...
    osAppInit
    cpu 0 entering scheduler
    app_init

    Huawei LiteOS #
    ```