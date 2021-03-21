# swtmr<a name="EN-US_TOPIC_0312409054"></a>

## Function<a name="en-us_topic_0175230501_section676257315176"></a>

The  **swtmr** command is used to query the information about system software timers.

## Format<a name="en-us_topic_0175230501_section3096931815176"></a>

swtmr \[_ID_\]

## Parameter Description<a name="en-us_topic_0175230501_section2805486115176"></a>

**Table  1**  Parameter description

<a name="en-us_topic_0175230501_table5785124015176"></a>
<table><thead align="left"><tr id="en-us_topic_0175230501_row3935748315176"><th class="cellrowborder" valign="top" width="21.099999999999998%" id="mcps1.2.4.1.1"><p id="en-us_topic_0175230501_p3383958815176"><a name="en-us_topic_0175230501_p3383958815176"></a><a name="en-us_topic_0175230501_p3383958815176"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.32%" id="mcps1.2.4.1.2"><p id="en-us_topic_0175230501_p5665211315176"><a name="en-us_topic_0175230501_p5665211315176"></a><a name="en-us_topic_0175230501_p5665211315176"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.58%" id="mcps1.2.4.1.3"><p id="en-us_topic_0175230501_p2541845915176"><a name="en-us_topic_0175230501_p2541845915176"></a><a name="en-us_topic_0175230501_p2541845915176"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230501_row4562928915176"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230501_p498493215176"><a name="en-us_topic_0175230501_p498493215176"></a><a name="en-us_topic_0175230501_p498493215176"></a>ID</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230501_p112632315176"><a name="en-us_topic_0175230501_p112632315176"></a><a name="en-us_topic_0175230501_p112632315176"></a>ID of a software timer. The value can be expressed in decimal or hexadecimal format.</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230501_p1578335115176"><a name="en-us_topic_0175230501_p1578335115176"></a><a name="en-us_topic_0175230501_p1578335115176"></a>[0,0xFFFFFFFF]</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0175230501_section338301615176"></a>

-   If the parameter is left unspecified, information about all software timers will be displayed.
-   If an ID is added after the  **swtmr** command, when the  **ID**  value falls in the range \[0,current number of software timers –1\], the status of the software timer specified by the ID is returned. A prompt indicating a parameter error will be displayed if the parameter value is outside the range.

## Example<a name="en-us_topic_0175230501_section4315602815176"></a>

Enter  **swtmr** and  **swtmr 1**.

## Output<a name="en-us_topic_0175230501_section1440763015176"></a>

Run the  **swtmr**  command to query information about the software timer. The command output is as follows:

```
Huawei LiteOS # swtmr

SwTmrID     State    Mode    Interval  Arg         handlerAddr
----------  -------  ------- --------- ----------  --------
0x00000000  Ticking  Period   1000     0x00000000  0x800442d
```

Run the  **swtmr 0**  command to query information about the software timer whose ID is  **0**. The command output is as follows:

```
Huawei LiteOS # swtmr 0

SwTmrID     State    Mode    Interval  Arg         handlerAddr
----------  -------  ------- --------- ----------  --------
0x00000000  Ticking  Period   1000     0x00000000  0x800442d
```

**Table  2**  Output

