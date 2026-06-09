#include "Beep.h"

int main(void)
{
    beep_init();

    /* 打开蜂鸣器 */
    beep_switch(1);

    while (1);

    return 0;
}
