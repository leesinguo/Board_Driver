#include "type.h"
#include "MCIMX6Y2.h"
#include "core_ca7.h"
#include "Interrupt.h"
#include "epit.h"

/* epit中断处理函数表 */
LOCAL system_irq_handler_func g_epit_irq_handler_table[EPIT_COUNT] = {0};

/* epit中断处理函数 */
__attribute__((weak)) void epit1_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void epit2_irq_handler(uint32_t gicciarr_num, void *param) {}

LOCAL void init_epit_irq_handler_table()
{
    REGISTER_EPIT_IRQ_HANDLER_FUNC(1, g_epit_irq_handler_table);
    REGISTER_EPIT_IRQ_HANDLER_FUNC(2, g_epit_irq_handler_table);
}

LOCAL system_irq_handler_func get_epit_irq_handler(uint32_t index)
{
    return g_epit_irq_handler_table[index];
}

/* 初始化epit */
void epit_init(EPIT_Type *ptr, epit_config_t *conf)
{
    /* 初始化中断函数表 */
    init_epit_irq_handler_table();   
    if (conf->clk_frac > EPIT_MAX_CLK_FRAC) {
        conf->clk_frac = EPIT_MAX_CLK_FRAC;
    }
    /* 配置epit_cr寄存器 */
    CLR_REG_BIT(ptr->CR, BIT0);
    SET_REG_BIT(ptr->CR, BIT1);
    SET_REG_BIT(ptr->CR, BIT2);
    SET_REG_BIT(ptr->CR, BIT3);
    SET_REG_FIELD(ptr->CR, BIT15, BIT4, conf->clk_frac);
    SET_REG_FIELD(ptr->CR, BIT25, BIT24, 0x1);
    
    /* 设置epit_lr寄存器 */
    SET_REG_FIELD(ptr->LR, BIT31, BIT0, conf->load_value);
    
    /* 设置epit_cmpr寄存器 */
    SET_REG_FIELD(ptr->CMPR, BIT31, BIT0, conf->cmp_value);
    
    /* 初始化中断 */
    if ((uint32_t)ptr == EPIT1_BASE) {
        GIC_EnableIRQ(EPIT1_IRQn);
        /* 注册中断处理函数 */
        system_register_irq_handler(EPIT1_IRQn, get_epit_irq_handler(0), ptr);
    } else if ((uint32_t)ptr == EPIT2_BASE) {
        GIC_EnableIRQ(EPIT2_IRQn);
        /* 注册中断处理函数 */
        system_register_irq_handler(EPIT2_IRQn, get_epit_irq_handler(1), ptr);
    }
    /* 开启定时器 */
    epit_enable(ptr);
}

/* 清除中断标志位 */
void clear_epit_interrupt_flag(EPIT_Type *ptr)
{
    SET_REG_BIT(ptr->SR, BIT0);
}

/* 关闭定时器 */
void epit_disable(EPIT_Type *ptr)
{
    CLR_REG_BIT(ptr->CR, BIT0);
}

/* 开启定时器 */
void epit_enable(EPIT_Type *ptr)
{
    SET_REG_BIT(ptr->CR, BIT0);
}

/* 重启epit定时器 */
void epit_restart(epit_config_t *conf, EPIT_Type *ptr)
{
    /* 关闭定时器 */
    epit_disable(ptr);
    SET_REG_FIELD(ptr->LR, BIT31, BIT0, conf->load_value);
    
    /* 开启定时器 */
    epit_enable(ptr);
}