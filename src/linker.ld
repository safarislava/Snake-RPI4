ENTRY(_start)

SECTIONS
{
    . = 0x80000;
    .text.boot : { *(.text.boot) }
    .text : { *(.vectors) *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : { *(.bss*) }
}