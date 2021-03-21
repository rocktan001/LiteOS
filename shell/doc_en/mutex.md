# mutex<a name="EN-US_TOPIC_0312409052"></a>

## Function<a name="en-us_topic_0175230521_section676257315176"></a>

The  **mutex**  command is used to view the mutex usage.

## Format<a name="en-us_topic_0175230521_section3096931815176"></a>

mutex

## User Guide<a name="en-us_topic_0175230521_section338301615176"></a>

This command depends on  **LOSCFG\_DEBUG\_MUTEX**. You can enable the marco by running  **make menuconfig**  to enable  **Enable Mutex Debugging**.

```
Debug  ---> Enable a Debug Version ---> Enable Debug LiteOS Kernel Resource ---> Enable Mutex Debugging
```

## Example<a name="en-us_topic_0175230521_section4315602815176"></a>

Enter  **mutex**.

## Output<a name="en-us_topic_0175230521_section1440763015176"></a>

Run the  **mutex**  command to display the mutex usage.

```
Huawei LiteOS # mutex
used mutexs information: 
Mutex ID <0x0> may leak, Owner is null, TaskEntry of creator: 0x8000711,Latest operation time: 0x0
```

The main output items are described as follows:

<a name="en-us_topic_0175230521_table19425104971413"></a>
<table><thead align="left"><tr id="en-us_topic_0175230521_row1642516498147"><th class="cellrowborder" valign="top" width="32.18%" id="mcps1.1.3.1.1"><p id="en-us_topic_0175230521_p1942554916149"><a name="en-us_topic_0175230521_p1942554916149"></a><a name="en-us_topic_0175230521_p1942554916149"></a>Output Item</p>
</th>
<th class="cellrowborder" valign="top" width="67.82000000000001%" id="mcps1.1.3.1.2"><p id="en-us_topic_0175230521_p7425164971412"><a name="en-us_topic_0175230521_p7425164971412"></a><a name="en-us_topic_0175230521_p7425164971412"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230521_row1342544911142"><td class="cellrowborder" valign="top" width="32.18%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230521_p1842514918146"><a name="en-us_topic_0175230521_p1842514918146"></a><a name="en-us_topic_0175230521_p1842514918146"></a>Mutex ID</p>
</td>
<td class="cellrowborder" valign="top" width="67.82000000000001%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230521_p194251949131420"><a name="en-us_topic_0175230521_p194251949131420"></a><a name="en-us_topic_0175230521_p194251949131420"></a>Mutex ID</p>
</td>
</tr>
<tr id="en-us_topic_0175230521_row11425749151413"><td class="cellrowborder" valign="top" width="32.18%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230521_p542514919149"><a name="en-us_topic_0175230521_p542514919149"></a><a name="en-us_topic_0175230521_p542514919149"></a>TaskEntry of creator</p>
</td>
<td class="cellrowborder" valign="top" width="67.82000000000001%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230521_p54252497145"><a name="en-us_topic_0175230521_p54252497145"></a><a name="en-us_topic_0175230521_p54252497145"></a>Interface IP address for creating a mutex</p>
</td>
</tr>
<tr id="en-us_topic_0175230521_row1242544961414"><td class="cellrowborder" valign="top" width="32.18%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230521_p1342584916141"><a name="en-us_topic_0175230521_p1342584916141"></a><a name="en-us_topic_0175230521_p1342584916141"></a>Latest operation time</p>
</td>
<td class="cellrowborder" valign="top" width="67.82000000000001%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230521_p8425349171413"><a name="en-us_topic_0175230521_p8425349171413"></a><a name="en-us_topic_0175230521_p8425349171413"></a>Last scheduling time of a task</p>
</td>
</tr>
</tbody>
</table>

