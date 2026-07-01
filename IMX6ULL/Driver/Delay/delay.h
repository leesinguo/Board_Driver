#ifndef __DELAY_H_
#define __DELAY_H_

#include "type.h"
#include "MCIMX6Y2.h"

#define GPT_NUM 3
#define COMPARE_EVENT_OCCURRED      1
#define COMPARE_EVENT_NO_OCCURRED   0

typedef enum {
    GPT_1 = 0, 
    GPT_2,
}gpt_num_t;

typedef struct {
    uint32_t count;
    uint32_t divide;
    GPT_Type *ptr;
}gpt_parms_t;


/* GPT 中断注册函数*/
#define REGISTER_GPT_IRQ_HANDLER_FUNC(gpt_num, table) \
{   \
    table[gpt_num - 1] = gpt##gpt_num##_irq_handler; \
}

extern void delay_us(uint32_t value);
extern void delay_ms(uint32_t value);
extern void delay_s(uint32_t value);
extern void delay_init(void);

#endif // !__DELAY_H_