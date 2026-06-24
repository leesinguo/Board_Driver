#include "Beep.h"
#include "Key.h"
#include "LED.h"
#include "Clock.h"
#include "delay.h"
#include "gpio.h"
#include "Interrupt.h"
#include "epit.h"
#include "MCIMX6Y2.h"

/* epit1中断处理函数 */
void epit1_irq_handler(uint32_t gicciarr_num, void *param)
{
    static uint8_t state = 0;
    
    if (GET_REG_BIT(((EPIT_Type*)param)->SR, BIT0) == EPIT_COMPARE_EVENT_OCCURRED) {
        state = !state;
        led_switch(LED1, state);
    }
    /* 清除中断标志位 */
    clear_epit_interrupt_flag(EPIT1);
}

int main(void)
{
    epit_config_t conf = {0};

    conf.clk_frac = 65;
    conf.cmp_value = 0;
    conf.load_value = 500000;
    conf.count_value = conf.load_value;

    imx_interrupt_init();    
    system_clock_init_696mhz();
    device_clock_enable();
    led_init();
    epit_init(EPIT1, &conf);
    while(1){

    }
    return 0;
}
