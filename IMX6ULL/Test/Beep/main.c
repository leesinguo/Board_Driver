#include "Clock.h"
#include "Beep.h"

int main(void)
{
    device_clock_enable();
    beep_init();

    /* 打开蜂鸣器 */
    beep_switch(1);

    while (1);

    return 0;
}
