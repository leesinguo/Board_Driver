#ifndef __INTERRUPT_H_
#define __INTERRUPT_H_

#include "type.h"
#include "MCIMX6Y2.h"

#define GPIOX_IRQ_TABLE_SIZE 32

/* 定义中断处理函数 */
typedef void (*system_irq_handler_func)(uint32_t gicciarr_num, void *param);

/* 中断处理函数结构体 */
typedef struct {
    system_irq_handler_func irqhandler;        /* 中断处理函数 */
    void *userparam;                        /* 中断处理函数参数 */
}sys_irq_handle_t;

void imx_interrupt_init(void);
void system_register_irq_handler(IRQn_Type IRQ, system_irq_handler_func func, void *userdata);

#endif // !__INTERRUPTH_H
