# Static Registration Programming Example<a name="EN-US_TOPIC_0312409019"></a>

## Example Description<a name="en-us_topic_0175230393_section12652506102830"></a>

This example shows how to add a shell command named  **test**  through static registration.

1.  Define the command processing function  **cmd\_test**  that will be called to add the new command.
2.  Call the  **SHELLCMD\_ENTRY**  function to add the new command.
3.  Add the parameter of the new command to the link option  **liteos\_tables\_ldflags.mk**.
4.  Run  **make menuconfig**  to enable the shell.
5.  Recompile code and run Huawei LiteOS.

## Example Code<a name="en-us_topic_0175230393_section15395384102858"></a>

1.  Define the cmd\_test function.

    ```c
    #include "shell.h"
    #include "shcmd.h"
    
    int cmd_test(void)
    {
        printf("hello everybody!\n");
        return 0;
    }
    ```

2.  Add the new command.

    ```c
    SHELLCMD_ENTRY(test_shellcmd, CMD_TYPE_EX, "test", 0, (CMD_CBK_FUNC)cmd_test);
    ```

3.  Add the command parameter to the linker options.

    Add  **-utest\_shellcmd**  to **LITEOS\_TABLES\_LDFLAGS** in **build/mk/liteos\_tables\_ldflags.mk**.

4.  Run  **make menuconfig**  to enable the shell, that is, set  **LOSCFG\_SHELL**  to  **y**.
5.  Recompile the commands.

    ```
    make clean;make
    ```


## Verification<a name="en-us_topic_0175230393_section6553141911578"></a>

Burn a new system image and restart the system. Run the  **help**  command to view all the registered commands in the current system. You can find that the  **test**  command is registered.

