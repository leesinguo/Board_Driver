SECTIONS{
    . = 0x87800000; /* 运行地址 */
    .text : {
        start.o
        *(.text)
    }
    .rodata ALIGN(4) : {
        *(.rodata)
    }
    .data ALIGN(4) : {
        *(.data)
    }
    __bss_start = .;
    .bss ALIGN(4) : {
        *(.bss) *(COMMON) /* COMMON段也放在.bss中 */
    }
    __bss_end = .;
}
