# Development Guide<a name="EN-US_TOPIC_0302395693"></a>

## Usage Scenarios<a name="section71126813216"></a>

As an online debugging tool, the shell provided by Huawei LiteOS supports input and output over the serial port and common basic debugging functions. In addition, you can add customized commands. The new commands can be executed only after rebuilding and burning.

## Functions<a name="section122211518314"></a>

1.  For details about the shell commands provided by Huawei LiteOS, see the sections of detailed command description.
2.  The shell module of Huawei LiteOS provides the following APIs. For details about the APIs, see the API reference.

    <a name="en-us_topic_0175230296_table5999158320325"></a>
    <table><thead align="left"><tr id="en-us_topic_0175230296_row2323990220325"><th class="cellrowborder" valign="top" width="20.712071207120715%" id="mcps1.1.4.1.1"><p id="en-us_topic_0175230296_p1748969020325"><a name="en-us_topic_0175230296_p1748969020325"></a><a name="en-us_topic_0175230296_p1748969020325"></a>Function</p>
    </th>
    <th class="cellrowborder" valign="top" width="21.74217421742174%" id="mcps1.1.4.1.2"><p id="en-us_topic_0175230296_p5025139720325"><a name="en-us_topic_0175230296_p5025139720325"></a><a name="en-us_topic_0175230296_p5025139720325"></a>API</p>
    </th>
    <th class="cellrowborder" valign="top" width="57.54575457545755%" id="mcps1.1.4.1.3"><p id="en-us_topic_0175230296_p2204176620325"><a name="en-us_topic_0175230296_p2204176620325"></a><a name="en-us_topic_0175230296_p2204176620325"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="en-us_topic_0175230296_row1839119416414"><td class="cellrowborder" rowspan="2" valign="top" width="20.712071207120715%" headers="mcps1.1.4.1.1 "><p id="en-us_topic_0175230296_p695912961416"><a name="en-us_topic_0175230296_p695912961416"></a><a name="en-us_topic_0175230296_p695912961416"></a>Registration command</p>
    </td>
    <td class="cellrowborder" valign="top" width="21.74217421742174%" headers="mcps1.1.4.1.2 "><p id="en-us_topic_0175230296_p14457102619145"><a name="en-us_topic_0175230296_p14457102619145"></a><a name="en-us_topic_0175230296_p14457102619145"></a>SHELLCMD_ENTRY</p>
    </td>
    <td class="cellrowborder" valign="top" width="57.54575457545755%" headers="mcps1.1.4.1.3 "><p id="en-us_topic_0175230296_p17391204116414"><a name="en-us_topic_0175230296_p17391204116414"></a><a name="en-us_topic_0175230296_p17391204116414"></a>Static registration command</p>
    </td>
    </tr>
    <tr id="en-us_topic_0175230296_row795992971416"><td class="cellrowborder" valign="top" headers="mcps1.1.4.1.1 "><p id="en-us_topic_0175230296_p5959329101415"><a name="en-us_topic_0175230296_p5959329101415"></a><a name="en-us_topic_0175230296_p5959329101415"></a>osCmdReg</p>
    </td>
    <td class="cellrowborder" valign="top" headers="mcps1.1.4.1.2 "><p id="en-us_topic_0175230296_p1959192991411"><a name="en-us_topic_0175230296_p1959192991411"></a><a name="en-us_topic_0175230296_p1959192991411"></a>Dynamic registration command</p>
    </td>
    </tr>
    </tbody>
    </table>

    >![](public_sys-resources/icon-note.gif) **NOTE:** 
    >
    >Normally, static registration is applicable to common system commands, and dynamic registration is applicable user commands.
    >The static registration command has five input parameters, and the dynamic registration command has four input parameters. The first input parameter is unique for static registration. The other four input parameters are the same for the two registration commands.
    >-   First input parameter: Command variable name, which is used to set the link option \(**LITEOS\_TABLES\_LDFLAGS**  variable of  **build/mk/liteos\_tables\_ldflags.mk**\). For example, if the variable name is  **ls\_shellcmd**, the link option must be set to  **LITEOS\_TABLES\_LDFLAGS += -uls\_shellcmd**. This input parameter is unique to static registration and does not exist in dynamic registration.
    >-   Second input parameter: Command type. Currently, two command types are supported.
    >    -   **CMD\_TYPE\_EX**: Standard command parameters cannot be input. The command keywords entered by users are shielded. For example, if you enter  **ls /ramfs**, only  **/ramfs**, which corresponds to  **argv\[0\]**  in the command processing function, is transferred to the function. The keyword  **ls**  is not transferred.
    >    -   **CMD\_TYPE\_STD**: Standard command parameter can be input. All entered characters are input after being parsed by the command. For example, if you enter  **ls /ramfs**,  **ls**  and  **/ramfs**, which correspond to  **argv\[0\]**  and  **argv\[1\]**  respectively, are transferred to the command processing function.
    >-   Third input parameter: Command keyword, which is the name of the command processing function in the shell. The command keyword must be unique. That is, two different commands cannot share the same command keyword. Otherwise, only one is executed. During user command execution, if multiple commands share the same keyword, the shell executes only the first one among the  **help**  commands.
    >-   Fourth input parameter: Maximum number of input parameters for the command processing function.
    >    -   Currently, this parameter cannot be set for the static registration command.
    >    -   For the dynamic registration command, this parameter can be set to  **32**, which indicates a maximum of 32 input parameters, or  **XARGS**  \(defined as  **0xffffffff**  in the code\), which indicates no limit for the number of parameters.
    >-   Fifth input parameter: Name of the command processing function, that is, the function called during the execution by the shell.


