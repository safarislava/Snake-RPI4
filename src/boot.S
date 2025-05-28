.section ".text.boot"
.global _start

_start:
    ldr x0, =_start
    mov sp, x0
    
    bl reset_handler
    b .
