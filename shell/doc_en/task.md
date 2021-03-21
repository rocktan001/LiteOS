# task<a name="EN-US_TOPIC_0312409045"></a>

## Function<a name="en-us_topic_0175230398_section676257315176"></a>

The  **task** command is used to query the information about tasks in Huawei LiteOS.

## Format<a name="en-us_topic_0175230398_section3096931815176"></a>

task \[_ID_\]

## Parameter Description<a name="en-us_topic_0175230398_section2805486115176"></a>

**Table  1**  Parameter description

<a name="en-us_topic_0175230398_table5785124015176"></a>
<table><thead align="left"><tr id="en-us_topic_0175230398_row3935748315176"><th class="cellrowborder" valign="top" width="21.099999999999998%" id="mcps1.2.4.1.1"><p id="en-us_topic_0175230398_p3383958815176"><a name="en-us_topic_0175230398_p3383958815176"></a><a name="en-us_topic_0175230398_p3383958815176"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.32%" id="mcps1.2.4.1.2"><p id="en-us_topic_0175230398_p5665211315176"><a name="en-us_topic_0175230398_p5665211315176"></a><a name="en-us_topic_0175230398_p5665211315176"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.58%" id="mcps1.2.4.1.3"><p id="en-us_topic_0175230398_p2541845915176"><a name="en-us_topic_0175230398_p2541845915176"></a><a name="en-us_topic_0175230398_p2541845915176"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230398_row4562928915176"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230398_p498493215176"><a name="en-us_topic_0175230398_p498493215176"></a><a name="en-us_topic_0175230398_p498493215176"></a>ID</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230398_p112632315176"><a name="en-us_topic_0175230398_p112632315176"></a><a name="en-us_topic_0175230398_p112632315176"></a>Task ID. The value can be expressed in decimal or hexadecimal format.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230398_p26357138173040"><a name="en-us_topic_0175230398_p26357138173040"></a><a name="en-us_topic_0175230398_p26357138173040"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0175230398_section338301615176"></a>

-   If the parameter is left unspecified, all task information will be printed by default.
-   If an ID added to the end of the  **task**  command is in the range of \[0, 64\], the task name, task ID, and call stack information \(a maximum of 15 call stacks are supported\) of the task with the specified ID are returned. If the task ID is not in the range of \[0, 64\], a parameter error message is returned. If the task corresponding to the specified ID is not created, the system displays a message.
-   If a task is in the  **Invalid**  state in the  **task**  command output, perform either of the following operations on  **pthread\_create**. Otherwise, resources cannot be properly reclaimed.
    -   Call the  **pthread\_join\(\)**  function in block mode.
    -   Call the  **pthread\_detach\(\)**  function in non-block mode.
    -   If you do not want to call the preceding two functions, set  **pthread\_attr\_t**  to  **PTHREAD\_STATE\_DETACHED**  and transfer the  **attr**  parameter to  **pthread\_create**. These operations are performed in non-block mode as well.


## Examples<a name="en-us_topic_0175230398_section4315602815176"></a>

Example 1: Enter  **task 6**.

Example 2: Enter  **task**.

## Output<a name="en-us_topic_0175230398_section1440763015176"></a>

Run the  **task 0xb**  command to query the information about the task whose ID is  **b**.

```
Huawei LiteOS # task 0xb
TaskName = SerialEntryTask
TaskId = 0xb
*******backtrace begin*******
traceback 0 -- lr = 0x1d804    fp = 0xa86bc
traceback 1 -- lr = 0x1da40    fp = 0xa86e4
traceback 2 -- lr = 0x20154    fp = 0xa86fc
traceback 3 -- lr = 0x258e4    fp = 0xa8714
traceback 4 -- lr = 0x242f4    fp = 0xa872c
traceback 5 -- lr = 0x123e4    fp = 0xa8754
traceback 6 -- lr = 0x2a9d8    fp = 0xb0b0b0b
```

Run the  **task**  command to query information about all tasks:

