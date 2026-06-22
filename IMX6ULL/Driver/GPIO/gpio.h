#ifndef __GPIO_H_
#define __GPIO_H_

#include "type.h"
#include "MCIMX6Y2.h"

/* GPIO_DIR */
typedef enum {
    KGPIO_INPUT = 0, 
    KGPIO_OUTPUT
} gpio_pin_dir_t;
typedef enum {
    LOW_LEVEL_TRIGGER = 0,
    HIGH_LEVEL_TRIGGER = 1,
    RISING_EDGE_TRIGGER = 2,
    FALLING_EDGE_TRIGGER = 3,
    ALL_EDGE_TRIGGER = 4
}INTERRUPT_TRIGGER_TYPE;
typedef struct {
    /* data */
    gpio_pin_dir_t dir;
    uint8_t output_logic;
    INTERRUPT_TRIGGER_TYPE trigger_type;
    IRQn_Type irq_num;
} gpio_pin_config_t;

#define GPIOx_IO00      0
#define GPIOx_IO01      1
#define GPIOx_IO02      2
#define GPIOx_IO03      3
#define GPIOx_IO04      4
#define GPIOx_IO05      5
#define GPIOx_IO06      6
#define GPIOx_IO07      7
#define GPIOx_IO08      8
#define GPIOx_IO09      9
#define GPIOx_IO10      10
#define GPIOx_IO11      11
#define GPIOx_IO12      12
#define GPIOx_IO13      13
#define GPIOx_IO14      14
#define GPIOx_IO15      15
#define GPIOx_IO16      16
#define GPIOx_IO17      17
#define GPIOx_IO18      18
#define GPIOx_IO19      19
#define GPIOx_IO20      20
#define GPIOx_IO21      21
#define GPIOx_IO22      22
#define GPIOx_IO23      23
#define GPIOx_IO24      24
#define GPIOx_IO25      25
#define GPIOx_IO26      26
#define GPIOx_IO27      27
#define GPIOx_IO28      28
#define GPIOx_IO29      29
#define GPIOx_IO30      30
#define GPIOx_IO31      31

#define GPIO_LOW                    0x0             
#define GPIO_HIGH(x)                (1<<x)   /* 输出高电平的值 */
#define GPIO_PAD_VALUE_OUTPUT       0x10B0          /* 配置引脚属性（输出） */
#define GPIO_PAD_VALUE_INPUT        0xF080          /* 配置引脚属性（输入） */

/* GPIO 中断注册函数*/
#define REGISTER_GPIOx_IRQ_HANDLER_FUNC(gpio_num, pin, table) \
{   \
    table[pin] = gpio##gpio_num##_##pin##_irq_handler; \
}

extern void gpio_pin_write(GPIO_Type *const base, const uint32_t pin,  const uint8_t value);
extern void gpio_init(GPIO_Type *const base, const uint32_t pin, const gpio_pin_config_t *config);
extern uint8_t gpio_pin_read(const GPIO_Type *base, const uint32_t pin);
extern void gpio_interrupt_enable(GPIO_Type *ptr, uint32_t pin);
extern void gpio_interrupt_disable(GPIO_Type *ptr, uint32_t pin);
extern void clear_gpio_interrupt_flag(GPIO_Type *ptr, uint32_t pin);
extern void config_gpio_interrupt(GPIO_Type *gpio_ptr, const gpio_pin_config_t *conf, uint32_t pin);
extern void gpio_interrupt_init(GPIO_Type *const base, const uint32_t pin, const gpio_pin_config_t *config);
#endif // ! __GPIO_H_
