.section ".text.boot"
.global _start
.global vectors

_start:
    ldr x0, =vectors
    msr vbar_el1, x0

    ldr x0, =_irq_stack   
    msr sp_el1, x0      

    ldr x0, =_start
    mov sp, x0
    
    bl kernel_main
    b .

.align 11               
.global vectors
vectors:
    .align 7
    b _start             // Reset handler
    .align 7
    b .                  // Undefined Instruction
    .align 7
    b .                  // SWI
    .align 7
    b .                  // Prefetch Abort
    .align 7
    b .                  // Data Abort
    .align 7
    b .                  // Reserved
    .align 7
    b irq_vector        // IRQ
    .align 7
    b .                  // FIQ         

irq_vector:
    stp x0, x1, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x20, x21, [sp, #-16]!
    stp x22, x23, [sp, #-16]!
    stp x24, x25, [sp, #-16]!
    stp x26, x27, [sp, #-16]!
    stp x28, x29, [sp, #-16]!
    str x30, [sp, #-16]!
    bl irq_handler   
    ldr x30, [sp], #16
    ldp x28, x29, [sp], #16
    ldp x26, x27, [sp], #16
    ldp x24, x25, [sp], #16
    ldp x22, x23, [sp], #16
    ldp x20, x21, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x0, x1, [sp], #16
    eret    