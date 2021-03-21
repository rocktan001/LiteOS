# watch<a name="EN-US_TOPIC_0312409060"></a>

## Function<a name="en-us_topic_0175230192_section81771101235"></a>

The  **watch** command is used to periodically monitor the command output.

## Format<a name="en-us_topic_0175230192_section3096931815176"></a>

watch \[_-c | -n | -t | --count | --interval | -no-title_\] <command\>

watch --over

## Parameter Description<a name="en-us_topic_0175230192_section2805486115176"></a>

**Table  1**  Parameter description

<a name="en-us_topic_0175230192_table5785124015176"></a>
<table><thead align="left"><tr id="en-us_topic_0175230192_row3935748315176"><th class="cellrowborder" valign="top" width="17.53%" id="mcps1.2.5.1.1"><p id="en-us_topic_0175230192_p3383958815176"><a name="en-us_topic_0175230192_p3383958815176"></a><a name="en-us_topic_0175230192_p3383958815176"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="40.400000000000006%" id="mcps1.2.5.1.2"><p id="en-us_topic_0175230192_p5665211315176"><a name="en-us_topic_0175230192_p5665211315176"></a><a name="en-us_topic_0175230192_p5665211315176"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="20.87%" id="mcps1.2.5.1.3"><p id="en-us_topic_0175230192_p2541845915176"><a name="en-us_topic_0175230192_p2541845915176"></a><a name="en-us_topic_0175230192_p2541845915176"></a>Default Value</p>
</th>
<th class="cellrowborder" valign="top" width="21.2%" id="mcps1.2.5.1.4"><p id="en-us_topic_0175230192_p203381426300"><a name="en-us_topic_0175230192_p203381426300"></a><a name="en-us_topic_0175230192_p203381426300"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230192_row4562928915176"><td class="cellrowborder" valign="top" width="17.53%" headers="mcps1.2.5.1.1 "><p id="en-us_topic_0175230192_p1372611313571"><a name="en-us_topic_0175230192_p1372611313571"></a><a name="en-us_topic_0175230192_p1372611313571"></a>-c | --count</p>
</td>
<td class="cellrowborder" valign="top" width="40.400000000000006%" headers="mcps1.2.5.1.2 "><p id="en-us_topic_0175230192_p54798368135752"><a name="en-us_topic_0175230192_p54798368135752"></a><a name="en-us_topic_0175230192_p54798368135752"></a>Total number of command executions.</p>
</td>
<td class="cellrowborder" valign="top" width="20.87%" headers="mcps1.2.5.1.3 "><p id="en-us_topic_0175230192_p37568760135854"><a name="en-us_topic_0175230192_p37568760135854"></a><a name="en-us_topic_0175230192_p37568760135854"></a>0xFFFFFF</p>
</td>
<td class="cellrowborder" valign="top" width="21.2%" headers="mcps1.2.5.1.4 "><p id="en-us_topic_0175230192_p912819366300"><a name="en-us_topic_0175230192_p912819366300"></a><a name="en-us_topic_0175230192_p912819366300"></a>(0,0xFFFFFF]</p>
</td>
</tr>
<tr id="en-us_topic_0175230192_row66475217135624"><td class="cellrowborder" valign="top" width="17.53%" headers="mcps1.2.5.1.1 "><p id="en-us_topic_0175230192_p5732809813576"><a name="en-us_topic_0175230192_p5732809813576"></a><a name="en-us_topic_0175230192_p5732809813576"></a>-n | --interval</p>
</td>
<td class="cellrowborder" valign="top" width="40.400000000000006%" headers="mcps1.2.5.1.2 "><p id="en-us_topic_0175230192_p9520387135757"><a name="en-us_topic_0175230192_p9520387135757"></a><a name="en-us_topic_0175230192_p9520387135757"></a>Time interval of executing commands, in seconds.</p>
</td>
<td class="cellrowborder" valign="top" width="20.87%" headers="mcps1.2.5.1.3 "><p id="en-us_topic_0175230192_p24983852135855"><a name="en-us_topic_0175230192_p24983852135855"></a><a name="en-us_topic_0175230192_p24983852135855"></a>1s</p>
</td>
<td class="cellrowborder" valign="top" width="21.2%" headers="mcps1.2.5.1.4 "><p id="en-us_topic_0175230192_p712813663012"><a name="en-us_topic_0175230192_p712813663012"></a><a name="en-us_topic_0175230192_p712813663012"></a>(0,0xFFFFFF]</p>
</td>
</tr>
<tr id="en-us_topic_0175230192_row36164603135634"><td class="cellrowborder" valign="top" width="17.53%" headers="mcps1.2.5.1.1 "><p id="en-us_topic_0175230192_p4536317135711"><a name="en-us_topic_0175230192_p4536317135711"></a><a name="en-us_topic_0175230192_p4536317135711"></a>-t | -no-title</p>
</td>
<td class="cellrowborder" valign="top" width="40.400000000000006%" headers="mcps1.2.5.1.2 "><p id="en-us_topic_0175230192_p1648427813582"><a name="en-us_topic_0175230192_p1648427813582"></a><a name="en-us_topic_0175230192_p1648427813582"></a>Close the time display on the top.</p>
</td>
<td class="cellrowborder" valign="top" width="20.87%" headers="mcps1.2.5.1.3 "><p id="en-us_topic_0175230192_p44556568135855"><a name="en-us_topic_0175230192_p44556568135855"></a><a name="en-us_topic_0175230192_p44556568135855"></a>N/A</p>
</td>
<td class="cellrowborder" valign="top" width="21.2%" headers="mcps1.2.5.1.4 "><p id="en-us_topic_0175230192_p1612803653010"><a name="en-us_topic_0175230192_p1612803653010"></a><a name="en-us_topic_0175230192_p1612803653010"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230192_row618245316529"><td class="cellrowborder" valign="top" width="17.53%" headers="mcps1.2.5.1.1 "><p id="en-us_topic_0175230192_p37180986135715"><a name="en-us_topic_0175230192_p37180986135715"></a><a name="en-us_topic_0175230192_p37180986135715"></a>command</p>
</td>
<td class="cellrowborder" valign="top" width="40.400000000000006%" headers="mcps1.2.5.1.2 "><p id="en-us_topic_0175230192_p684484513587"><a name="en-us_topic_0175230192_p684484513587"></a><a name="en-us_topic_0175230192_p684484513587"></a>Shell commands to be listened on.</p>
</td>
<td class="cellrowborder" valign="top" width="20.87%" headers="mcps1.2.5.1.3 "><p id="en-us_topic_0175230192_p48457616135856"><a name="en-us_topic_0175230192_p48457616135856"></a><a name="en-us_topic_0175230192_p48457616135856"></a>N/A</p>
</td>
<td class="cellrowborder" valign="top" width="21.2%" headers="mcps1.2.5.1.4 "><p id="en-us_topic_0175230192_p61281736133017"><a name="en-us_topic_0175230192_p61281736133017"></a><a name="en-us_topic_0175230192_p61281736133017"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230192_row94889542563"><td class="cellrowborder" valign="top" width="17.53%" headers="mcps1.2.5.1.1 "><p id="en-us_topic_0175230192_p53382769174642"><a name="en-us_topic_0175230192_p53382769174642"></a><a name="en-us_topic_0175230192_p53382769174642"></a>--over</p>
</td>
<td class="cellrowborder" valign="top" width="40.400000000000006%" headers="mcps1.2.5.1.2 "><p id="en-us_topic_0175230192_p29037021174642"><a name="en-us_topic_0175230192_p29037021174642"></a><a name="en-us_topic_0175230192_p29037021174642"></a>Disable the current monitor.</p>
</td>
<td class="cellrowborder" valign="top" width="20.87%" headers="mcps1.2.5.1.3 "><p id="en-us_topic_0175230192_p3188461174642"><a name="en-us_topic_0175230192_p3188461174642"></a><a name="en-us_topic_0175230192_p3188461174642"></a>N/A</p>
</td>
<td class="cellrowborder" valign="top" width="21.2%" headers="mcps1.2.5.1.4 "><p id="en-us_topic_0175230192_p56938761174642"><a name="en-us_topic_0175230192_p56938761174642"></a><a name="en-us_topic_0175230192_p56938761174642"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0175230192_section11917418145516"></a>

