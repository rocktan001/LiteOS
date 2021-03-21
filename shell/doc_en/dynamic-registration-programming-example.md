# Dynamic Registration Programming Example<a name="EN-US_TOPIC_0312409020"></a>

## Example Description<a name="en-us_topic_0299028381_section34072723104457"></a>

This example shows how to add a shell command named  **test**  through dynamic registration.

1.  Define the command processing function  **cmd\_test**  that will be called to add the new command.
2.  Call the  **osCmdReg**  function to add the new command.
3.  Run  **make menuconfig**  to enable the shell.
4.  Recompile and run.

## Example Code<a name="en-us_topic_0299028381_section10666408193750"></a>

1.  Define the command processing function  **cmd\_test**  that will be called to add the new command.

    ```c
    #include "shell.h"
    #include "shcmd.h"
    
    int cmd_test(void)
    {
        printf("hello everybody!\n");
        return 0;
    }
    ```

2.  Call the  **osCmdReg**  function in the  **app\_init**  function for dynamical registration.

    ```c
    void app_init(void)
    {
         ....
         ....
         osCmdReg(CMD_TYPE_EX, "test", 0,(CMD_CBK_FUNC)cmd_test);
         ....
    }
    ```

3.  Run  **make menuconfig**  to enable the shell, that is, set  **LOSCFG\_SHELL**  to  **y**.
4.  Recompile the code.

    ```
    make clean;make
    ```


## Verification<a name="en-us_topic_0299028381_section6553141911578"></a>

Burn a new system image and restart the system. Run the  **help**  command to view all the registered commands in the current system. You can find that the  **test**  command is registered.

