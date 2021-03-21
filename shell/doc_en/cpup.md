# cpup<a name="EN-US_TOPIC_0312409059"></a>

## Function<a name="en-us_topic_0175230345_section676257315176"></a>

The  **cpup** command is used to query the CPU usage in a percentage.

## Format<a name="en-us_topic_0175230345_section3096931815176"></a>

cpup \[_mode_\] \[_taskID_\]

## Parameter Description<a name="en-us_topic_0175230345_section2805486115176"></a>

**Table  1**  Parameter description

<a name="en-us_topic_0175230345_table5785124015176"></a>
<table><thead align="left"><tr id="en-us_topic_0175230345_row3935748315176"><th class="cellrowborder" valign="top" width="21.099999999999998%" id="mcps1.2.4.1.1"><p id="en-us_topic_0175230345_p3383958815176"><a name="en-us_topic_0175230345_p3383958815176"></a><a name="en-us_topic_0175230345_p3383958815176"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.32%" id="mcps1.2.4.1.2"><p id="en-us_topic_0175230345_p5665211315176"><a name="en-us_topic_0175230345_p5665211315176"></a><a name="en-us_topic_0175230345_p5665211315176"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.58%" id="mcps1.2.4.1.3"><p id="en-us_topic_0175230345_p2541845915176"><a name="en-us_topic_0175230345_p2541845915176"></a><a name="en-us_topic_0175230345_p2541845915176"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230345_row4562928915176"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230345_p498493215176"><a name="en-us_topic_0175230345_p498493215176"></a><a name="en-us_topic_0175230345_p498493215176"></a>mode</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><a name="en-us_topic_0175230345_ul11870718153533"></a><a name="en-us_topic_0175230345_ul11870718153533"></a><ul id="en-us_topic_0175230345_ul11870718153533"><li>Default: displays the CPU usage in the last 10 seconds.</li><li><strong id="en-us_topic_0175230345_b1414365735415"><a name="en-us_topic_0175230345_b1414365735415"></a><a name="en-us_topic_0175230345_b1414365735415"></a>0</strong>: displays the CPU usage in the last 10 seconds.</li><li><strong id="en-us_topic_0175230345_b1086495945415"><a name="en-us_topic_0175230345_b1086495945415"></a><a name="en-us_topic_0175230345_b1086495945415"></a>1</strong>: displays the CPU usage in the last second.</li><li>Other value: displays the CPU usage since Huawei LiteOS is started.</li></ul>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230345_p31410743143155"><a name="en-us_topic_0175230345_p31410743143155"></a><a name="en-us_topic_0175230345_p31410743143155"></a>[0,0xFFFF]</p>
<p id="en-us_topic_0175230345_p14261236143155"><a name="en-us_topic_0175230345_p14261236143155"></a><a name="en-us_topic_0175230345_p14261236143155"></a>or 0xFFFFFFFF</p>
</td>
</tr>
<tr id="en-us_topic_0175230345_row3741643292421"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230345_p120357692421"><a name="en-us_topic_0175230345_p120357692421"></a><a name="en-us_topic_0175230345_p120357692421"></a>taskID</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230345_p3038082892421"><a name="en-us_topic_0175230345_p3038082892421"></a><a name="en-us_topic_0175230345_p3038082892421"></a>Task ID</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230345_p56026989173356"><a name="en-us_topic_0175230345_p56026989173356"></a><a name="en-us_topic_0175230345_p56026989173356"></a>[0,0xFFFF]</p>
<p id="en-us_topic_0175230345_p34480858173356"><a name="en-us_topic_0175230345_p34480858173356"></a><a name="en-us_topic_0175230345_p34480858173356"></a>or 0xFFFFFFFF</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0175230345_section338301615176"></a>

-   By default, the system displays the CPU usage in the latest 10 seconds.
-   If parameter is only one, and the parameter is mode, the CPU usage percent of system corresponding time ago will be displayed.
-   If two parameters are passed in, and the first one is mode, the second one is taskID. The CPU usage percent of system with the specific task ID corresponding time ago will be displayed.
-   To enable this function, you need to enable the CPU usage module by running  **make menuconfig**. The menu path is as follows:

    ```
    Kernel ---> Enable Extend Kernel ---> Enable Cpup
    ```

    For more information about the CPU usage module, see  [CPU Usage](/doc/LiteOS_Maintenance_Guide_en/cpu-usage.md#EN-US_TOPIC_0312244419).


## Example<a name="en-us_topic_0175230345_section4315602815176"></a>

Enter  **cpup 1 1**.

## Output<a name="en-us_topic_0175230345_section1440763015176"></a>

Run the  **cpup 1 1**  command to display the CPU usage of the task whose ID is 1 in the last 1s.

```
Huawei LiteOS # cpup 1 1
TaskId 1 CpuUsage in 1s: 78.7
```

