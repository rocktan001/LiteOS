# dlock<a name="EN-US_TOPIC_0312409053"></a>

## Function<a name="en-us_topic_0298978858_section292522625313"></a>

The  **dlock**  command is used to check whether a task mutex deadlock occurs in the system. The command output displays all the tasks in the system with mutex information.

## Format<a name="en-us_topic_0298978858_section219137125319"></a>

dlock

## User Guide<a name="en-us_topic_0298978858_section11147121921813"></a>

-   **LOSCFG\_DEBUG\_DEADLOCK** must be enabled before this command is executed. You can run the  **make menuconfig**  command to enable  **Enable Mutex Deadlock Debugging**.

    ```
    Debug ---> Enable a Debug Version ---> Enable Debug LiteOS Kernel Resource ---> Enable Mutex Deadlock Debugging
    ```

-   The output of the  **dlock**  command is the information of tasks without mutex when it exceeds the time threshold \(10 minutes by default\). However, it does not indicate that deadlock occurs on all these tasks. You need to further confirm the deadlock based on the mutex information and task call stack information.

## Example<a name="en-us_topic_0298978858_section38825106556"></a>

Enter  **dlock**.

## Output<a name="en-us_topic_0298978858_section2127155445310"></a>

If no task deadlock occurs in the system, the following information is displayed:

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

When a deadlock occurs in the system, the following information is displayed:

```
Huawei LiteOS # dlock
Start mutexs deadlock check:
Task_name:SendToSer, ID:0x0, holds the Mutexs below:
null
*******backtrace begin*******
********backtrace end********

Task_name:WowWriteFlashTask, ID:0x3, holds the Mutexs below:
null
*******backtrace begin*******
********backtrace end********

Task_name:system_wq, ID:0x4, holds the Mutexs below:
null
*******backtrace begin*******
********backtrace end********

Task_name:app_Task, ID:0x5, holds the Mutexs below:
<Mutex0 info>
Ptr handle:0x8036104c
Owner:app_Task
Count:1
Pended task: 0. name:mutexDlock_Task, id:0xc
*******backtrace begin*******
********backtrace end********

Task_name:Swt_Task, ID:0x6, holds the Mutexs below:
null
*******backtrace begin*******
*******backtrace begin*******
traceback 0 -- lr = 0x4    fp = 0x0
********backtrace end********

Task_name:IdleCore000, ID:0x7, holds the Mutexs below:
null
*******backtrace begin*******
********backtrace end********

Task_name:eth_irq_Task, ID:0xb, holds the Mutexs below:
null
*******backtrace begin*******
********backtrace end********

Task_name:mutexDlock_Task, ID:0xc, holds the Mutexs below:
<Mutex0 info>
Ptr handle:0x80361060
Owner:mutexDlock_Task
Count:1
Pended task: 0. name:app_Task       , id:0x5
*******backtrace begin*******
********backtrace end********

-----------End-----------
```

The output items are described as follows:

-   "Task\_name:_xxx_, ID:_xxx_, holds the Mutexs below" indicates the name and ID of the task that is suspected to be deadlocked. The information in the following lines is the mutex information of the task.  **null**  indicates that the task does not have mutex information.
-   "<Mutex_N_  info\>" are followed by lines of detailed information about the mutex as follows.

    <a name="en-us_topic_0298978858_table15310135019130"></a>
    <table><thead align="left"><tr id="en-us_topic_0298978858_row731015011313"><th class="cellrowborder" valign="top" width="31.169999999999998%" id="mcps1.1.3.1.1"><p id="en-us_topic_0298978858_p83119508137"><a name="en-us_topic_0298978858_p83119508137"></a><a name="en-us_topic_0298978858_p83119508137"></a>Output Item</p>
    </th>
    <th class="cellrowborder" valign="top" width="68.83%" id="mcps1.1.3.1.2"><p id="en-us_topic_0298978858_p8311450181319"><a name="en-us_topic_0298978858_p8311450181319"></a><a name="en-us_topic_0298978858_p8311450181319"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="en-us_topic_0298978858_row14311165014136"><td class="cellrowborder" valign="top" width="31.169999999999998%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0298978858_p143112050191314"><a name="en-us_topic_0298978858_p143112050191314"></a><a name="en-us_topic_0298978858_p143112050191314"></a>Ptr handle</p>
    </td>
    <td class="cellrowborder" valign="top" width="68.83%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0298978858_p11311750141315"><a name="en-us_topic_0298978858_p11311750141315"></a><a name="en-us_topic_0298978858_p11311750141315"></a>Address of the control block of the mutex.</p>
    </td>
    </tr>
    <tr id="en-us_topic_0298978858_row3311250161311"><td class="cellrowborder" valign="top" width="31.169999999999998%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0298978858_p1031113505136"><a name="en-us_topic_0298978858_p1031113505136"></a><a name="en-us_topic_0298978858_p1031113505136"></a>Owner</p>
    </td>
    <td class="cellrowborder" valign="top" width="68.83%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0298978858_p13112050141318"><a name="en-us_topic_0298978858_p13112050141318"></a><a name="en-us_topic_0298978858_p13112050141318"></a>Name of the task with the mutex.</p>
    </td>
    </tr>
    <tr id="en-us_topic_0298978858_row19311125021318"><td class="cellrowborder" valign="top" width="31.169999999999998%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0298978858_p183119506134"><a name="en-us_topic_0298978858_p183119506134"></a><a name="en-us_topic_0298978858_p183119506134"></a>Count</p>
    </td>
    <td class="cellrowborder" valign="top" width="68.83%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0298978858_p03115508132"><a name="en-us_topic_0298978858_p03115508132"></a><a name="en-us_topic_0298978858_p03115508132"></a>Reference count of the mutex.</p>
    </td>
    </tr>
    <tr id="en-us_topic_0298978858_row83111050181311"><td class="cellrowborder" valign="top" width="31.169999999999998%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0298978858_p1831119504132"><a name="en-us_topic_0298978858_p1831119504132"></a><a name="en-us_topic_0298978858_p1831119504132"></a>Pended Task</p>
    </td>
    <td class="cellrowborder" valign="top" width="68.83%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0298978858_p931165019134"><a name="en-us_topic_0298978858_p931165019134"></a><a name="en-us_topic_0298978858_p931165019134"></a>Name of the task that is waiting for the mutex. If no task is waiting for the mutex, the value is <strong id="en-us_topic_0298978858_b5670425113211"><a name="en-us_topic_0298978858_b5670425113211"></a><a name="en-us_topic_0298978858_b5670425113211"></a>null</strong>.</p>
    </td>
    </tr>
    </tbody>
    </table>


