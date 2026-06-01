.global _start  @全局编号

_start:
    /*使能所有外设时钟*/
    ldr r0, =0x020C4068     @寄存器地址CCGR0
    ldr r1, =0xffffffff     @设入的值
    str r1, [r0]            @将r1的数值写入r0

    ldr r0, =0x020C406C     @寄存器地址CCGR1
    str r1, [r0]            @将r1的数值写入r0

    ldr r0, =0x020C4070     @寄存器地址CCGR2
    str r1, [r0]            @将r1的数值写入r0

    ldr r0, =0x020C4074     @寄存器地址CCGR3
    str r1, [r0]            @将r1的数值写入r0

    ldr r0, =0x020C4078     @寄存器地址CCGR4
    str r1, [r0]            @将r1的数值写入r0

    ldr r0, =0x020C407C     @寄存器地址CCGR5
    str r1, [r0]            @将r1的数值写入r0

    ldr r0, =0x020C4080     @寄存器地址CCGR6
    str r1, [r0]            @将r1的数值写入r0

    /*配置引脚复用*/
    ldr r0, =0x020E0068     @寄存器地址IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03
    ldr r1, =0x5            @设入的值,配置为GPIO1_IO03
    str r1, [r0]            @将r1的数值写入r0

    /*配置引脚属性*/
    ldr r0, =0x020E02F4     @寄存器地址IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03
    ldr r1, =0x10B0         @设入的值,配置为驱动能力为R0/6,上拉使能,100K上拉
    str r1, [r0]            @将r1的数值写入r0

    /*配置GPIO1_IO03为输出模式*/
    ldr r0, =0x0209C004     @寄存器地址
    ldr r1, [r0]            @读取GPIO1的GDIR寄存器值
    orr r1, r1, #0x8        @将GPIO1_IO03对应的位设置为1，配置为输出模式
    str r1, [r0]            @将修改后的值写回GPIO1的GDIR寄存器

    /*点亮LED*/
    ldr r0, =0x0209C000     @寄存器地址
    ldr r1, =0x0            @设入的值,配置为输出低电平，点亮LED
    ldr r1, [r0]            @读取GPIO1的DR寄存器值 
loop:
    b loop
