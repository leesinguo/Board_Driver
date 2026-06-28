#include "type.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "core_ca7.h"
#include "Interrupt.h"
#include "gpio.h"

/* gpio1中断处理函数表 */
LOCAL system_irq_handler_func g_gpio1_irq_handler_table[GPIOX_IRQ_TABLE_SIZE] = {0};

/* GPIO1 各pin的默认中断处理函数（weak空实现，用户可在测试代码中覆盖） */
__attribute__((weak)) void gpio1_0_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_1_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_2_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_3_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_4_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_5_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_6_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_7_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_8_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_9_irq_handler(uint32_t gicciarr_num, void *param)  {}
__attribute__((weak)) void gpio1_10_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_11_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_12_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_13_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_14_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_15_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_16_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_17_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_18_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_19_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_20_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_21_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_22_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_23_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_24_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_25_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_26_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_27_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_28_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_29_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_30_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpio1_31_irq_handler(uint32_t gicciarr_num, void *param) {}

LOCAL system_irq_handler_func get_gpio1_irq_handler(uint32_t pin)
{
    return g_gpio1_irq_handler_table[pin];
}

/* 初始化gpio1中断处理函数表 */
LOCAL void init_gpio1_irq_handler_table()
{
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 0,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 1,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 2,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 3,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 4,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 5,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 6,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 7,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 8,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 9,  g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 10, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 11, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 12, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 13, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 14, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 15, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 16, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 17, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 18, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 19, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 20, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 21, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 22, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 23, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 24, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 25, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 26, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 27, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 28, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 29, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 30, g_gpio1_irq_handler_table);
    REGISTER_GPIOx_IRQ_HANDLER_FUNC(1, 31, g_gpio1_irq_handler_table);
}

/* 控制GPIO高低电平 */
void gpio_pin_write(GPIO_Type *const base, const uint32_t pin, const uint8_t value)
{
    if (value == GPIO_LOW) {
        base->DR &= ~GPIO_HIGH(pin);
    } else {
        base->DR |= GPIO_HIGH(pin);
    }
}

/* 获取GPIO pin值*/
uint8_t gpio_pin_read(const GPIO_Type *base, const uint32_t pin)
{
    uint32_t value;

    value = base->DR;
    value &= GPIO_HIGH(pin);

    return !!value;
}

/* GPIO初始化 */
void gpio_init(GPIO_Type *const base, const uint32_t pin, const gpio_pin_config_t *config)
{
    /* 0 -> input 1 -> output*/
    if (config->dir == KGPIO_INPUT) {
        base->GDIR &= ~GPIO_HIGH(pin);
    } else {
        base->GDIR |= GPIO_HIGH(pin);
        /* 设置默认输出电平 */
        gpio_pin_write(base, pin, config->output_logic);
    }    
}

/* gpio中断初始化 */
void gpio_interrupt_init(GPIO_Type *const base, const uint32_t pin, const gpio_pin_config_t *config)
{
    init_gpio1_irq_handler_table();
    config_gpio_interrupt(base, config, pin);
}

void gpio_interrupt_enable(GPIO_Type *ptr, uint32_t pin)
{
    SET_REG_BIT(ptr->IMR, pin);
}

void gpio_interrupt_disable(GPIO_Type *ptr, uint32_t pin)
{
    CLR_REG_BIT(ptr->IMR, pin);
}

void clear_gpio_interrupt_flag(GPIO_Type *ptr, uint32_t pin)
{
    SET_REG_BIT(ptr->ISR, pin);
}

void config_gpio_interrupt(GPIO_Type *gpio_ptr, const gpio_pin_config_t *conf, uint32_t pin)
{
    static gpio_interrupt_params_t inter_parmars = {0};

    if (pin <= GPIOx_IO15) {
        /* 清除指定位域 */
        SET_REG_FIELD(gpio_ptr->ICR1, 2 * pin + 1, 2 * pin, 0x00);
        if (conf->trigger_type == ALL_EDGE_TRIGGER) {
            SET_REG_BIT(gpio_ptr->EDGE_SEL, pin);
        } else {
            /* 设置触发方式 */
            SET_REG_FIELD(gpio_ptr->ICR1, 2 * pin + 1, 2 * pin, conf->trigger_type);
        }
    } else {
        /* 清除指定位域 */
        SET_REG_FIELD(gpio_ptr->ICR2, (pin - 16) * 2 + 1, (pin - 16) * 2, 0x00);
        if (conf->trigger_type == ALL_EDGE_TRIGGER) {
            SET_REG_BIT(gpio_ptr->EDGE_SEL, pin);
        } else {
            /* 设置触发方式 */
            SET_REG_FIELD(gpio_ptr->ICR2, (pin - 16) * 2 + 1, (pin - 16) * 2, conf->trigger_type);
        }
    }
    
    /* 使能GIC中断控制器 */
    GIC_EnableIRQ(conf->irq_num);
    inter_parmars.ptr = gpio_ptr;
    inter_parmars.pin_num = pin;
    
    /* 注册中断处理函数 */
    system_register_irq_handler(conf->irq_num, get_gpio1_irq_handler(pin), &inter_parmars);

    /* 开启对应中断 */
    gpio_interrupt_enable(gpio_ptr, pin);
}