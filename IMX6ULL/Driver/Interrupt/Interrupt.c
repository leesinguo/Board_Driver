#include "core_ca7.h"
#include "type.h"
#include "MCIMX6Y2.h"
#include "gpio.h"
#include "Interrupt.h"

/* 中断处理函数表 */
LOCAL sys_irq_handle_t g_irq_table[NUMBER_OF_INT_VECTORS] = {{0}};

/* 中断嵌套计数器 */
LOCAL uint32_t g_irqnest_count = 0;

/* 默认中断处理函数 */
LOCAL void default_irq_handler(uint32_t gicciarr_num, void *param)
{
    while (TRUE) {

    }
}

/* 初始化中断处理函数表 */
LOCAL void system_irqtable_init(void)
{
    uint32_t i = 0;
    g_irqnest_count = 0;

    for (i = 0; i < NUMBER_OF_INT_VECTORS; i++) {
        g_irq_table[i].irqhandler = default_irq_handler;
        g_irq_table[i].userparam = NULL;
    }
}

/* 注册中断处理函数 */
void system_register_irq_handler(IRQn_Type IRQ, system_irq_handler_func func, void *userdata)
{
    g_irq_table[IRQ].irqhandler = func;
    g_irq_table[IRQ].userparam = userdata;   
}

/* 中断初始化 */
void imx_interrupt_init(void)
{
    GIC_Init();
    system_irqtable_init();
    /* 中断向量偏移 */
    __set_VBAR(0x87800000);
}

/* 具体的中断处理函数, IRQ_Handler会调用次函数 */
void system_irqhandler(uint32_t gicciar)
{
    uint32_t intrrupt_num = gicciar & 0x3ff;
    
    /* 检查中断ID */
    if (intrrupt_num > NUMBER_OF_INT_VECTORS) {
        return ;
    }
    g_irqnest_count++;
    /* 根据中断ID号读取中断处理函数 */
    g_irq_table[intrrupt_num].irqhandler(intrrupt_num, g_irq_table[intrrupt_num].userparam);
    g_irqnest_count--;
}
