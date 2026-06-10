#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "type.h"
#include "Clock.h"

/* 使能外设时钟 */
void device_clock_enable(void)
{
    /* 使能时钟 */
    CCM->CCGR0 |= CCGRx_VALUE;
    CCM->CCGR1 |= CCGRx_VALUE;
    CCM->CCGR2 |= CCGRx_VALUE;
    CCM->CCGR3 |= CCGRx_VALUE;
    CCM->CCGR4 |= CCGRx_VALUE;
    CCM->CCGR5 |= CCGRx_VALUE;
    CCM->CCGR6 |= CCGRx_VALUE;

}

/* 初始化系统时钟528MHZ */
void system_clock_init_528mhz(void)
{
    /* 设置主频528MHZ */
    if (GET_REG_BIT(CCM->CCSR,BIT2) == 0) {
        /* 设置step_clk = osc_clk = 24MHZ */
        CLR_REG_BIT(CCM->CCSR, BIT8);

        /* 切换到备用时钟step_clk */
        SET_REG_BIT(CCM->CCSR, BIT2);
    }
    /* 设置PLL1_Clk = 1056MHZ */
    SET_REG_FIELD(CCM_ANALOG->PLL_ARM, BIT6, BIT0, 0x58);
    /* 打开时钟 */
    SET_REG_BIT(CCM_ANALOG->PLL_ARM, BIT13);
    /* 设置分频系数 /2*/
    SET_REG_FIELD(CCM->CACRR, BIT2, BIT0, 0x1);
    /*切换到主时钟ppl_clk*/
    CLR_REG_BIT(CCM->CCSR, BIT2);
}

/* 初始化系统时钟696MHZ */
void system_clock_init_696mhz(void)
{
    /* 设置主频696MHZ */
    if (GET_REG_BIT(CCM->CCSR,BIT2) == 0) {
        /* 设置step_clk = osc_clk = 24MHZ */
        CLR_REG_BIT(CCM->CCSR, BIT8);

        /* 切换到备用时钟step_clk */
        SET_REG_BIT(CCM->CCSR, BIT2);
    }
    /* 设置PLL1_Clk = 1056MHZ */
    SET_REG_FIELD(CCM_ANALOG->PLL_ARM, BIT6, BIT0, 0x3A);
    /* 打开时钟 */
    SET_REG_BIT(CCM_ANALOG->PLL_ARM, BIT13);
    /* 设置分频系数 /1*/
    SET_REG_FIELD(CCM->CACRR, BIT2, BIT0, 0x0);
    /*切换到主时钟ppl_clk*/
    CLR_REG_BIT(CCM->CCSR, BIT2);
}