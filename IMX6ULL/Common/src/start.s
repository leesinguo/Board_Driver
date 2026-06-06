.global _start
.global _bss_start
.global _bss_end

_bss_start:
    .word __bss_start
_bss_end:
    .word __bss_end

_start:
    /*设置处理器进入SVC模式*/
    mrs r0, cpsr            @读取当前程序状态寄存器的值
    bic r0, r0, #0x1f       @清除模式位
    orr r0, r0, #0x13       @设置为SVC模式
    msr cpsr, r0            @写入程序状态寄存器

    /* 清除BSS段 */
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    mov r2, #0
bss_loop:
    stmia r0!, {r2}
    cmp r0, r1              @比较当前地址和BSS段结束地址
    ble bss_loop            @如果当前地址小于或等于BSS段结束地址，继续清零

    /*设置栈指针*/
    ldr sp, =0x80200000     @将0x80200000写入sp寄存器

    /*跳转到C语言main函数*/
    bl main                 @调用main函数
