# trace\_dump<a name="EN-US_TOPIC_0312409065"></a>

## Function<a name="en-us_topic_0278763424_section7773833153212"></a>

This command is used to dump the trace buffer information in offline mode.

## Format<a name="en-us_topic_0278763424_section2077511334327"></a>

trace\_dump \[1 | 0\]

## Parameter Description<a name="en-us_topic_0278763424_section9775433103218"></a>

**Table  1**  Parameter Description

<a name="en-us_topic_0278763424_table10776033163211"></a>
<table><thead align="left"><tr id="en-us_topic_0278763424_row158021233133214"><th class="cellrowborder" valign="top" width="21.21%" id="mcps1.2.4.1.1"><p id="en-us_topic_0278763424_p20802193343210"><a name="en-us_topic_0278763424_p20802193343210"></a><a name="en-us_topic_0278763424_p20802193343210"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.53%" id="mcps1.2.4.1.2"><p id="en-us_topic_0278763424_p18802143316321"><a name="en-us_topic_0278763424_p18802143316321"></a><a name="en-us_topic_0278763424_p18802143316321"></a>Parameter Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.26%" id="mcps1.2.4.1.3"><p id="en-us_topic_0278763424_p08021933163212"><a name="en-us_topic_0278763424_p08021933163212"></a><a name="en-us_topic_0278763424_p08021933163212"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0278763424_row10802833103220"><td class="cellrowborder" valign="top" width="21.21%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0278763424_p780213331320"><a name="en-us_topic_0278763424_p780213331320"></a><a name="en-us_topic_0278763424_p780213331320"></a>1</p>
</td>
<td class="cellrowborder" valign="top" width="52.53%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0278763424_p1802103363218"><a name="en-us_topic_0278763424_p1802103363218"></a><a name="en-us_topic_0278763424_p1802103363218"></a><span id="en-us_topic_0278763424_ph1557725119287"><a name="en-us_topic_0278763424_ph1557725119287"></a><a name="en-us_topic_0278763424_ph1557725119287"></a>Export trace data to the client.</span></p>
</td>
<td class="cellrowborder" valign="top" width="26.26%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0278763424_p10802133193216"><a name="en-us_topic_0278763424_p10802133193216"></a><a name="en-us_topic_0278763424_p10802133193216"></a>NA</p>
</td>
</tr>
<tr id="en-us_topic_0278763424_row8575573349"><td class="cellrowborder" valign="top" width="21.21%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0278763424_p35759717344"><a name="en-us_topic_0278763424_p35759717344"></a><a name="en-us_topic_0278763424_p35759717344"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="52.53%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0278763424_p95757710347"><a name="en-us_topic_0278763424_p95757710347"></a><a name="en-us_topic_0278763424_p95757710347"></a><span id="en-us_topic_0278763424_ph69299589304"><a name="en-us_topic_0278763424_ph69299589304"></a><a name="en-us_topic_0278763424_ph69299589304"></a>Format and print trace data.</span></p>
</td>
<td class="cellrowborder" valign="top" width="26.26%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0278763424_p12575127113419"><a name="en-us_topic_0278763424_p12575127113419"></a><a name="en-us_topic_0278763424_p12575127113419"></a>NA</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0278763424_section1278343333217"></a>

-   The  **trace\_dump** command can be used only in offline mode.
-   By default, the displayed trace data is formatted.
-   The  **trace\_dump**  command displays the data between  **trace\_start** and  **trace\_stop**. Therefore, you need to run the  **trace\_stop** command to stop the trace, and then run the  **trace\_dump** command to display the information about the trace buffer.

## Example<a name="en-us_topic_0278763424_section1783163315326"></a>

Enter  **trace\_dump**.

## Output<a name="en-us_topic_0278763424_section11783733183215"></a>

Run the  **trace\_dump** command to format and display the buffer data.

```
Huawei LiteOS # trace_dump
*******TraceInfo begin*******
clockFreq = 180000000
CurEvtIndex = 19
Index   Time(cycles)      EventType      CurTask   Identity      params    
0       0x7da8da5180      0x45           0x5       0x2           0x9          0x20         0x1f
1       0x7dde8c6980      0x45           0x2       0x5           0x1f         0x4          0x9
2       0x7e1431df20      0x45           0x5       0x2           0x9          0x20         0x1f
3       0x7e49e3f720      0x45           0x2       0x5           0x1f         0x4          0x9
4       0x7e7f896cc0      0x45           0x5       0x2           0x9          0x20         0x1f
5       0x7eb53b84c0      0x45           0x2       0x5           0x1f         0x4          0x9
6       0x7eeae0fa60      0x45           0x5       0x2           0x9          0x20         0x1f
7       0x7f20931260      0x45           0x2       0x5           0x1f         0x4          0x9
8       0x7f56388800      0x45           0x5       0x2           0x9          0x20         0x1f
9       0x7f8beaa000      0x45           0x2       0x5           0x1f         0x4          0x9
10      0x7fc19015a0      0x45           0x5       0x2           0x9          0x20         0x1f
11      0x7ff7422da0      0x45           0x2       0x5           0x1f         0x4          0x9
12      0x802ce7a340      0x45           0x5       0x2           0x9          0x20         0x1f
13      0x806299bb40      0x45           0x2       0x5           0x1f         0x4          0x9
14      0x80983f30e0      0x45           0x5       0x2           0x9          0x20         0x1f
15      0x80cdf148e0      0x45           0x2       0x5           0x1f         0x4          0x9
……
24      0x6c560a8d00      0x24           0x2       0x2d          0x0          0x0          0x0
25      0x6c8baf7600      0x25           0x2       0x2d          0x0          0x0          0x0
……
36      0x71fe6f2000      0x24           0x2       0x2d          0x0          0x0          0x0
37      0x7234140900      0x25           0x2       0x2d          0x0          0x0          0x0
38      0x7269c20250      0x45           0x2       0x1           0x1f         0x4          0x0
39      0x734055a650      0x45           0x1       0x2           0x0          0x8          0x1f
40      0x7380b52450      0x45           0x2       0x1           0x1f         0x4          0x0
……
48      0x77a6d3b300      0x24           0x2       0x2d          0x0          0x0          0x0 
49      0x77dc789c00      0x25           0x2       0x2d          0x0          0x0          0x0
50      0x7812269550      0x45           0x2       0x1           0x1f         0x4          0x0
……
*******TraceInfo end*******
```