## Configuration Items<a name="section16681751777"></a>

Run the  **make menuconfig**  command and choose  **Debug**  \>  **Enable a Debug Version**  \>  **Enable Shell**  to configure the shell.

<a name="en-us_topic_0175230296_table1813095045911"></a>
<table><thead align="left"><tr id="en-us_topic_0175230296_row1913095035911"><th class="cellrowborder" valign="top" width="21.29%" id="mcps1.1.6.1.1"><p id="en-us_topic_0175230296_p17130175013598"><a name="en-us_topic_0175230296_p17130175013598"></a><a name="en-us_topic_0175230296_p17130175013598"></a>Configuration Item</p>
</th>
<th class="cellrowborder" valign="top" width="34.56%" id="mcps1.1.6.1.2"><p id="en-us_topic_0175230296_p313019506593"><a name="en-us_topic_0175230296_p313019506593"></a><a name="en-us_topic_0175230296_p313019506593"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="10.99%" id="mcps1.1.6.1.3"><p id="en-us_topic_0175230296_p10130105012592"><a name="en-us_topic_0175230296_p10130105012592"></a><a name="en-us_topic_0175230296_p10130105012592"></a>Value Range</p>
</th>
<th class="cellrowborder" valign="top" width="10.440000000000001%" id="mcps1.1.6.1.4"><p id="en-us_topic_0175230296_p7130205019593"><a name="en-us_topic_0175230296_p7130205019593"></a><a name="en-us_topic_0175230296_p7130205019593"></a>Default Value</p>
</th>
<th class="cellrowborder" valign="top" width="22.720000000000002%" id="mcps1.1.6.1.5"><p id="en-us_topic_0175230296_p25049101933"><a name="en-us_topic_0175230296_p25049101933"></a><a name="en-us_topic_0175230296_p25049101933"></a>Dependency</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0175230296_row101311250135920"><td class="cellrowborder" valign="top" width="21.29%" headers="mcps1.1.6.1.1 "><p id="en-us_topic_0175230296_p81312050105917"><a name="en-us_topic_0175230296_p81312050105917"></a><a name="en-us_topic_0175230296_p81312050105917"></a>LOSCFG_SHELL</p>
</td>
<td class="cellrowborder" valign="top" width="34.56%" headers="mcps1.1.6.1.2 "><p id="en-us_topic_0175230296_p1213185095911"><a name="en-us_topic_0175230296_p1213185095911"></a><a name="en-us_topic_0175230296_p1213185095911"></a>Tailoring switch of the shell module.</p>
</td>
<td class="cellrowborder" valign="top" width="10.99%" headers="mcps1.1.6.1.3 "><p id="en-us_topic_0175230296_p171317509593"><a name="en-us_topic_0175230296_p171317509593"></a><a name="en-us_topic_0175230296_p171317509593"></a>YES/NO</p>
</td>
<td class="cellrowborder" valign="top" width="10.440000000000001%" headers="mcps1.1.6.1.4 "><p id="en-us_topic_0175230296_p0131165014591"><a name="en-us_topic_0175230296_p0131165014591"></a><a name="en-us_topic_0175230296_p0131165014591"></a>YES</p>
</td>
<td class="cellrowborder" valign="top" width="22.720000000000002%" headers="mcps1.1.6.1.5 "><p id="en-us_topic_0175230296_p8504141016310"><a name="en-us_topic_0175230296_p8504141016310"></a><a name="en-us_topic_0175230296_p8504141016310"></a>LOSCFG_DEBUG_VERSION(=y)  &amp;&amp; LOSCFG_DRIVERS_UART(=y)</p>
</td>
</tr>
<tr id="en-us_topic_0175230296_row3131175017594"><td class="cellrowborder" valign="top" width="21.29%" headers="mcps1.1.6.1.1 "><p id="en-us_topic_0175230296_p111311850165920"><a name="en-us_topic_0175230296_p111311850165920"></a><a name="en-us_topic_0175230296_p111311850165920"></a>LOSCFG_SHELL_CONSOLE (it is unavailable in the open-source version)</p>
</td>
<td class="cellrowborder" valign="top" width="34.56%" headers="mcps1.1.6.1.2 "><p id="en-us_topic_0175230296_p713115085919"><a name="en-us_topic_0175230296_p713115085919"></a><a name="en-us_topic_0175230296_p713115085919"></a>Directly interact the shell with the console.</p>
</td>
<td class="cellrowborder" valign="top" width="10.99%" headers="mcps1.1.6.1.3 "><p id="en-us_topic_0175230296_p1313195018593"><a name="en-us_topic_0175230296_p1313195018593"></a><a name="en-us_topic_0175230296_p1313195018593"></a>YES/NO</p>
</td>
<td class="cellrowborder" valign="top" width="10.440000000000001%" headers="mcps1.1.6.1.4 "><p id="en-us_topic_0175230296_p3131650135913"><a name="en-us_topic_0175230296_p3131650135913"></a><a name="en-us_topic_0175230296_p3131650135913"></a>YES</p>
</td>
<td class="cellrowborder" valign="top" width="22.720000000000002%" headers="mcps1.1.6.1.5 "><p id="en-us_topic_0175230296_p135047101932"><a name="en-us_topic_0175230296_p135047101932"></a><a name="en-us_topic_0175230296_p135047101932"></a>LOSCFG_SHELL(=y)</p>
</td>
</tr>
<tr id="en-us_topic_0175230296_row2131650135914"><td class="cellrowborder" valign="top" width="21.29%" headers="mcps1.1.6.1.1 "><p id="en-us_topic_0175230296_p11311150125915"><a name="en-us_topic_0175230296_p11311150125915"></a><a name="en-us_topic_0175230296_p11311150125915"></a>LOSCFG_SHELL_UART</p>
</td>
<td class="cellrowborder" valign="top" width="34.56%" headers="mcps1.1.6.1.2 "><p id="en-us_topic_0175230296_p3131115095911"><a name="en-us_topic_0175230296_p3131115095911"></a><a name="en-us_topic_0175230296_p3131115095911"></a>Directly interact the shell with the UART driver.</p>
</td>
<td class="cellrowborder" valign="top" width="10.99%" headers="mcps1.1.6.1.3 "><p id="en-us_topic_0175230296_p1613195015917"><a name="en-us_topic_0175230296_p1613195015917"></a><a name="en-us_topic_0175230296_p1613195015917"></a>YES/NO</p>
</td>
<td class="cellrowborder" valign="top" width="10.440000000000001%" headers="mcps1.1.6.1.4 "><p id="en-us_topic_0175230296_p1513145015916"><a name="en-us_topic_0175230296_p1513145015916"></a><a name="en-us_topic_0175230296_p1513145015916"></a>NO</p>
</td>
<td class="cellrowborder" valign="top" width="22.720000000000002%" headers="mcps1.1.6.1.5 "><p id="en-us_topic_0175230296_p14504141014319"><a name="en-us_topic_0175230296_p14504141014319"></a><a name="en-us_topic_0175230296_p14504141014319"></a>LOSCFG_DRIVERS_UART(=y)</p>
</td>
</tr>
</tbody>
</table>

