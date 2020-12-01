# shell使用教程


## 使用场景
shell命令可以通过串口工具输入输出。用户可以新增定制的命令，新增命令需重新编译烧录后才能执行。

## 编译shell
shell功能默认关闭，可以通过`make menuconfig`打开shell组件的开关。
```
Debug --> Enable a Debug Version --> Enable Shell --> Functionality of Shell --> Select shell functionality -->  Enable full functionality of shell
```

## 开发流程

### 新增Shell命令的开发流程

1. **创建shell命令处理函数**

   shell命令处理函数用于处理用户注册的命令，例如创建一个命令处理函数osShellCmdTest，可以打印新增命令的入参：
   ```
   #include "stdio.h"
   UINT32 osShellCmdTest(UINT32 argc, CHAR **argv)
   {
       printf("this is a shell test\n");
       if (argc == 1) {
           printf("test cmd arg 1 is %s\n", argv[0]);
       } else if (argc == 2) {
           printf("test cmd arg 2 is %s %s\n", argv[0], argv[1]);
       } else if (argc > 2) {
           printf("input error\n");
       }
       return 0;
   }
   ```

   在头文件中声明命令处理函数：
   ```
   UINT32 osShellCmdTest(UINT32 argc, CHAR **argv);
   ```

   下面介绍示例中的两个入参：
   ##### argc
   -  shell命令中参数的个数。
   -  个数中是否包括命令名，和注册命令时的命令类型有关。
   ##### argv
   -  执行shell命令时传入命令处理函数的参数。
   -  参数中是否包括命令名，和注册命令时的命令类型有关。

2. **注册命令**

   有两种命令注册方式。下面以注册一个名为“test”的命令为例，介绍命令注册的方法。“test”命令的处理函数就是上面例子中的osShellCmdTest()函数：

   -  **静态注册命令**
      ```
      #include "shcmd.h"
      SHELLCMD_ENTRY(testShellcmd, CMD_TYPE_EX, "test", XARGS, (CMD_CBK_FUNC)osShellCmdTest)
      ```
   -  **系统运行时动态注册命令**
      ```
      #include "shell.h"
      osCmdReg(CMD_TYPE_EX, "test", XARGS, (CMD_CBK_FUNC)osShellCmdTest);
      ```

    下面介绍注册命令函数的入参。
    ##### 静态注册的命令变量名
    -  静态注册命令比动态注册命令，增加了一个命令变量名，用于设置链接选项。
    -  命令变量名只要符合变量的命名规范即可，无其他要求。
    -  需要在链接选项（build/mk/liteos_tables_ld.mk的LITEOS_TABLES_LDFLAGS变量）中增加此命令变量名，例如示例中的变量名为`testShellcmd`，链接选项就应该设置为：`LITEOS_TABLES_LDFLAGS += -utestShellcmd`。

    ##### 命令类型
    支持两种命令类型：
    -  **CMD_TYPE_EX** 不支持标准命令参数输入，会把用户填写的命令名屏蔽掉，例如在串口输入`test -a -b`，传入命令处理函数的只有参数`-a`和`-b`，分别对应于命令处理函数中的`argv[0]`和`argv[1]`。

    -  **CMD_TYPE_STD** 支持标准命令参数输入，所有输入的字符都会通过命令解析后被传入，例如输入`test -a -b`，会把`test`，`-a`，`-b`都传入命令处理函数，分别对应于命令处理函数中的`argv[0]`，`argv[1]`，`argv[2]`。

    ##### 命令名
    -  在shell中调用命令处理函数的命令名，符合变量的命名规范即可，例如示例中的`test`就是命令处理函数`osShellCmdTest`在串口中输入的命令名。

    ##### 命令处理函数的最大参数个数
    -  静态注册命令暂不支持设置。
    -  动态注册命令支持设置不超过32的最大参数个数，或者设置为宏定义`XARGS`（其在代码中被定义为`0xffffffff`）表示不限制参数个数。

    ##### (CMD_CBK_FUNC)osShellCmdTest
    -  命令处理函数名，即在shell中被执行的函数。

    **注意：**
    -  静态注册命令方式一般用在系统常用命令注册，动态注册命令一般用在用户命令注册。

    -  命令名必须是唯一的，两个不同的命令处理函数不能有相同的命令名，否则只会执行其中一个。

