# dmesg<a name="EN-US_TOPIC_0312409057"></a>

## Function<a name="en-us_topic_0175230297_section676257315176"></a>

The  **dmesg** command is used to control the dmesg buffer in core.

## Format<a name="en-us_topic_0175230297_section3096931815176"></a>

dmesg

dmesg \[_-c | -C | -D | -E | -L | -U_\]

dmesg -s <size\>

dmesg -l <level\>

dmesg \> file \(The open-source version does not support this command.\)

## Parameter Description<a name="en-us_topic_0175230297_section2805486115176"></a>

**Table  1**  Parameter Description

<a name="en-us_topic_0175230297_table5785124015176"></a>
<table><thead align="left"><tr id="en-us_topic_0175230297_row3935748315176"><th class="cellrowborder" valign="top" width="21.099999999999998%" id="mcps1.2.4.1.1"><p id="en-us_topic_0175230297_p3383958815176"><a name="en-us_topic_0175230297_p3383958815176"></a><a name="en-us_topic_0175230297_p3383958815176"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.32%" id="mcps1.2.4.1.2"><p id="en-us_topic_0175230297_p5665211315176"><a name="en-us_topic_0175230297_p5665211315176"></a><a name="en-us_topic_0175230297_p5665211315176"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.58%" id="mcps1.2.4.1.3"><p id="en-us_topic_0175230297_p2541845915176"><a name="en-us_topic_0175230297_p2541845915176"></a><a name="en-us_topic_0175230297_p2541845915176"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230297_row4562928915176"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230297_p1372611313571"><a name="en-us_topic_0175230297_p1372611313571"></a><a name="en-us_topic_0175230297_p1372611313571"></a>-c</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230297_p54798368135752"><a name="en-us_topic_0175230297_p54798368135752"></a><a name="en-us_topic_0175230297_p54798368135752"></a>Print logs in the dmesg buffer, and then clean the dmesg buffer.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230297_p37568760135854"><a name="en-us_topic_0175230297_p37568760135854"></a><a name="en-us_topic_0175230297_p37568760135854"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230297_row66475217135624"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230297_p5732809813576"><a name="en-us_topic_0175230297_p5732809813576"></a><a name="en-us_topic_0175230297_p5732809813576"></a>-C</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230297_p9520387135757"><a name="en-us_topic_0175230297_p9520387135757"></a><a name="en-us_topic_0175230297_p9520387135757"></a>Clean the dmesg buffer.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230297_p24983852135855"><a name="en-us_topic_0175230297_p24983852135855"></a><a name="en-us_topic_0175230297_p24983852135855"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230297_row36164603135634"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230297_p4536317135711"><a name="en-us_topic_0175230297_p4536317135711"></a><a name="en-us_topic_0175230297_p4536317135711"></a>-D | -E</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230297_p1648427813582"><a name="en-us_topic_0175230297_p1648427813582"></a><a name="en-us_topic_0175230297_p1648427813582"></a>Specifies whether to enable the console printing function. This parameter is not supported in the open-source version.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230297_p44556568135855"><a name="en-us_topic_0175230297_p44556568135855"></a><a name="en-us_topic_0175230297_p44556568135855"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230297_row4216085135652"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230297_p37180986135715"><a name="en-us_topic_0175230297_p37180986135715"></a><a name="en-us_topic_0175230297_p37180986135715"></a>-L | -U</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230297_p684484513587"><a name="en-us_topic_0175230297_p684484513587"></a><a name="en-us_topic_0175230297_p684484513587"></a>Specifies whether to enable the serial port printing function. This parameter is not supported in the open-source version.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230297_p48457616135856"><a name="en-us_topic_0175230297_p48457616135856"></a><a name="en-us_topic_0175230297_p48457616135856"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230297_row64205653135648"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230297_p9261965135720"><a name="en-us_topic_0175230297_p9261965135720"></a><a name="en-us_topic_0175230297_p9261965135720"></a>-s &lt;size&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230297_p865461135812"><a name="en-us_topic_0175230297_p865461135812"></a><a name="en-us_topic_0175230297_p865461135812"></a>Set the size of the dmesg buffer.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230297_p30040610135857"><a name="en-us_topic_0175230297_p30040610135857"></a><a name="en-us_topic_0175230297_p30040610135857"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230297_row30833787135638"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230297_p19379370135731"><a name="en-us_topic_0175230297_p19379370135731"></a><a name="en-us_topic_0175230297_p19379370135731"></a>-l &lt;level&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230297_p32254578135822"><a name="en-us_topic_0175230297_p32254578135822"></a><a name="en-us_topic_0175230297_p32254578135822"></a>Set the dmesg level.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230297_p64022719135858"><a name="en-us_topic_0175230297_p64022719135858"></a><a name="en-us_topic_0175230297_p64022719135858"></a>0 -- 5</p>
</td>
</tr>
<tr id="en-us_topic_0175230297_row32039995135619"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230297_p30224331135741"><a name="en-us_topic_0175230297_p30224331135741"></a><a name="en-us_topic_0175230297_p30224331135741"></a>&gt; file</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230297_p32052248135832"><a name="en-us_topic_0175230297_p32052248135832"></a><a name="en-us_topic_0175230297_p32052248135832"></a>Writes the content in the buffer to a file. The open-source version does not support this parameter.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230297_p5490711413590"><a name="en-us_topic_0175230297_p5490711413590"></a><a name="en-us_topic_0175230297_p5490711413590"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-notice.gif) **NOTICE:** 
>1.  Before writing a file, ensure that the file system has been mounted.
>2.  Disabling the serial port print function affects the use of the shell. You are advised to connect to the telnet and then disable the serial port.

## User Guide<a name="en-us_topic_0175230297_section338301615176"></a>

-   This command depends on  **LOSCFG\_SHELL\_DMESG**. You can run the  **make menuconfig**  command to enable  **Enable Shell dmesg**.

    ```
    Debug  ---> Enable a Debug Version---> Enable Shell---> Enable Shell dmesg
    ```

-   If the parameter is left unspecified, logs in the dmesg buffer will be printed by default.
-   The parameters cannot be used together.

## Example<a name="en-us_topic_0175230297_section4315602815176"></a>

Enter  **dmesg**  first, and then enter  **dmesg -C**  and  **dmesg**.

## Output<a name="en-us_topic_0175230297_section1440763015176"></a>

In the above figure, in the blue box is the input command. After the  **dmesg** command is executed for the first time, the buffer content is displayed. After running the  **dmesg -C**  command to clear the cache, run the  **dmesg**  command again. We can see that the cache is cleared.

```
Huawei LiteOS # dmesg

Huawei LiteOS # log level 4
Set current log level INFO
Huawei LiteOS # dmesg

Huawei LiteOS # dmesg -C
Huawei LiteOS # dmesg

Huawei LiteOS # dmesg
```

