# memused<a name="EN-US_TOPIC_0312409048"></a>

## Function<a name="en-us_topic_0175230629_section4476907513433"></a>

The **memused** command is used to view the function call stack LR information saved in the current system used node. Memory leaks can be detected by analyzing data.

## Format<a name="en-us_topic_0175230629_section2174806813433"></a>

memused

## User Guide<a name="en-us_topic_0175230629_section3280846113433"></a>

Run the  **make menuconfig**  command to enable memory leakage check.

-   Currently, only the  **bestfit**  memory management algorithm supports this function. You need to enable  **LOSCFG\_KERNEL\_MEM\_BESTFIT**.

    ```
    Kernel ---> Memory Management ---> Dynamic Memory Management Algorithm ---> bestfit
    ```


-   This command depends on  **LOSCFG\_MEM\_LEAKCHECK**. You can enable the  **Enable Function call stack of Mem operation recorded**  menu item.

    ```
    Debug  ---> Enable a Debug Version ---> Enable MEM Debug ---> Enable Function call stack of Mem operation recorded
    ```

    While opening this configuration, the function call relationship LR is recorded in the memory node control block when the memory operation is performed. If the memory node of the same call stack grows with time, there is a possibility of leakage. The location of the memory application can be traced through the LR. Focus on LR duplicate nodes.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:** 
    >
    >Memory usage and memory operation performance will be affected when this configuration is turned on, so it is only turned on when detecting memory leaks.


## Example<a name="en-us_topic_0175230629_section2661303313433"></a>

Enter  **memused**.

## Output<a name="en-us_topic_0175230629_section643948713433"></a>

```
Huawei LiteOS # memused
node         LR[0]       LR[1]       LR[2]
0x802d79e4:  0x8011d740  0x8011a990  0x00000000
0x802daa0c:  0x8011d5ec  0x8011d740  0x8011a990
0x802dca28:  0x8006e6f4  0x8006e824  0x8011d5ec
0x802e2a48:  0x8014daac  0x8014db4c  0x800f6da0
0x802e8a68:  0x8011d274  0x8011d654  0x8011d740
0x802e8a94:  0x8014daac  0x8014db4c  0x8011d494
0x802eeab4:  0x8011d4e0  0x8011d658  0x8011d740
0x802f4ad4:  0x8015326c  0x80152a20  0x800702bc
0x802f4b48:  0x8015326c  0x80152a20  0x800702bc
0x802f4bac:  0x801504d8  0x801505d8  0x80150834
0x802f4c08:  0x801504d8  0x801505d8  0x80150834
0x802f4c74:  0x801504d8  0x801505d8  0x80150834
0x802f4e08:  0x801504d8  0x801505d8  0x80150834
0x802f4e60:  0x801030e8  0x801504d8  0x801505d8
0x802f4e88:  0x80103114  0x801504d8  0x801505d8
0x802f4eb4:  0x801504d8  0x801505d8  0x80150834
0x802f4f7c:  0x801504d8  0x801505d8  0x80150834
0x802f5044:  0x801504d8  0x801505d8  0x80150834
0x802f510c:  0x800702bc  0x80118f24  0x00000000
```

