#ifndef __EPIT_H_
#define __EPIT_H_

#include "type.h"

#define EPIT_MAX_CLK_FRAC   4095
#define EPIT_COUNT          2

#define EPIT_COMPARE_EVENT_OCCURRED     1
#define EPIT_COMPARE_EVENT_NO_OCCURRED  0

typedef struct {
    uint32_t count_value;
    uint32_t load_value;
    uint32_t cmp_value;
    uint32_t clk_frac;
}epit_config_t;

/* EPIT 中断注册函数*/
#define REGISTER_EPIT_IRQ_HANDLER_FUNC(epit_num, table) \
{   \
    table[epit_num - 1] = epit##epit_num##_irq_handler; \
}

extern void epit_init(EPIT_Type *ptr, epit_config_t *conf);
extern void clear_epit_interrupt_flag(EPIT_Type *ptr);
extern void epit_disable(EPIT_Type *ptr);
extern void epit_restart(epit_config_t *conf, EPIT_Type *ptr);
extern void epit_enable(EPIT_Type *ptr);
#endif // !__EPIT_H_
