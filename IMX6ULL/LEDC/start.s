.global _start

_start:
    /*设置处理器进入SVC模式*/
    mrs r0, cpsr            @读取当前程序状态寄存器的值
    bic r0, r0, #0x1f       @清除模式位
    orr r0, r0, #0x13       @设置为SVC模式
    msr cpsr, r0            @写入程序状态寄存器

    /*设置栈指针*/
    ldr sp, =0x80200000     @将0x80200000写入sp寄存器

    /*跳转到C语言main函数*/
    bl main                 @调用main函数
