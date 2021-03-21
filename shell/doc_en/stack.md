# stack<a name="EN-US_TOPIC_0312409058"></a>

## Function<a name="en-us_topic_0291387623_section54470097115514"></a>

The  **stack**  command is used to view information about all the stacks in the current OS.

## Format<a name="en-us_topic_0291387623_section47362124115514"></a>

stack

## User Guide<a name="en-us_topic_0291387623_section11139120115514"></a>

This function is enabled by default. 

## Example<a name="en-us_topic_0291387623_section19975367115514"></a>

Enter  **stack**.

## Output<a name="en-us_topic_0291387623_section66528011115514"></a>

Run the  **stack**  command to view information about all stacks in the system.

```
Huawei LiteOS # stack

 stack name    cpu id     stack addr     total size   used size
 ----------    ------     ---------      --------     --------
  udf_stack      3        0x3c800        0x28         0x0   
  udf_stack      2        0x3c828        0x28         0x0   
  udf_stack      1        0x3c850        0x28         0x0   
  udf_stack      0        0x3c878        0x28         0x0   
  abt_stack      3        0x3c8a0        0x28         0x0   
  abt_stack      2        0x3c8c8        0x28         0x0   
  abt_stack      1        0x3c8f0        0x28         0x0   
  abt_stack      0        0x3c918        0x28         0x0   
  fiq_stack      3        0x3ca40        0x40         0x0   
  fiq_stack      2        0x3ca80        0x40         0x0   
  fiq_stack      1        0x3cac0        0x40         0x0   
  fiq_stack      0        0x3cb00        0x40         0x0   
  svc_stack      3        0x3cb40        0x2000       0x524 
  svc_stack      2        0x3eb40        0x2000       0x524 
  svc_stack      1        0x40b40        0x2000       0x524 
  svc_stack      0        0x42b40        0x2000       0x528 
  irq_stack      3        0x3c940        0x40         0x0   
  irq_stack      2        0x3c980        0x40         0x0   
  irq_stack      1        0x3c9c0        0x40         0x0   
  irq_stack      0        0x3ca00        0x40         0x0   
  exc_stack      3        0x44b40        0x1000       0x0   
  exc_stack      2        0x45b40        0x1000       0x0   
  exc_stack      1        0x46b40        0x1000       0x0   
  exc_stack      0        0x47b40        0x1000       0x0
```