### 执行Shell命令

通过串口终端工具（比如xShell），连接串口。

选择SERIAL协议，然后配置SERIAL：选择对应的串口号，设置波特率为115200。

连接后重启开发板。
```
********Hello Huawei LiteOS********

LiteOS Kernel Version : 5.0.0-rc1
build data : Nov 25 2020 01:24:06

**********************************
osAppInit
cpu 0 entering scheduler

Huawei LiteOS #
```

这时可以输入命令，按`回车键`执行命令。

按`Tab键`可自动补全。

按`退格键`可删除一个字符。

按`方向键上下`可选择历史命令。

## 内置命令

### help

##### 命令功能
help命令用于显示当前操作系统内所有shell命令。

##### 命令格式
```
help
```

##### 参数说明
无。

##### 使用示例

```
Huawei LiteOS # help
*******************shell commands:*************************

cpup          date          dlock         dmesg         free          help          hwi
log           memcheck      mutex         queue         sem           stack         swtmr
systeminfo    task          uname         watch

```

### cpup
##### 命令功能
查询系统CPU的占用率。

##### 命令格式
```
cpup [mode] [taskID]
```

##### 参数说明
|参数|参数说明|取值范围|
|:---:|:---|:---:|
|mode|缺省：显示系统最近10s的CPU占用率<br>0：显示系统最近10s的CPU占用率<br>1：显示系统最近1s的CPU占用率<br>其他数字：显示系统启动至今总的CPU占用率<br>以上都是以百分比显示的占用率| [0,0xFFFF]<br>或0xFFFFFFFF|
|taskID|任务ID号|[0,0xFFFF]或0xFFFFFFFF|

##### 使用指南
-  参数缺省时，显示系统最近10s的CPU占用率。

-  只输入一个参数时，该参数为mode，显示系统相应时间的CPU占用率。

-  输入两个参数时，第一个参数为mode，第二个参数为taskID，显示指定任务ID的任务在相应时间的CPU占用率。

##### 使用示例
```
Huawei LiteOS # cpup

SysCpuUsage in 10s: 69.2

Huawei LiteOS # cpup 0

SysCpuUsage in 10s: 71.0

Huawei LiteOS # cpup 1

SysCpuUsage in 1s: 98.0

Huawei LiteOS # cpup 2

SysCpuUsage in all time: 75.9
```
### date
##### 命令功能
查询及设置系统时间。

##### 命令格式
```
date

date --help

date +Format

date -s YY/MM/DD

date -s hh:mm:ss

date -r Filename(暂不支持)
```

##### 参数说明
参数|参数说明|取值范围|
|:---:|:---|:---:|
|--help|使用帮助|
|+Format|根据Format格式打印时间|--help中列出的占位符|
|-s YY/MM/DD|设置系统时间，用“/”分割的年月日|>= 1970/01/01|
|-s hh\:mm\:ss|设置系统时间，用“:”分割的时分秒|
|-r|查询文件修改时间（暂不支持）|

##### 使用指南
-  date参数缺省时，默认显示当前系统时间。
-  --help、+Format、-s、-r不能混合使用。

