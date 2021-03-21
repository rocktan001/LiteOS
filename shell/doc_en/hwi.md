# hwi<a name="EN-US_TOPIC_0312409049"></a>

## Function<a name="en-us_topic_0175230278_section52746037103926"></a>

The **hwi** command is used to query the information about current interruptions.

## Format<a name="en-us_topic_0175230278_section65591119103926"></a>

hwi

## User Guide<a name="en-us_topic_0175230278_section7497889103926"></a>

-   Enter  **hwi**  to display the interruption number, the number of occurrences, and the name of each current interruption.
-   If  **LOSCFG\_CPUP\_INCLUDE\_IRQ**  is selected, the processing time \(cycles\), CPU usage and interruption type of each interruption are displayed. You can run the  **make menuconfig**  command to enable the  **Enable Cpup include irq**  menu item to enable the macro.

    ```
    Kernel ---> Enable Extend Kernel ---> Enable Cpup ---> Enable Cpup include irq
    ```

    For details about the macro, see  [Development Process](/doc/LiteOS_Maintenance_Guide_en/development-guidelines.md#en-us_topic_0175230412_section5280239320811).


## Example<a name="en-us_topic_0175230278_section30143519103926"></a>

Enter  **hwi**.

## Output<a name="en-us_topic_0175230278_section30027462103926"></a>

1.  Information of interruptions with  **LOSCFG\_CPUP\_INCLUDE\_IRQ**  unselected.

    ```
    Huawei LiteOS # hwi
    InterruptNo     Count     Name
    35:             1364:
    36:             0:
    40:             79:       uart_pl011
    ```

2.  Information of interruptions with  **LOSCFG\_CPUP\_INCLUDE\_IRQ**  selected.

    ```
    Huawei LiteOS # hwi
    InterruptNo Count   Name   CYCLECOST  CPUUSE CPUUSE10s CPUUSE1s mode
            3:  1333            122       0.0    0.0       0.0    normal
            4:  0               0         0.0    0.0       0.0    normal
            5:  59   uart_pl011 305       0.0    0.0       0.0    normal
           12:  96      ETH     131       0.0    0.0       0.0    normal
    ```