-   The parameter  **command**  must be a shell command. For a non-shell command, the error message "command is not fount" will be displayed.
-   The parameter  **command**  is mandatory if you want to listen on command.
-   The parameter **--over** cannot be used together with other parameters.

## Examples<a name="en-us_topic_0175230192_section4315602815176"></a>

Example 1: Enter  **watch -c 5 task 1**.

Example 2: If the  **watch**  command is not required for listening, run the  **watch --over**  command.

## Output<a name="en-us_topic_0175230192_section3262608195524"></a>

The  **task 1**  command is executed for five times at an interval of 1 second. The following information is displayed after the  **watch**  command is executed:

```
Huawei LiteOS # watch -c 3 task 1

Huawei LiteOS # Thu Jan  1 16:26:26 1970

TaskName = Swt_Task
TaskId = 0x1
*******backtrace begin*******
traceback 1 -- lr = 0x08004006 -- fp = 0x0800045e
traceback 2 -- lr = 0x08004000 -- fp = 0x0800194c
traceback 3 -- lr = 0x080040da -- fp = 0x08003e50
traceback 4 -- lr = 0x080015c2 -- fp = 0x080040a8
traceback 5 -- lr = 0x0800396e -- fp = 0x08001598

Thu Jan  1 16:26:27 1970

TaskName = Swt_Task
TaskId = 0x1
*******backtrace begin*******
traceback 1 -- lr = 0x08004006 -- fp = 0x0800045e
traceback 2 -- lr = 0x08004000 -- fp = 0x0800194c
traceback 3 -- lr = 0x080040da -- fp = 0x08003e50
traceback 4 -- lr = 0x080015c2 -- fp = 0x080040a8
traceback 5 -- lr = 0x0800396e -- fp = 0x08001598

Thu Jan  1 16:26:28 1970

TaskName = Swt_Task
TaskId = 0x1
*******backtrace begin*******
traceback 1 -- lr = 0x08004006 -- fp = 0x0800045e
traceback 2 -- lr = 0x08004000 -- fp = 0x0800194c
traceback 3 -- lr = 0x080040da -- fp = 0x08003e50
traceback 4 -- lr = 0x080015c2 -- fp = 0x080040a8
traceback 5 -- lr = 0x0800396e -- fp = 0x08001598
```