##### 使用示例
```
Huawei LiteOS # date
Fri Jan  2 07:05:54 1970


Huawei LiteOS # date --help

Usage: date [+FORMAT]
   or: date [-s] [YY/MM/DD] [hh:mm:ss]
Display the current time in the given FORMAT, or set the system date.
FORMAT controls the output.  Interpreted sequences are:
  %b     The abbreviated month name according to the current locale.
  %B     The full month name according to the current locale.
  %C     The century number (year/100) as a 2-digit integer. (SU)
  %d     The day of the month as a decimal number (range 01 to 31).
  %e     Like %d, the day of the month as a decimal number, 
         but a leading zero is replaced by a space.
  %h     Equivalent to %b.  (SU)
  %H     The hour as a decimal number using a 24-hour clock (range 00 to 23).
  %I     The hour as a decimal number using a 12-hour clock (range 01 to 12).
  %j     The day of the year as a decimal number (range 001 to 366).
  %k     The hour (24-hour clock) as a decimal number (range  0  to  23); 
         single digits are preceded by a blank.  (See also %H.)  (TZ)
  %l     The hour (12-hour  clock) as a decimal number (range 1 to 12); 
         single digits are preceded by a blank.  (See also %I.)  (TZ)
  %m     The month as a decimal number (range 01 to 12).
  %M     The minute as a decimal number (range 00 to 59).
  %n     A newline character. (SU)
  %p     Either "AM" or "PM" according to the given time value, 
         or the corresponding strings for the current locale.
         Noon is treated as "PM" and midnight as "AM".
  %P     Like %p but in lowercase: "am" or "pm" 
         or a corresponding string for the current locale. (GNU)
  %s     The number of seconds since the Epoch, that is,
         since 1970-01-01 00:00:00 UTC. (TZ)
  %S     The second as a decimal number (range 00 to 60).
         (The range is up to 60 to allow for occasional leap seconds.)
  %t     A tab character. (SU)
  %y     The year as a decimal number without a century (range 00 to 99).
  %Y     The year as a decimal number including the century.
  %%     A literal '%' character.

Examples:
Set system date (2017-01-01)
$ date -s 2017/01/01
Set system time (12:00:00)
$ date -s 12:00:00
Show the time with format Year-Month-Day
$ date +%Y-%m-%d
```

### free
##### 命令功能
显示系统内存的使用情况，同时显示系统的text段、data段、rodata段、bss段大小。

##### 命令格式
```
free [-k | -m]
```

##### 参数说明
|参数|参数说明|取值范围|
|:---:|:---|:---:|
|无参数|以Byte为单位显示|
|-k|以KByte为单位显示|
|-m|以MByte为单位显示|

##### 使用指南
-  输入free显示内存使用情况，total表示系统动态内存池的总大小，used表示已使用的内存大小，free表示空闲的内存大小。text表示代码段大小，data表示数据段大小，rodata表示只读数据段大小，bss表示未初始化全局变量占用的内存大小。
-  free命令可以以三种单位来显示内存使用情况，包括Byte、KByte和MByte。

##### 使用示例
```
Huawei LiteOS # free

        total        used          free
Mem:    183748       72200         111548

        text         data          rodata        bss
Mem:    61728        472           14776         5572

Huawei LiteOS # free -k

        total        used          free
Mem:    179          70            108

        text         data          rodata        bss
Mem:    60           0             14            5
```

### log
##### 命令功能
设置&查询系统的日志打印等级。

##### 命令格式
```
log level [levelNum]
```
暂时不支持指定模块和文件。

##### 参数说明
参数|参数说明|取值范围
|:---:|:---|:---:|
|levelNum|设置日志打印等级|[0x0，0x5]|

##### 使用指南
-  该命令需使能`LOSCFG_SHELL_LK`，使能方式可以通过`make menuconfig`在配置项中开启`Enable Shell lk`。
    ```
    Debug --> Enable a Debug Version --> Enable Shell --> Functionality of Shell --> Enable Shell lk
    ```
-  `log level`命令用于设置系统的日志打印等级，包括5个等级。
    ```
    TRACE_EMG = 0,

    TRACE_COMMOM = 1,

    TRACE_ERROR = 2,

    TRACE_WARN = 3,

    TRACE_INFO = 4,

    TRACE_DEBUG = 5
    ```
-  若`log level`命令不加`levelNum`参数，则会显示系统当前的日志打印等级，并且提示使用方法。

##### 使用示例
```
Huawei LiteOS # log level 0
Set current log level EMG

Huawei LiteOS # log level 1
Set current log level COMMOM

Huawei LiteOS # log level 2
Set current log level ERR

Huawei LiteOS # log level 3
Set current log level WARN

Huawei LiteOS # log level 4
Set current log level INFO

Huawei LiteOS # log level 5
Set current log level DEBUG
```

### memcheck
##### 命令功能
检查动态申请的内存块是否完整，是否存在内存越界造成节点损坏。

##### 命令格式
```
memcheck
```

##### 参数说明
无。

