#include "LED.h"
#include "Clock.h"
#include "delay.h"
#include "gpio.h"
#include "Interrupt.h"
#include "MCIMX6Y2.h"
#include "uart.h"

int main(void)
{
    uint8_t led_state = 0;

    imx_interrupt_init();    
    system_clock_init_528mhz();
    device_clock_enable();
    led_init();
    delay_init();
    uart1_init_115200();

    while(1){
        led_state = !led_state;
        led_switch(LED1, led_state);
        debug_log(DLOG_INFO, "LED state %d", led_state);
        delay_ms(2000);
    }
    return 0;
}
