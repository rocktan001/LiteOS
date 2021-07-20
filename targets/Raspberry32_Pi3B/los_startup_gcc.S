#include "arch/exception.h"
#include "arch/regs.h"

/* stack */
.global __exc_stack_top
.global __irq_stack_top
.global __fiq_stack_top
.global __svc_stack_top
.global __abt_stack_top
.global __undef_stack_top
.global __exc_stack
.global __irq_stack
.global __fiq_stack
.global __svc_stack
.global __abt_stack
.global __undef_stack

/* param0 is stack top, param1 is stack size, param2 is magic num */
.macro STACK_MAGIC_SET param0, param1, param2
    ldr     r0, =\param0
    mov     r1, \param1
    ldr     r2, =\param2
    bl      excstack_magic
.endm

.code   32
.section ".vectors","ax"
.globl system_vectors
system_vectors:

    b   _reset
    b   _osExceptUndefInstrHdl
    b   _osExceptSwiHdl
    b   _osExceptPrefetchAbortHdl
    b   _osExceptDataAbortHdl
    b   _osExceptAddrAbortHdl
    b   OsIrqHandler
    b   _osExceptFiqHdl

.text
/* reset entry */
.globl _reset
_reset:
    mrs r0, cpsr_all 
    and r0, r0, #0x1F
    mov r8, #0x1A
    cmp r0, r8
    beq hypHandle
    b common
hypHandle:
    ldr r1, =common
    msr ELR_hyp, r1
    mrs r1, cpsr_all
    and r1, r1, #0x1f
    orr r1, r1, #0x13
    msr SPSR_hyp, r1	/* return SVC */
    eret

common:
    /* get cpuid and keep it in r11 */
    mrc     p15, 0, r11, c0, c0, 5
    and     r11, r11, #MPIDR_CPUID_MASK

    /* set vector base 0x00000000 */
    mrc p15, 0, r0, c1, c0, 0        
    bic r0, #(1 << 13)
    mcr p15, 0, r0, c1, c0, 0

    /* disable mmu */
    mcr     p15, #0, r0, c8, c7, #0    @ invalidate tlb
    mrc     p15, #0, r0, c1, c0, #0
    bic     r0, r0, #1
    mcr     p15, #0, r0, c1, c0, #0    @ clear mmu bit
    dsb

    
    cmp     r11, #0
    bne     excstatck_loop_done


excstatck_loop:
    /* clear out the interrupt and exception stack and set magic num to check the overflow */
    ldr     r0, =__undef_stack
    ldr     r1, =__exc_stack_top
    bl      stack_init
    STACK_MAGIC_SET __undef_stack, #OS_EXC_UNDEF_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __abt_stack, #OS_EXC_ABT_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __irq_stack, #OS_EXC_IRQ_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __fiq_stack, #OS_EXC_FIQ_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __svc_stack, #OS_EXC_SVC_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __exc_stack, #OS_EXC_STACK_SIZE, OS_STACK_MAGIC_WORD

    /* clear .bss */
    mov     r0,#0                   /* get a zero                       */
    ldr     r1,=__bss_start         /* bss start                        */
    ldr     r2,=__bss_end           /* bss end                          */

bss_loop:
    cmp     r1,r2                   /* check if data to clear           */
    strlo   r0,[r1],#4              /* clear 4 bytes                    */
    blo     bss_loop                /* loop until done                  */

excstatck_loop_done:
    /* set svc stack, every cpu has OS_EXC_SVC_STACK_SIZE stack */
    ldr     r0, = __svc_stack_top
    mov     r1, #OS_EXC_SVC_STACK_SIZE
    mul     r1, r1, r11
    sub     r0, r0, r1
    mov     sp, r0

    /* enable fpu+neon */
    LDR     r0, =(0xF << 20)
    MCR     p15, 0, r0, c1, c0, 2

    MOV     r3, #0x40000000
    VMSR    FPEXC, r3

    cmp     r11, #0
    bne     cpu_start
    b main
    b       .

cpu_start:
    b       .

.text
/*
 * set magic num to stack top for all cpu
 * r0 is stack top, r1 is stack size, r2 is magic num
 */
excstack_magic:
    mov     r3, #0
excstack_magic_loop:
    str     r2, [r0]
    add     r0, r0, r1
    add     r3, r3, #1
    cmp     r3, #CORE_NUM
    blt     excstack_magic_loop
    bx      lr

/*
 * init stack to initial value
 * r0 is stack mem start, r1 is stack mem end
 */
stack_init:
    ldr     r2, =OS_STACK_INIT
    ldr     r3, =OS_STACK_INIT

/* 
 * Main loop sets 32 bytes at a time.
 */
stack_init_loop:
    .irp    offset, #0, #8, #16, #24
    strd    r2, r3, [r0, \offset]
    .endr
    add     r0, #32
    cmp     r0, r1
    blt     stack_init_loop
    bx      lr

.section ".int_stack", "wa", %nobits
.align  3

__undef_stack:
    .space OS_EXC_UNDEF_STACK_SIZE * CORE_NUM
__undef_stack_top:

__abt_stack:
    .space OS_EXC_ABT_STACK_SIZE * CORE_NUM
__abt_stack_top:

__fiq_stack:
    .space OS_EXC_FIQ_STACK_SIZE * CORE_NUM
__fiq_stack_top:

__irq_stack:
    .space OS_EXC_IRQ_STACK_SIZE * CORE_NUM
__irq_stack_top:

__svc_stack:
    .space OS_EXC_SVC_STACK_SIZE * CORE_NUM
__svc_stack_top:

__exc_stack:
    .space OS_EXC_STACK_SIZE * CORE_NUM
__exc_stack_top:

