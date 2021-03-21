# sem<a name="EN-US_TOPIC_0312409051"></a>

## Function<a name="en-us_topic_0175230548_section676257315176"></a>

The  **sem** command is used to query the information about semaphores of Huawei LiteOS Kernel.

## Format<a name="en-us_topic_0175230548_section3096931815176"></a>

sem \[_ID_\]

sem fulldata

## Parameter Description<a name="en-us_topic_0175230548_section2805486115176"></a>

**Table  1**  Parameter description

<a name="en-us_topic_0175230548_table5785124015176"></a>
<table><thead align="left"><tr id="en-us_topic_0175230548_row3935748315176"><th class="cellrowborder" valign="top" width="21.099999999999998%" id="mcps1.2.4.1.1"><p id="en-us_topic_0175230548_p3383958815176"><a name="en-us_topic_0175230548_p3383958815176"></a><a name="en-us_topic_0175230548_p3383958815176"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.32%" id="mcps1.2.4.1.2"><p id="en-us_topic_0175230548_p5665211315176"><a name="en-us_topic_0175230548_p5665211315176"></a><a name="en-us_topic_0175230548_p5665211315176"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.58%" id="mcps1.2.4.1.3"><p id="en-us_topic_0175230548_p2541845915176"><a name="en-us_topic_0175230548_p2541845915176"></a><a name="en-us_topic_0175230548_p2541845915176"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230548_row4562928915176"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230548_p498493215176"><a name="en-us_topic_0175230548_p498493215176"></a><a name="en-us_topic_0175230548_p498493215176"></a>ID</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230548_p112632315176"><a name="en-us_topic_0175230548_p112632315176"></a><a name="en-us_topic_0175230548_p112632315176"></a>Semaphore ID. The value can be expressed in decimal or hexadecimal format.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230548_p55594668143150"><a name="en-us_topic_0175230548_p55594668143150"></a><a name="en-us_topic_0175230548_p55594668143150"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
<tr id="en-us_topic_0175230548_row1166922524814"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230548_p26701425154813"><a name="en-us_topic_0175230548_p26701425154813"></a><a name="en-us_topic_0175230548_p26701425154813"></a>fulldata</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230548_p3769105924816"><a name="en-us_topic_0175230548_p3769105924816"></a><a name="en-us_topic_0175230548_p3769105924816"></a>Print all semaphore information in use: SemID, Count, Original Count, Creater TaskEntry, Last Access Time</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230548_p5670132534810"><a name="en-us_topic_0175230548_p5670132534810"></a><a name="en-us_topic_0175230548_p5670132534810"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0175230548_section338301615176"></a>

-   Parameter displays the usage number and total number of semaphore.
-   If an ID is added, when the  **ID**  value falls in the range \[0,1023\], the usage number of the specified semaphore will be displayed. \(A prompt will be displayed if the semaphore specified by the ID is not in use.\) A prompt indicating a parameter error will be displayed if the parameter value is outside the range \[0,1023\].
-   The parameter ID and fulldata cannot be used together.
-   The  **fulldata**  parameter depends on  **LOSCFG\_DEBUG\_SEMAPHORE**. You can run the  **make menuconfig**  command to enable the  **Enable Semaphore Debugging**  menu item.

    ```
    Debug  ---> Enable a Debug Version ---> Enable Debug LiteOS Kernel Resource ---> Enable Semaphore Debugging
    ```


## Examples<a name="en-us_topic_0175230548_section4315602815176"></a>

Example 1: enter  **sem 1**.

Example 2: enter  **sem** and **sem fulldata**.

## Output<a name="en-us_topic_0175230548_section1440763015176"></a>

Run  **sem 1**  to query the command output.

```
Huawei LiteOS # sem 1
   SemID       Count
   ----------  -----
   0x00000001      0x1
No task is pended on this semphore!
```

Run the  **sem**  and  **sem fulldata**  commands to query information about all semaphores in use.

```
Huawei LiteOS # sem
   SemID       Count
   ----------  -----
   0x00000000  1
   SemID       Count
   ----------  -----
   0x00000001  1
   SemID       Count
   ----------  -----
   0x00000002  1
   SemUsingNum   : 3

Huawei LiteOS # sem fulldata
Used Semaphore List:
   SemID   Count   OriginalCout   Creater(TaskEntry)   LastAccessTime
   ------  -----   ------------   -----------------    --------------
   0x2     0x1     0x1            0x80164d70           0x3
   0x0     0x1     0x1            0x0                  0x3
   0x1     0x1     0x1            0x0                  0x3
```