##### 使用指南
-  需要在platform_config.h中添加：
   ```
   #define LOSCFG_BASE_MEM_NODE_INTEGRITY_CHECK       YES
   ```
   并通过`make menuconfig`在配置项中修改内存算法为`bestfit`。
   ```
   Kernel --> Memory Management --> Dynamic Memory Management Algorithm --> bestfit
   ```
-  当内存池所有节点完整时，输出"memcheck over, all passed!"。
-  当内存池存在节点不完整时，输出被损坏节点的内存块信息。

##### 使用示例
```
Huawei LiteOS # memcheck
system memcheck over, all passed!
```

### sem
##### 命令功能
查询系统内核信号量相关信息。

##### 命令格式
```
sem [ID] 
sem fulldata
```

##### 参数说明
参数|参数说明|取值范围
|:---:|:---|:---:|
|ID|信号ID号|[0, 0xFFFFFFFF]|
|fulldata|查询所有在用的信号量信息，打印信息包括：SemID, Count, Original Count, Creater TaskEntry, Last Access Time|

##### 使用指南
- 参数缺省时，显示所有信号量的使用数及信号量总数。
- sem后加ID，显示指定ID号的信号量的使用数。
- sem的ID参数在[0, 1023]范围内时，返回对应ID的信号量状态（如果对应ID的信号量未被使用则进行提示）；其他取值时返回参数错误的提示。
- sem的参数ID和fulldata不可以混用。
- 参数`fulldata`需使能`LOSCFG_DEBUG_SEMAPHORE`，使能方式可以通过`make menuconfig`在配置项中开启`Enable Semaphore Debugging`。
  ```
  Debug ---> Enable a Debug Version ---> Enable Debug LiteOS Kernel Resource ---> Enable Semaphore Debugging
  ```

##### 使用示例
```
Huawei LiteOS # sem 1
   SemID       Count
   ----------  -----
   0x00000001    0x1
No task is pended on this semphore!
```

### swtmr
##### 命令功能
查询系统软件定时器相关信息。

##### 命令格式
```
swtmr [ID]
```

##### 参数说明
|参数|参数说明|取值范围|
|:---:|:---|:---:|
|ID|软件定时器ID号|[0, 0xFFFFFFFF]|

##### 使用指南
-  参数缺省时，默认显示所有软件定时器的相关信息。
-  swtmr后加ID号时，显示指定ID号的软件定时器的相关信息。

##### 使用示例
```
Huawei LiteOS # swtmr

SwTmrID     State    Mode    Interval  Arg         handlerAddr
----------  -------  ------- --------- ----------  --------
0x00000000  Ticking  Period   1000     0x00000000  0x800442d

Huawei LiteOS # swtmr 1

The SwTimerID is not exist.

Huawei LiteOS # swtmr 0

SwTmrID     State    Mode    Interval  Arg         handlerAddr
----------  -------  ------- --------- ----------  --------
0x00000000  Ticking  Period   1000     0x00000000  0x800442d
```

### systeminfo
##### 命令功能
显示当前操作系统的资源使用情况，包括任务、信号量、互斥锁、队列、定时器等。

##### 命令格式
```
systeminfo
```

##### 参数说明
无。

##### 使用指南
systeminfo会显示各类资源的总数和已经被使用的数量。

##### 使用示例
```
Huawei LiteOS # systeminfo

   Module    Used      Total
--------------------------------
   Task      5         16
   Sem       0         20
   Mutex     1         20
   Queue     1         10
   SwTmr     1         16
```

### task
##### 命令功能
查询系统的任务信息。

##### 命令格式
```
task [ID]
```

##### 参数说明
|参数|参数说明|取值范围|
|:---:|:---|:---:|
|ID|任务ID号|[0, 0xFFFFFFFF]|

##### 使用指南
-  参数缺省时，默认打印全部运行任务信息。
-  task后加ID，显示指定ID号任务的任务名、任务ID。