```
Huawei LiteOS # task
Name          TaskEntryAddr    TID   Priority  Status     StackSize  WaterLine  StackPoint  TopOfStack EventMask SemID  CPUUSE  CPUUSE10s  CPUUSE1s MEMUSE
----          ------------     ---   -------   --------   ---------  --------   ----------  ---------- -------  -----  -------  ---------  ------  -------
Swt_Task          0x40002770   0x0    0        QueuePend  0x6000     0x2cc     0x4015a318  0x401544e8  0x0      0xffff    0.0       0.0     0.0     0
IdleCore000       0x40002dc8   0x1    31       Ready      0x400      0x15c     0x4015a7f4  0x4015a550  0x0      0xffff   98.6      98.2    99.9     0
system_wq         0x400b80fc   0x3    1        Pend       0x6000     0x244     0x40166928  0x40160ab8  0x1      0xffff    0.0       0.0     0.0     0
SerialShellTask   0x40090158   0x5    9        Running    0x3000     0x55c     0x40174918  0x40171e70  0xfff    0xffff    1.2       1.7     0.0     48
SerialEntryTask   0x4008fe30   0x6    9        Pend       0x1000      0x2c4    0x40175c78  0x40174e88  0x1      0xffff    0.0       0.0     0.0     72
```

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>1.  Description of output items
>    -   **Name**: Task name.
>    -   **TID**: Task ID.
>    -   **Priority**: Priority of a task.
>    -   **Status**: Status of the current task.
>    -   **StackSize**: Size of a task stack.
>    -   **WaterLine**: Occupied memory of a task stack.
>    -   **StackPoint**: Start address of a task stack.
>    -   **TopOfStack**: Address of stack top.
>    -   **EventMask**: Event mask of current task, default even mask of task that is not used is 0. \(If there are many events used in task, the recently used one will be displayed\).
>    -   **SemID**: Semaphore ID that current task owned, default semaphore ID that is not used is 0xFFFF. \(If there are many semaphores used in task, the recently used one will be displayed\).
>    -   **CPUUSE**: CPU usage since startup.
>    -   **CPUUSE10s**: CPU usage in the last 10 seconds.
>    -   **CPUUSE1s**: CPU usage in the last second.
>    -   **MEMUSE**: Size of memory that is allocated till now, with unit byte. The counting of  **MEMUSE**  refers to system memory pool. The memory used by operations that take place during an interrupt and any memory processed before task scheduling starts will not be counted.
>        If memory is allocated to tasks, the  **MEMUSE**  value increases. If tasks release memory, the  **MEMUSE**  value decreases. The value of  **MEMUSE**  can be positive or negative.
>        \(1\) If no memory is allocated to tasks, or the allocated memory equals the released memory, the  **MEMUSE**  value is 0.
>        \(2\) If the  **MEMUSE**  value is positive, some memory is not released by the task.
>        \(3\) If the  **MEMUSE**  value is negative, the released memory is larger than the allocated memory.
>2.  Description of initial system tasks in Huawei LiteOS
>    -   **Swt\_Task**: Software timer task, which is used to process the timeout callback function for software timers.
>    -   **IdleCore000**: Task that is executed when Huawei LiteOS is idle.
>    -   **system\_wq**: Default work queue for processing tasks.
>    -   **SerialEntryTask**: Reads user input from the lower-layer buf and preliminarily parses a command, such as arrow keys and command completion by pressing  **Tab**.
>    -   **SerialShellTask**: Further parses the command sent by cmdParesTask and calls the registration function that matches the command.
>3.  Description of task status
>    -   **Ready**: The task is ready.
>    -   **Pend**: The task is pending.
>    -   **PendTime**: The pending task timed out.
>    -   **Suspend**: The task is suspended.
>    -   **Running**: The task is running.
>    -   **Delay**: The task is delayed.
>    -   **SuspendTime**: The suspended task timed out.
>    -   **Invalid**: The task is not in any of the preceding states.

