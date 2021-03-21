# log<a name="EN-US_TOPIC_0312409056"></a>

## Function<a name="en-us_topic_0175230447_section676257315176"></a>

The  **log** command is used to query & modify log print level.

## Format<a name="en-us_topic_0175230447_section3096931815176"></a>

log level \[_levelNum_\]

## Parameter Description<a name="en-us_topic_0175230447_section2805486115176"></a>

**Table  1**  Parameter Description

<a name="en-us_topic_0175230447_table5785124015176"></a>
<table><thead align="left"><tr id="en-us_topic_0175230447_row3935748315176"><th class="cellrowborder" valign="top" width="21.099999999999998%" id="mcps1.2.4.1.1"><p id="en-us_topic_0175230447_p3383958815176"><a name="en-us_topic_0175230447_p3383958815176"></a><a name="en-us_topic_0175230447_p3383958815176"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.32%" id="mcps1.2.4.1.2"><p id="en-us_topic_0175230447_p5665211315176"><a name="en-us_topic_0175230447_p5665211315176"></a><a name="en-us_topic_0175230447_p5665211315176"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.58%" id="mcps1.2.4.1.3"><p id="en-us_topic_0175230447_p2541845915176"><a name="en-us_topic_0175230447_p2541845915176"></a><a name="en-us_topic_0175230447_p2541845915176"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230447_row4562928915176"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230447_p498493215176"><a name="en-us_topic_0175230447_p498493215176"></a><a name="en-us_topic_0175230447_p498493215176"></a>levelNum</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230447_p4200868294541"><a name="en-us_topic_0175230447_p4200868294541"></a><a name="en-us_topic_0175230447_p4200868294541"></a>config log print level</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230447_p1578335115176"><a name="en-us_topic_0175230447_p1578335115176"></a><a name="en-us_topic_0175230447_p1578335115176"></a>[0x0,0x5]</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-notice.gif) **NOTICE:** 
>
>Configuration of module and path are not supported now.

## User Guide<a name="en-us_topic_0175230447_section338301615176"></a>

-   This command depends on  **LOSCFG\_SHELL\_LK**. You can run  **make menuconfig**  to enable  **Enable Shell lk**.

    ```
    Debug  ---> Enable a Debug Version ---> Enable Shell ---> Enable Shell lK
    ```

-   **log level**  command is used to config log print level which includes the following 6 levels:

    TRACE\_EMG = 0

    TRACE\_COMMOM = 1

    TRACE\_ERROR = 2

    TRACE\_WARN = 3

    TRACE\_INFO = 4

    TRACE\_DEBUG = 5

-   If  **log level**  has not \[**levelNum**\] parameter, it will print the current log level by default and display the usage information.

## Example<a name="en-us_topic_0175230447_section4315602815176"></a>

Enter  **log level 4**.

## Output<a name="en-us_topic_0175230447_section1440763015176"></a>

Run the  **log level 4**  command to set the log level to  **INFO**.

```
Huawei LiteOS # log level 4
Set current log level INFO
```

