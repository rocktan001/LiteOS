# date<a name="EN-US_TOPIC_0312409023"></a>

## Function<a name="en-us_topic_0175230538_section676257315176"></a>

The  **date** command is used to query and set the system time.

## Format<a name="en-us_topic_0175230538_section3096931815176"></a>

date

date  --help

date  +Format

date  -s  YY/MM/DD

date  -s  hh:mm:ss

date -r Filename \(The open-source version does not support this command.\)

## Parameter Description<a name="en-us_topic_0175230538_section2805486115176"></a>

**Table  1**  Parameter Description

<a name="en-us_topic_0175230538_table5785124015176"></a>
<table><thead align="left"><tr id="en-us_topic_0175230538_row3935748315176"><th class="cellrowborder" valign="top" width="21.099999999999998%" id="mcps1.2.4.1.1"><p id="en-us_topic_0175230538_p3383958815176"><a name="en-us_topic_0175230538_p3383958815176"></a><a name="en-us_topic_0175230538_p3383958815176"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="49.69%" id="mcps1.2.4.1.2"><p id="en-us_topic_0175230538_p5665211315176"><a name="en-us_topic_0175230538_p5665211315176"></a><a name="en-us_topic_0175230538_p5665211315176"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="29.21%" id="mcps1.2.4.1.3"><p id="en-us_topic_0175230538_p2541845915176"><a name="en-us_topic_0175230538_p2541845915176"></a><a name="en-us_topic_0175230538_p2541845915176"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230538_row4562928915176"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230538_p26790210135033"><a name="en-us_topic_0175230538_p26790210135033"></a><a name="en-us_topic_0175230538_p26790210135033"></a>--help</p>
</td>
<td class="cellrowborder" valign="top" width="49.69%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230538_p59863311135138"><a name="en-us_topic_0175230538_p59863311135138"></a><a name="en-us_topic_0175230538_p59863311135138"></a>Get help info.</p>
</td>
<td class="cellrowborder" valign="top" width="29.21%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230538_p2930806135233"><a name="en-us_topic_0175230538_p2930806135233"></a><a name="en-us_topic_0175230538_p2930806135233"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230538_row62510682135012"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230538_p4092812213513"><a name="en-us_topic_0175230538_p4092812213513"></a><a name="en-us_topic_0175230538_p4092812213513"></a>+Format</p>
</td>
<td class="cellrowborder" valign="top" width="49.69%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230538_p62477151135146"><a name="en-us_topic_0175230538_p62477151135146"></a><a name="en-us_topic_0175230538_p62477151135146"></a>Print the current time in the configured format.</p>
</td>
<td class="cellrowborder" valign="top" width="29.21%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230538_p50435944135242"><a name="en-us_topic_0175230538_p50435944135242"></a><a name="en-us_topic_0175230538_p50435944135242"></a>Placeholders listed using <strong id="en-us_topic_0175230538_b1288219138113"><a name="en-us_topic_0175230538_b1288219138113"></a><a name="en-us_topic_0175230538_b1288219138113"></a>--help</strong></p>
</td>
</tr>
<tr id="en-us_topic_0175230538_row5365911213508"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230538_p60074205135110"><a name="en-us_topic_0175230538_p60074205135110"></a><a name="en-us_topic_0175230538_p60074205135110"></a>-s YY/MM/DD</p>
</td>
<td class="cellrowborder" valign="top" width="49.69%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230538_p32125931135151"><a name="en-us_topic_0175230538_p32125931135151"></a><a name="en-us_topic_0175230538_p32125931135151"></a>Set the system time. The value is in YY/MM/DD format. The year, month, and date are separated by slashes (/). </p>
</td>
<td class="cellrowborder" valign="top" width="29.21%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230538_p25441007135232"><a name="en-us_topic_0175230538_p25441007135232"></a><a name="en-us_topic_0175230538_p25441007135232"></a>≥ 1970/01/01</p>
</td>
</tr>
<tr id="en-us_topic_0175230538_row3084225516144"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230538_p1519475816144"><a name="en-us_topic_0175230538_p1519475816144"></a><a name="en-us_topic_0175230538_p1519475816144"></a>-s  hh:mm:ss</p>
</td>
<td class="cellrowborder" valign="top" width="49.69%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230538_p973195117445"><a name="en-us_topic_0175230538_p973195117445"></a><a name="en-us_topic_0175230538_p973195117445"></a>Set the system time. The value is in hh:mm:ss format. The hour, minute, and second are separated by colons (:).</p>
</td>
<td class="cellrowborder" valign="top" width="29.21%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230538_p24727246446"><a name="en-us_topic_0175230538_p24727246446"></a><a name="en-us_topic_0175230538_p24727246446"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230538_row34574578134959"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230538_p36895963135128"><a name="en-us_topic_0175230538_p36895963135128"></a><a name="en-us_topic_0175230538_p36895963135128"></a>-r Filename</p>
</td>
<td class="cellrowborder" valign="top" width="49.69%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230538_p51178271135217"><a name="en-us_topic_0175230538_p51178271135217"></a><a name="en-us_topic_0175230538_p51178271135217"></a>Query the last modification time of a specified file. LOSCFG_FS_VFS needs to be enabled.</p>
</td>
<td class="cellrowborder" valign="top" width="29.21%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230538_p40075877135229"><a name="en-us_topic_0175230538_p40075877135229"></a><a name="en-us_topic_0175230538_p40075877135229"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0175230538_section338301615176"></a>

-   If date is not specified, the current system time is displayed by default.
-   The  **--help**,  **+Format**,  **-s**, and  **-r**  commands cannot be used together.

## Example<a name="en-us_topic_0175230538_section4315602815176"></a>

Enter  **date +%Y--%m--%d**.

## Output<a name="en-us_topic_0175230538_section1440763015176"></a>

Run the  **date +%Y--%m--%d**  command to display the current system time in the specified format.

```
Huawei LiteOS # date +%Y--%m--%d
2021--01--20
```