##### 使用示例
```
Huawei LiteOS # task

Name                   TaskEntryAddr       TID    Priority   Status       StackSize    WaterLine    StackPoint  TopOfStack   EventMask  SemID       CPUUSE  CPUUSE10s  CPUUSE1s     MEMUSE
----                   -------------       ---    --------   --------     ---------    ----------   ----------  ----------   ---------  ----------  ------  ---------  --------     ------
agenttiny_task         0x8009819           0x0    2          Invalid      0x1000       0xfc         0x2001445c   0x20013528   0x0        0xffffffff     0.0        0.0       0.0          0
Swt_Task               0x8000c59           0x1    0          Pend         0x600        0x184        0x2000e1ac   0x2000dd28   0x0        0xffffffff     0.0        0.0       0.0          0
IdleCore000            0x80027dd           0x2    31         Ready        0x800        0x100        0x2000ea8c   0x2000e388   0x0        0xffffffff   89.91       58.7       0.0          0
SerialShellTask        0x8007d9d           0x4    9          Running      0x3000       0x850        0x2001239c   0x2000f508   0xfff      0xffffffff    78.9        0.0       0.0       1980
SerialEntryTask        0x80079e9           0x5    9          Pend         0x1000       0x610        0x2001332c   0x20012518   0x1        0xffffffff   68.72       58.7      80.2        368

Huawei LiteOS # task 1
TaskName = Swt_Task
TaskId = 0x1
```

### uname
##### 命令功能
显示操作系统的名称，系统编译时间，版本信息等。

##### 命令格式
```
uname [-a | -s | -t | -v | --help]
```

##### 参数说明
参数|参数说明
|:---:|:---|
|-a|显示全部信息|
|-s|显示操作系统名称|
|-t|显示系统的编译时间|
|-v|显示版本信息|
|--help|显示uname的帮助信息|

##### 使用指南
-  参数缺省时，默认显示操作系统名称。
-  `uname`的参数不能混合使用。

##### 使用示例
```
Huawei LiteOS # uname --help
-a,            print all information
-s,            print the kernel name
-t,            print the build date
-v,            print the kernel version

Huawei LiteOS # uname -a
Huawei LiteOS - Huawei LiteOS 5.0.0-rc1 Nov  2 2020 00:50:54
```

### watch
##### 命令功能
周期性监听一个命令的运行结果。

##### 命令格式
```
watch [-c | -n | -t | --count | --interval | -no-title | --over] [command]
```

##### 参数说明

|参数|参数说明|缺省值|取值范围|
|:---:|:---|:---|:---|
|-c / --count|命令执行的总次数|0xFFFFFF|（0,0xFFFFFF]|
|-n / --interval|命令周期性执行的时间间隔（s）|1s|（0,0xFFFFFF]|
|-t / -no-title|关闭顶端的时间显示|
|command|需要监听的Shell命令|
|--over|关闭当前的监听|

#### 使用指南
-  command参数必须是Shell命令，对于非Shell命令，会有错误提示“command is not fount”。
-  command是必填参数。
-  --over参数与其他参数不能混合使用。

##### 使用示例
```
Huawei LiteOS # watch -c 5 task 1

Huawei LiteOS # Thu Jan  1 16:26:26 1970

TaskName = Swt_Task
TaskId = 0x1
Thu Jan  1 16:26:27 1970

TaskName = Swt_Task
TaskId = 0x1
Thu Jan  1 16:26:28 1970

TaskName = Swt_Task
TaskId = 0x1
Thu Jan  1 16:26:29 1970

TaskName = Swt_Task
TaskId = 0x1
Thu Jan  1 16:26:30 1970

TaskName = Swt_Task
TaskId = 0x1
```

### dmesg
##### 命令功能
dmesg命令用于控制内核dmesg缓存区。

##### 命令格式
```
dmesg

dmesg [-c | -C | -D | -E | -L | -U]

dmesg -s size

dmesg -l level

dmesg > fileA(暂不支持)
```

##### 参数说明
|参数|参数说明|取值范围|
|:---:|:---|:---|
|-c|打印缓存区内容并清空缓存区|
|-C|清空缓存区|
|-D \| -E|关闭/开启控制台打印(暂不支持)|
|-s size|设置缓存区大小|
|-l level|设置缓存区的日志打印等级|0 -- 5|
|> fileA|将缓存区内容写入文件(暂不支持)|