<a name="en-us_topic_0175230501_table14887020151220"></a>
<table><thead align="left"><tr id="en-us_topic_0175230501_row42043184151220"><th class="cellrowborder" valign="top" width="28.38%" id="mcps1.2.3.1.1"><p id="en-us_topic_0175230501_p47839586151220"><a name="en-us_topic_0175230501_p47839586151220"></a><a name="en-us_topic_0175230501_p47839586151220"></a>Output Item</p>
</th>
<th class="cellrowborder" valign="top" width="71.61999999999999%" id="mcps1.2.3.1.2"><p id="en-us_topic_0175230501_p49801239151220"><a name="en-us_topic_0175230501_p49801239151220"></a><a name="en-us_topic_0175230501_p49801239151220"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230501_row45557973151220"><td class="cellrowborder" valign="top" width="28.38%" headers="mcps1.2.3.1.1 "><p id="en-us_topic_0175230501_p66317162151220"><a name="en-us_topic_0175230501_p66317162151220"></a><a name="en-us_topic_0175230501_p66317162151220"></a>SwTmrID</p>
</td>
<td class="cellrowborder" valign="top" width="71.61999999999999%" headers="mcps1.2.3.1.2 "><p id="en-us_topic_0175230501_p2981019151220"><a name="en-us_topic_0175230501_p2981019151220"></a><a name="en-us_topic_0175230501_p2981019151220"></a>ID of a software timer</p>
</td>
</tr>
<tr id="en-us_topic_0175230501_row26829178151220"><td class="cellrowborder" valign="top" width="28.38%" headers="mcps1.2.3.1.1 "><p id="en-us_topic_0175230501_p25679842151220"><a name="en-us_topic_0175230501_p25679842151220"></a><a name="en-us_topic_0175230501_p25679842151220"></a>State</p>
</td>
<td class="cellrowborder" valign="top" width="71.61999999999999%" headers="mcps1.2.3.1.2 "><p id="en-us_topic_0175230501_p66801306151220"><a name="en-us_topic_0175230501_p66801306151220"></a><a name="en-us_topic_0175230501_p66801306151220"></a>State of a software timer</p>
</td>
</tr>
<tr id="en-us_topic_0175230501_row64340843151220"><td class="cellrowborder" valign="top" width="28.38%" headers="mcps1.2.3.1.1 "><p id="en-us_topic_0175230501_p44225823151220"><a name="en-us_topic_0175230501_p44225823151220"></a><a name="en-us_topic_0175230501_p44225823151220"></a>Mode</p>
</td>
<td class="cellrowborder" valign="top" width="71.61999999999999%" headers="mcps1.2.3.1.2 "><p id="en-us_topic_0175230501_p25521911151220"><a name="en-us_topic_0175230501_p25521911151220"></a><a name="en-us_topic_0175230501_p25521911151220"></a>Mode of a software timer</p>
</td>
</tr>
<tr id="en-us_topic_0175230501_row28370612151220"><td class="cellrowborder" valign="top" width="28.38%" headers="mcps1.2.3.1.1 "><p id="en-us_topic_0175230501_p16318270151220"><a name="en-us_topic_0175230501_p16318270151220"></a><a name="en-us_topic_0175230501_p16318270151220"></a>Interval</p>
</td>
<td class="cellrowborder" valign="top" width="71.61999999999999%" headers="mcps1.2.3.1.2 "><p id="en-us_topic_0175230501_p46711521151220"><a name="en-us_topic_0175230501_p46711521151220"></a><a name="en-us_topic_0175230501_p46711521151220"></a>Number of ticks used by a software timer</p>
</td>
</tr>
<tr id="en-us_topic_0175230501_row47480058152310"><td class="cellrowborder" valign="top" width="28.38%" headers="mcps1.2.3.1.1 "><p id="en-us_topic_0175230501_p20679490152310"><a name="en-us_topic_0175230501_p20679490152310"></a><a name="en-us_topic_0175230501_p20679490152310"></a>Arg</p>
</td>
<td class="cellrowborder" valign="top" width="71.61999999999999%" headers="mcps1.2.3.1.2 "><p id="en-us_topic_0175230501_p64426007152310"><a name="en-us_topic_0175230501_p64426007152310"></a><a name="en-us_topic_0175230501_p64426007152310"></a>Number of input parameters</p>
</td>
</tr>
<tr id="en-us_topic_0175230501_row8527264152328"><td class="cellrowborder" valign="top" width="28.38%" headers="mcps1.2.3.1.1 "><p id="en-us_topic_0175230501_p19619792152328"><a name="en-us_topic_0175230501_p19619792152328"></a><a name="en-us_topic_0175230501_p19619792152328"></a>handlerAddr</p>
</td>
<td class="cellrowborder" valign="top" width="71.61999999999999%" headers="mcps1.2.3.1.2 "><p id="en-us_topic_0175230501_p45699300152328"><a name="en-us_topic_0175230501_p45699300152328"></a><a name="en-us_topic_0175230501_p45699300152328"></a>Address of a callback function</p>
</td>
</tr>
</tbody>
</table>

