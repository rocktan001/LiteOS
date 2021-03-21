# free<a name="EN-US_TOPIC_0312409046"></a>

## Function<a name="en-us_topic_0175230306_section3397848916315"></a>

The **free** command displays the usage of memory in Huawei LiteOS and the sizes of the text segment, data segment, rodata segment, and bss segment.

## Format<a name="en-us_topic_0175230306_section714782516315"></a>

free \[_-k_ |  _-m_\]

## Parameter Description<a name="en-us_topic_0175230306_section2432543416315"></a>

**Table  1**  Parameter description

<a name="en-us_topic_0175230306_table2420316616315"></a>
<table><thead align="left"><tr id="en-us_topic_0175230306_row335408816315"><th class="cellrowborder" valign="top" width="21.099999999999998%" id="mcps1.2.4.1.1"><p id="en-us_topic_0175230306_p324569116315"><a name="en-us_topic_0175230306_p324569116315"></a><a name="en-us_topic_0175230306_p324569116315"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.32%" id="mcps1.2.4.1.2"><p id="en-us_topic_0175230306_p6157439016315"><a name="en-us_topic_0175230306_p6157439016315"></a><a name="en-us_topic_0175230306_p6157439016315"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.58%" id="mcps1.2.4.1.3"><p id="en-us_topic_0175230306_p2146969816315"><a name="en-us_topic_0175230306_p2146969816315"></a><a name="en-us_topic_0175230306_p2146969816315"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230306_row6132397416315"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230306_p118602716315"><a name="en-us_topic_0175230306_p118602716315"></a><a name="en-us_topic_0175230306_p118602716315"></a>No parameters</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230306_p2618439793551"><a name="en-us_topic_0175230306_p2618439793551"></a><a name="en-us_topic_0175230306_p2618439793551"></a>In the unit of byte</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230306_p5350974593540"><a name="en-us_topic_0175230306_p5350974593540"></a><a name="en-us_topic_0175230306_p5350974593540"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230306_row1524302995233"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230306_p2672584595233"><a name="en-us_topic_0175230306_p2672584595233"></a><a name="en-us_topic_0175230306_p2672584595233"></a>-k</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230306_p1730981795233"><a name="en-us_topic_0175230306_p1730981795233"></a><a name="en-us_topic_0175230306_p1730981795233"></a>In the unit of KB</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230306_p5991793095233"><a name="en-us_topic_0175230306_p5991793095233"></a><a name="en-us_topic_0175230306_p5991793095233"></a>N/A</p>
</td>
</tr>
<tr id="en-us_topic_0175230306_row48438219540"><td class="cellrowborder" valign="top" width="21.099999999999998%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0175230306_p568052339540"><a name="en-us_topic_0175230306_p568052339540"></a><a name="en-us_topic_0175230306_p568052339540"></a>-m</p>
</td>
<td class="cellrowborder" valign="top" width="52.32%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0175230306_p378211249540"><a name="en-us_topic_0175230306_p378211249540"></a><a name="en-us_topic_0175230306_p378211249540"></a>In the unit of MB</p>
</td>
<td class="cellrowborder" valign="top" width="26.58%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0175230306_p436122419540"><a name="en-us_topic_0175230306_p436122419540"></a><a name="en-us_topic_0175230306_p436122419540"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0175230306_section2177154516315"></a>

-   Run the  **free**  command to display the memory usage. In the command output,  **total**  indicates the total size of the dynamic memory pool,  **used**  indicates the size of the used memory, and  **free**  indicates the size of the free memory.  **text**  indicates the code segment size,  **data**  indicates the data segment size,  **rodata**  indicates the read-only data segment size, and  **bss**  indicates the memory size occupied by uninitialized global variables.
-   The  **free** command can be used to display the memory usage in three units: byte, KB, and MB.

## Example<a name="en-us_topic_0175230306_section367785216315"></a>

Enter  **free**,  **free -k**, and  **free -m**.

## Output<a name="en-us_topic_0175230306_section6390849316315"></a>

Display the memory usage in three units

```
Huawei LiteOS # free

        total        used          free
Mem:    117631744    31826864      85804880

        text         data          rodata        bss
Mem:    4116480      423656        1204224       6659316

Huawei LiteOS # free -k

        total        used          free
Mem:    114874       31080         83793

        text         data          rodata        bss
Mem:    4020         423           1176         6503

Huawei LiteOS # free -m

        total        used          free
Mem:    112          30            81

        text         data          rodata        bss
Mem:    3            0             1             6
```

