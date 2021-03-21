# uname<a name="EN-US_TOPIC_0312409024"></a>

## Function<a name="en-us_topic_0175230301_section676257315176"></a>

The  **uname** command is used to display the current OS name, time of OS building, and version of Huawei LiteOS.

## Format<a name="en-us_topic_0175230301_section3096931815176"></a>

uname \[_-a _|_ -s _|_ -t  _|_ -v_   |  _--help_\]

## Parameter Description<a name="en-us_topic_0175230301_section2805486115176"></a>

<a name="en-us_topic_0175230301_table6399415210235"></a>
<table><thead align="left"><tr id="en-us_topic_0175230301_row2195413910235"><th class="cellrowborder" valign="top" width="26.71%" id="mcps1.1.3.1.1"><p id="en-us_topic_0175230301_p3345482910235"><a name="en-us_topic_0175230301_p3345482910235"></a><a name="en-us_topic_0175230301_p3345482910235"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="73.29%" id="mcps1.1.3.1.2"><p id="en-us_topic_0175230301_p2548661510235"><a name="en-us_topic_0175230301_p2548661510235"></a><a name="en-us_topic_0175230301_p2548661510235"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230301_row2024022710334"><td class="cellrowborder" valign="top" width="26.71%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230301_p2884569610334"><a name="en-us_topic_0175230301_p2884569610334"></a><a name="en-us_topic_0175230301_p2884569610334"></a>-a</p>
</td>
<td class="cellrowborder" valign="top" width="73.29%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230301_p5480005810334"><a name="en-us_topic_0175230301_p5480005810334"></a><a name="en-us_topic_0175230301_p5480005810334"></a>Display all information.</p>
</td>
</tr>
<tr id="en-us_topic_0175230301_row1433513210347"><td class="cellrowborder" valign="top" width="26.71%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230301_p2029506910347"><a name="en-us_topic_0175230301_p2029506910347"></a><a name="en-us_topic_0175230301_p2029506910347"></a>-s</p>
</td>
<td class="cellrowborder" valign="top" width="73.29%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230301_p3328793110347"><a name="en-us_topic_0175230301_p3328793110347"></a><a name="en-us_topic_0175230301_p3328793110347"></a>OS name</p>
</td>
</tr>
<tr id="en-us_topic_0175230301_row16746104474820"><td class="cellrowborder" valign="top" width="26.71%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230301_p881511410342"><a name="en-us_topic_0175230301_p881511410342"></a><a name="en-us_topic_0175230301_p881511410342"></a>-t</p>
</td>
<td class="cellrowborder" valign="top" width="73.29%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230301_p4293562710342"><a name="en-us_topic_0175230301_p4293562710342"></a><a name="en-us_topic_0175230301_p4293562710342"></a>Displays the OS building time.</p>
</td>
</tr>
<tr id="en-us_topic_0175230301_row4950562210235"><td class="cellrowborder" valign="top" width="26.71%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230301_p5053240910235"><a name="en-us_topic_0175230301_p5053240910235"></a><a name="en-us_topic_0175230301_p5053240910235"></a>-v</p>
</td>
<td class="cellrowborder" valign="top" width="73.29%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230301_p438626391033"><a name="en-us_topic_0175230301_p438626391033"></a><a name="en-us_topic_0175230301_p438626391033"></a>Version</p>
</td>
</tr>
<tr id="en-us_topic_0175230301_row3930805314256"><td class="cellrowborder" valign="top" width="26.71%" headers="mcps1.1.3.1.1 "><p id="en-us_topic_0175230301_p2983571114256"><a name="en-us_topic_0175230301_p2983571114256"></a><a name="en-us_topic_0175230301_p2983571114256"></a>--help</p>
</td>
<td class="cellrowborder" valign="top" width="73.29%" headers="mcps1.1.3.1.2 "><p id="en-us_topic_0175230301_p77354614256"><a name="en-us_topic_0175230301_p77354614256"></a><a name="en-us_topic_0175230301_p77354614256"></a>Prompt of uname command format</p>
</td>
</tr>
</tbody>
</table>

## User Guide<a name="en-us_topic_0175230301_section338301615176"></a>

-   If this parameter is not specified, the OS name is displayed by default.
-   The  **uname**  parameters cannot be used together.

## Example<a name="en-us_topic_0175230301_section4315602815176"></a>

Enter  **uname -a**.

## Output<a name="en-us_topic_0175230301_section1440763015176"></a>

Run the  **uname -a**  command to obtain the system information.

```
Huawei LiteOS # uname -a
Huawei LiteOS V200R002C00SPC050B011 Huawei LiteOS 3.2.2 Mar 30 2019 16:09:28
```

