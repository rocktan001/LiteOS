# memcheck<a name="EN-US_TOPIC_0312409047"></a>

## Function<a name="en-us_topic_0175230403_section4476907513433"></a>

The  **memcheck**  command is used to check whether the dynamically applied memory is complete and whether a node is damaged due to memory overwriting.

## Format<a name="en-us_topic_0175230403_section2174806813433"></a>

memcheck

## User Guide<a name="en-us_topic_0175230403_section3280846113433"></a>

-   Enable the memory integrity check function.
    -   Currently, only the  **bestfit**  memory management algorithm supports this command. You need to enable  **LOSCFG\_KERNEL\_MEM\_BESTFIT**.

        ```
        Kernel ---> Memory Management ---> Dynamic Memory Management Algorithm ---> bestfit
        ```

    -   This command depends on  **LOSCFG\_BASE\_MEM\_NODE\_INTEGRITY\_CHECK**. Before running this command, enable the  **Enable integrity check or not**  menu item as follows:

        ```
        Debug  ---> Enable a Debug Version ---> Enable MEM Debug ---> Enable integrity check or not
        ```


-   If memory leak does not occur, the output of memcheck is "memcheck over, all passed! "
-   If nodes are not completed memory pool, the output is the information about the memory of the node that destroyed.

## Example<a name="en-us_topic_0175230403_section2661303313433"></a>

Enter  **memcheck**.

## Output<a name="en-us_topic_0175230403_section036810911200"></a>

-   If no memory overwriting occurs, the output of the  **memcheck**  command is as follows.

    ```
    Huawei LiteOS # memcheck
    system memcheck over, all passed!
    ```

-   If memory overwriting occurs, the output of the  **memcheck**  command is as follows.

    ```
    Huawei LiteOS # memcheck
    [ERR][OsMemIntegrityCheck], 1145, memory check error!
    freeNodeInfo.pstPrev:(nil) is out of legal mem range[0x80353540, 0x84000000]
    
    broken node head: (nil)  (nil)  (nil)  0x0, pre node head: 0x7fc6a31b  0x8  0x80395ccc  0x80000110
    
    ---------------------------------------------
     dump mem tmpNode:0x80395df4 ~ 0x80395e34
    
     0x80395df4 :00000000 00000000 00000000 00000000
     0x80395e04 :cacacaca cacacaca cacacaca cacacaca
     0x80395e14 :cacacaca cacacaca cacacaca cacacaca
     0x80395e24 :cacacaca cacacaca cacacaca cacacaca
    
    ---------------------------------------------
     dump mem :0x80395db4 ~ tmpNode:0x80395df4
    
     0x80395db4 :00000000 00000000 00000000 00000000
     0x80395dc4 :00000000 00000000 00000000 00000000
     0x80395dd4 :00000000 00000000 00000000 00000000
     0x80395de4 :00000000 00000000 00000000 00000000
    
    ---------------------------------------------
    cur node: 0x80395df4
    pre node: 0x80395ce4
    pre node was allocated by task:SerialShellTask
    cpu0 is in exc.
    cpu1 is running.
    excType:software interrupt
    taskName = SerialShellTask
    taskId = 8
    task stackSize = 12288
    system mem addr = 0x80353540
    excBuffAddr pc = 0x80210b78
    excBuffAddr lr = 0x80210b7c
    excBuffAddr sp = 0x803b2d50
    excBuffAddr fp = 0x80280368
    R0         = 0x59
    R1         = 0x600101d3
    R2         = 0x0
    R3         = 0x8027a300
    R4         = 0x1
    R5         = 0xa0010113
    R6         = 0x80395e04
    R7         = 0x80317254
    R8         = 0x803b2de4
    R9         = 0x4
    R10        = 0x803afca4
    R11        = 0x80280368
    R12        = 0x1
    CPSR       = 0x600101d3
    ```

    The key output items are described as follows:

    -   "mem check error" indicates that the memory node is damaged.
    -   "cur node" indicates the node where the memory is illegally overwritten and the memory address is printed.
    -   "pre node" indicates the node preceding the node where the memory is illegally overwritten, and the node address is printed.
    -   "pre node was allocated by task" indicates that memory overwriting occurs in  **SerialShellTask**.
    -   "taskName" and "taskId" indicate the name and ID of an abnormal task.