## Development Process of Adding a Shell Command<a name="section13835461177"></a>

The following uses the  **ls**  command as an example to describe the typical development process of adding a shell command.

1.  Define the shell command processing function.

    The shell command processing function is used to process registered commands. For example, define a command processing function  **osShellCmdLs**  to process the  **ls**  command, and declare the command processing function prototype in the header file.

    ```c
    int osShellCmdLs(int argc, const char **argv);
    ```

    >![](public_sys-resources/icon-notice.gif) **NOTICE:** 
    >
    >The parameters of the command processing function are similar to those of the  **main**  function in the C language, including the following two input parameters:
    >-   **argc**: Number of parameters in the shell command. Whether the command keyword is included in the parameter value depends on the command type when the command is registered.
    >-   **argv**: Pointer array. Each element points to a character string, which is the parameter transferred to the command processing function during the shell command execution. Whether the command keyword is included in the parameter value depends on the command type when the command is registered.

2.  Register a command.

    The command can be registered statically and dynamically when the OS is running.

    -   Static registration

        ```c
        #include "shcmd.h"
        SHELLCMD_ENTRY(ls_shellcmd, CMD_TYPE_EX, "ls", XARGS, (CMD_CBK_FUNC)osShellCmdLs);
        ```

    -   Dynamic registration

        ```c
        #include "shell.h"
        osCmdReg(CMD_TYPE_EX, "ls", XARGS, (CMD_CBK_FUNC)osShellCmdLs);
        ```

3.  For static registration command mode, set the link option \(LITEOS\_TABLES\_LDFLAGS variable\) in  **build/mk/liteos\_tables\_ldflags.mk**.
4.  Run  **make menuconfig**  to enable the shell. For details, see  [Configuration Items](#configuration-items).
5.  After compiling and burning the system, you can run the added shell command.

## Running Shell Command<a name="section14687172311412"></a>

1.  Use a serial port terminal tool \(such as xShell\) to connect to the serial port.
2.  Select the SERIAL protocol and set SERIAL. Select the corresponding serial port number and set the baud rate to  **115200**.
3.  Restart the development board. After the system is started, the  **Huawei LiteOS \#**  prompt is displayed in the serial port tool.

    ```
    Huawei LiteOS #
    ```

    Enter a command and press  **Enter**  to run the command.

    -   You can press  **Tab**  to automatically complete the matching item. If there are multiple matching items, supplement common characters and output multiple matching items.
    -   You can press the Backspace key to delete a character. If you enter a Chinese character in the UTF8 format, you can delete the character by rolling back three times. The default language is English.
    -   You can press the up or down arrow key to select a history command.


