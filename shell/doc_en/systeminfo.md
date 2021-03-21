# systeminfo<a name="EN-US_TOPIC_0312409055"></a>

## Function<a name="en-us_topic_0175230520_section31007017114432"></a>

The  **systeminfo** command is used to view the usage of resources including tasks, semaphores, mutexes, queues, and timers in Huawei LiteOS.

If the semaphore, mutex, queue, and software timer are tailored in the system image, the system does not use these resources. In this case, this command does not display the information about these resources.

## Format<a name="en-us_topic_0175230520_section55537546114432"></a>

systeminfo

## Example<a name="en-us_topic_0175230520_section63149349114432"></a>

Enter  **systeminfo**.

## Output<a name="en-us_topic_0175230520_section66303639114432"></a>

Run the  **systeminfo**  command to check the system resource usage. The following information is displayed:

```
Huawei LiteOS # systeminfo

   Module    Used      Total
--------------------------------
   Task      5         16
   Sem       0         20
   Mutex     1         20
   Queue     1         10
   SwTmr     1         16
```

The output items are described as follows:

<a name="en-us_topic_0175230520_table66720985141632"></a>
<table><thead align="left"><tr id="en-us_topic_0175230520_row47392211141632"><th class="cellrowborder" valign="top" width="25.790000000000003%" id="mcps1.1.3.1.1"><p id="en-us_topic_0175230520_p13563887141632"><a name="en-us_topic_0175230520_p13563887141632"></a><a name="en-us_topic_0175230520_p13563887141632"></a>Output Item</p>
</th>
<th class="cellrowborder" valign="top" width="74.21%" id="mcps1.1.3.1.2"><p id="en-us_topic_0175230520_p24933059141632"><a name="en-us_topic_0175230520_p24933059141632"></a><a name="en-us_topic_0175230520_p24933059141632"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230520_row6311928141632"><td class="cellrowborder" valign="top" width="25.790000000000003%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230520_p41504182141632"><a name="en-us_topic_0175230520_p41504182141632"></a><a name="en-us_topic_0175230520_p41504182141632"></a>Module</p>
</td>
<td class="cellrowborder" valign="top" width="74.21%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230520_p6395556141632"><a name="en-us_topic_0175230520_p6395556141632"></a><a name="en-us_topic_0175230520_p6395556141632"></a>Module name</p>
</td>
</tr>
<tr id="en-us_topic_0175230520_row57560004141632"><td class="cellrowborder" valign="top" width="25.790000000000003%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230520_p31848766141632"><a name="en-us_topic_0175230520_p31848766141632"></a><a name="en-us_topic_0175230520_p31848766141632"></a>Used</p>
</td>
<td class="cellrowborder" valign="top" width="74.21%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230520_p29613244141632"><a name="en-us_topic_0175230520_p29613244141632"></a><a name="en-us_topic_0175230520_p29613244141632"></a>Number of used resources</p>
</td>
</tr>
<tr id="en-us_topic_0175230520_row65192608141632"><td class="cellrowborder" valign="top" width="25.790000000000003%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230520_p46109920141632"><a name="en-us_topic_0175230520_p46109920141632"></a><a name="en-us_topic_0175230520_p46109920141632"></a>Total</p>
</td>
<td class="cellrowborder" valign="top" width="74.21%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230520_p43916057141632"><a name="en-us_topic_0175230520_p43916057141632"></a><a name="en-us_topic_0175230520_p43916057141632"></a>Maximum number of usable resources</p>
</td>
</tr>
</tbody>
</table>