##### 使用指南
-  该命令需使能`LOSCFG_SHELL_DMESG`，使能方式可以通过`make menuconfig`在配置项中开启`Enable Shell dmesg`。
```
Debug  ---> Enable a Debug Version---> Enable Shell ---> Functionality of Shell ---> Enable Shell dmesg
```
-  参数缺省时，默认打印缓存区内容。
-  参数均不能混合使用。

##### 使用示例
```
Huawei LiteOS # dmesg -s 10
Set dmesg buf size 10 success

Huawei LiteOS # dmesg -l 1
Set current dmesg log level COMMOM
```

### mutex
##### 命令功能

查看互斥锁使用情况。

##### 命令格式
```
mutex
```
##### 参数说明
无。
##### 使用指南
-  该命令需使能`LOSCFG_DEBUG_MUTEX`，使能方式可以通过`make menuconfig`在配置项中开启`Enable Mutex Debugging`。
  ```
  Debug ---> Enable a Debug Version ---> Enable Debug LiteOS Kernel Resource ---> Enable Mutex Debugging
  ```
##### 使用示例
```
Huawei LiteOS # mutex
used mutexs information: 
Mutex ID <0x0> may leak, Owner is null, TaskEntry of creator: 0x8000711,Latest operation time: 0x0
```

### dlock

##### 命令功能
互斥锁死锁检测时间阈值。
##### 命令格式
```
dlock
```
##### 参数说明
无。
##### 使用指南
-  该命令需使能`LOSCFG_DEBUG_DEADLOCK`，使能方式可以通过`make menuconfig`在配置项中开启`Enable Mutex Deadlock Debugging`。
  ```
  Debug ---> Enable a Debug Version ---> Enable Debug LiteOS Kernel Resource ---> Enable Mutex Deadlock Debugging
  ```
##### 使用示例
```
Huawei LiteOS # dlock
Start mutexs deadlock check:
Task_name:agenttiny_task, ID:0x0, holds the Mutexs below:
null
*******backtrace begin*******
********backtrace end********

Task_name:SerialShellTask, ID:0x4, holds the Mutexs below:
null
*******backtrace begin*******
********backtrace end********

-----------End-----------
```
### hwi
##### 命令功能
查询当前中断信息。

##### 命令格式
```
hwi
```
##### 参数说明
无。
##### 使用指南
-  输入hwi即显示当前中断号、中断次数及注册中断名称。
-  若打开宏开关`LOSCFG_CPUP_INCLUDE_IRQ`，还会显示各个中断的处理时间（cycles）、CPU占用率以及中断类型。`LOSCFG_CPUP_INCLUDE_IRQ`的使能方式可以通过`make menuconfig`在配置项中开启`Enable Cpup include irq`。
   ```
   Kernel --> Enable Cpup --> Enable Cpup include irq
   ```

##### 使用示例
**关闭LOSCFG_CPUP_INCLUDE_IRQ：**
```
Huawei LiteOS # hwi
 InterruptNo     Count     Name
       15:       975:
       53:         5:
      255: 536890416:      ?
```
**开启LOSCFG_CPUP_INCLUDE_IRQ：**
```
Huawei LiteOS # hwi
 InterruptNo     Count     Name         CYCLECOST   CPUUSE   CPUUSE10s    CPUUSE1s   mode
       15:       2719                   179278392   99.9      90.0        0.1        normal
       53:       5                      71929026    0.0       9.9         99.9       normal
      255:       536896560 ?            0           0.0       0.0         0.0        normal
```

### queue
##### 命令功能
可以查看队列使用情况。
##### 命令格式
```
queue
```
##### 参数说明
无。
##### 使用指南

-  该命令需使能`LOSCFG_DEBUG_QUEUE`，使能方式可以通过`make menuconfig`在配置项中开启`Enable Queue Debugging`。
   ```
   Debug  ---> Enable a Debug Version---> Enable Debug LiteOS Kernel Resource ---> Enable Queue Debugging
   ```

##### 使用示例

```
Huawei LiteOS # queue
used queues information:
Queue ID <0x0> may leak, queue len is 0x10, readable cnt:0x0, writeable cnt:0x10, TaskEntry of creator:0x0x80007d5, Latest operation time: 0x614271
```