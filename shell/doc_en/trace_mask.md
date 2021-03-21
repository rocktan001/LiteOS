# trace\_mask<a name="EN-US_TOPIC_0312409064"></a>

## Function<a name="en-us_topic_0278763423_section10402133119271"></a>

The **trace\_mask** command is used to set the event filtering mask.

## Format<a name="en-us_topic_0278763423_section1540317311276"></a>

trace\_mask \[_MASK_\]

## Parameter Description<a name="en-us_topic_0278763423_section15404163152711"></a>

**Table  1**  Parameter description

<a name="en-us_topic_0278763423_table3405133110275"></a>
<table><thead align="left"><tr id="en-us_topic_0278763423_row15441103117273"><th class="cellrowborder" valign="top" width="21.21%" id="mcps1.2.4.1.1"><p id="en-us_topic_0278763423_p11441173111271"><a name="en-us_topic_0278763423_p11441173111271"></a><a name="en-us_topic_0278763423_p11441173111271"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="52.53%" id="mcps1.2.4.1.2"><p id="en-us_topic_0278763423_p1544113192712"><a name="en-us_topic_0278763423_p1544113192712"></a><a name="en-us_topic_0278763423_p1544113192712"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="26.26%" id="mcps1.2.4.1.3"><p id="en-us_topic_0278763423_p044143172712"><a name="en-us_topic_0278763423_p044143172712"></a><a name="en-us_topic_0278763423_p044143172712"></a>Value Range</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0278763423_row14411231172720"><td class="cellrowborder" valign="top" width="21.21%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0278763423_p444143110271"><a name="en-us_topic_0278763423_p444143110271"></a><a name="en-us_topic_0278763423_p444143110271"></a>MASK</p>
</td>
<td class="cellrowborder" valign="top" width="52.53%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0278763423_p5441731112718"><a name="en-us_topic_0278763423_p5441731112718"></a><a name="en-us_topic_0278763423_p5441731112718"></a>Trace event mask</p>
</td>
<td class="cellrowborder" valign="top" width="26.26%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0278763423_p04411831102714"><a name="en-us_topic_0278763423_p04411831102714"></a><a name="en-us_topic_0278763423_p04411831102714"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0278763423_section94114312274"></a>

-   If the event mask is not set or the default parameter is used when this command is executed, only the task and interrupt event recording is enabled by default.
-   If  **MASK**  is added after  **trace\_mask**, the event recording function of the corresponding module is enabled.

## Examples<a name="en-us_topic_0278763423_section241120310279"></a>

1.  Enter  **trace\_mask 0**.
2.  Enter **trace\_mask 0xFFFFFFFF**.

## Output<a name="en-us_topic_0278763423_section241133182710"></a>

Run the  **trace\_mask 0**  command to set the events of all modules not to be recorded. After the command is executed successfully, no information is displayed.

```
Huawei LiteOS # trace_mask 0

Huawei LiteOS #
```

Run the  **trace\_mask 0xFFFFFFFF**  command to set the events of all modules to be recorded. After the command is executed successfully, no information is displayed.

```
Huawei LiteOS # trace_mask 0xFFFFFFFF

Huawei LiteOS #
```

