# queue<a name="EN-US_TOPIC_0317501925"></a>

## Function<a name="en-us_topic_0313668615_section676257315176"></a>

The  **queue**  command is used to view the queue usage.

## Format<a name="en-us_topic_0313668615_section3096931815176"></a>

queue

## User Guide<a name="en-us_topic_0313668615_section338301615176"></a>

The macro  **LOSCFG\_DEBUG\_QUEUE**  should be opened before using the command  **queue**.

Debug ---\> Enable a Debug Version---\> Enable Debug LiteOS Kernel Resource---\> Enable Queue Debugging

## Example<a name="en-us_topic_0313668615_section735813159472"></a>

Enter  **queue**

## Output<a name="en-us_topic_0313668615_section20711626163713"></a>

The putput of the **queue** command:
```
Huawei LiteOS # queue
used queues information:
Queue ID <0x0> may leak, queue len is 0x10, readable cnt:0x0, writeable cnt:0x10, TaskEntry of creator:0x0x80007d5, Latest operation time: 0x614271
```

The meanings of the items in the above figure are as follows:
<a name="en-us_topic_0313668615_table1143112346254"></a>
<table><thead align="left"><tr id="en-us_topic_0313668615_row164311534172517"><th class="cellrowborder" valign="top" width="30.75%" id="mcps1.1.3.1.1"><p id="en-us_topic_0313668615_p74311634102516"><a name="en-us_topic_0313668615_p74311634102516"></a><a name="en-us_topic_0313668615_p74311634102516"></a>Output</p>
</th>
<th class="cellrowborder" valign="top" width="69.25%" id="mcps1.1.3.1.2"><p id="en-us_topic_0313668615_p74315345255"><a name="en-us_topic_0313668615_p74315345255"></a><a name="en-us_topic_0313668615_p74315345255"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0313668615_row1943119343252"><td class="cellrowborder" valign="top" width="30.75%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0313668615_p1343173482517"><a name="en-us_topic_0313668615_p1343173482517"></a><a name="en-us_topic_0313668615_p1343173482517"></a>Queue ID</p>
</td>
<td class="cellrowborder" valign="top" width="69.25%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0313668615_p8431113432510"><a name="en-us_topic_0313668615_p8431113432510"></a><a name="en-us_topic_0313668615_p8431113432510"></a>Queue ID</p>
</td>
</tr>
<tr id="en-us_topic_0313668615_row743117346255"><td class="cellrowborder" valign="top" width="30.75%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0313668615_p1943133412253"><a name="en-us_topic_0313668615_p1943133412253"></a><a name="en-us_topic_0313668615_p1943133412253"></a>queue len</p>
</td>
<td class="cellrowborder" valign="top" width="69.25%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0313668615_p1143117348255"><a name="en-us_topic_0313668615_p1143117348255"></a><a name="en-us_topic_0313668615_p1143117348255"></a>Number of queue message nodes</p>
</td>
</tr>
<tr id="en-us_topic_0313668615_row1343115342257"><td class="cellrowborder" valign="top" width="30.75%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0313668615_p17431133413251"><a name="en-us_topic_0313668615_p17431133413251"></a><a name="en-us_topic_0313668615_p17431133413251"></a>readable cnt</p>
</td>
<td class="cellrowborder" valign="top" width="69.25%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0313668615_p1943153415252"><a name="en-us_topic_0313668615_p1943153415252"></a><a name="en-us_topic_0313668615_p1943153415252"></a>Number of messages nodes that can be read in the queue</p>
</td>
</tr>
<tr id="en-us_topic_0313668615_row1143153418252"><td class="cellrowborder" valign="top" width="30.75%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0313668615_p184321634142517"><a name="en-us_topic_0313668615_p184321634142517"></a><a name="en-us_topic_0313668615_p184321634142517"></a>writeable cnt</p>
</td>
<td class="cellrowborder" valign="top" width="69.25%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0313668615_p154323346259"><a name="en-us_topic_0313668615_p154323346259"></a><a name="en-us_topic_0313668615_p154323346259"></a>Number of messages nodes that can be written in the queue</p>
</td>
</tr>
<tr id="en-us_topic_0313668615_row1432834142514"><td class="cellrowborder" valign="top" width="30.75%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0313668615_p12432103415257"><a name="en-us_topic_0313668615_p12432103415257"></a><a name="en-us_topic_0313668615_p12432103415257"></a>TaskEntry of creator</p>
</td>
<td class="cellrowborder" valign="top" width="69.25%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0313668615_p14432153432518"><a name="en-us_topic_0313668615_p14432153432518"></a><a name="en-us_topic_0313668615_p14432153432518"></a>The interface address which created the queue</p>
</td>
</tr>
<tr id="en-us_topic_0313668615_row12432103422513"><td class="cellrowborder" valign="top" width="30.75%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0313668615_p14432134152510"><a name="en-us_topic_0313668615_p14432134152510"></a><a name="en-us_topic_0313668615_p14432134152510"></a>Latest operation time</p>
</td>
<td class="cellrowborder" valign="top" width="69.25%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0313668615_p10432133410255"><a name="en-us_topic_0313668615_p10432133410255"></a><a name="en-us_topic_0313668615_p10432133410255"></a>Last operation time of the queue</p>
</td>
</tr>
</tbody>
</table>

