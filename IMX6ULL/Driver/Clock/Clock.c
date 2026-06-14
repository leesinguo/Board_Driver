#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "type.h"
#include "Clock.h"

/* 设置PLL2 4路PFD时钟 */
LOCAL void pll2_pfd_clock_init(void)
{
    uint32_t reg;
    reg = CCM_ANALOG->PFD_528;
	reg &= ~(0X3F3F3F3F);		/* 清除原来的设置 						*/
	reg |= 32<<24;				/* PLL2_PFD3=528*18/32=297Mhz 	*/
	reg |= 24<<16;				/* PLL2_PFD2=528*18/24=396Mhz(DDR使用的时钟，最大400Mhz) */
	reg |= 16<<8;				/* PLL2_PFD1=528*18/16=594Mhz 	*/
	reg |= 27<<0;				/* PLL2_PFD0=528*18/27=352Mhz  	*/
	CCM_ANALOG->PFD_528=reg;	/* 设置PLL2_PFD0~3 */
}

/* 设置PLL3 4路PFD时钟 */
LOCAL void pll3_pfd_clock_init(void)
{
    uint32_t reg;
	reg = 0;					/* 清零   */
	reg = CCM_ANALOG->PFD_480;
	reg &= ~(0X3F3F3F3F);		/* 清除原来的设置 							*/
	reg |= 19<<24;				/* PLL3_PFD3=480*18/19=454.74Mhz 	*/
	reg |= 17<<16;				/* PLL3_PFD2=480*18/17=508.24Mhz 	*/
	reg |= 16<<8;				/* PLL3_PFD1=480*18/16=540Mhz		*/
	reg |= 12<<0;				/* PLL3_PFD0=480*18/12=720Mhz	 	*/
	CCM_ANALOG->PFD_480=reg;	/* 设置PLL3_PFD0~3 					*/	
}

LOCAL void ahb_clk_root_init(void)
{
    /* 设置时钟源 */
    SET_REG_FIELD(CCM->CBCMR, BIT19, BIT18, 0x1); /* 选择pll2_pfd2 */
    while (GET_REG_BIT(CCM->CDHIPR, BIT5) == DIVIDER_BUSY) {
        /* 判断是否空闲 */
    }
    CLR_REG_BIT(CCM->CBCDR, BIT25); /* 选择PLL2时钟源 */
    while (GET_REG_BIT(CCM->CDHIPR, BIT5) == DIVIDER_BUSY) {
        /* 等到握手信号完成 */
    }

    while (GET_REG_BIT(CCM->CDHIPR, BIT1) == DIVIDER_BUSY) {
        /* 判断是否空闲 */
    }
    SET_REG_FIELD(CCM->CBCDR, BIT12, BIT10, 0x2); /* 设置AHB分频系数为4，AHB根时钟 = 396MHZ/3 = 132MHZ */
    while (GET_REG_BIT(CCM->CDHIPR, BIT1) == DIVIDER_BUSY) {
        /* 等到握手信号完成 */
    }
}

LOCAL void ipg_clk_root_init(void)
{
    /* 设置分频系数 */
    SET_REG_FIELD(CCM->CBCDR, BIT9, BIT8, 0x1); /* 分频系数2 132MHZ/2 = 66MHZ */
}

LOCAL void perclk_clk_root_init(void)
{
    /* 选择时钟源 */
    CLR_REG_BIT(CCM->CSCMR1, BIT6); 
    /* 设置分频系数 */
    SET_REG_FIELD(CCM->CSCMR1, BIT5, BIT0, 0x0); /* 分频系数1 66MHZ/1 = 66MHZ */
}

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

    /* 清除BYPASS位 
     * 0 -> 走PLL琐相环，也就是设置的倍频时钟
     * 1 -> 跳过琐相环，输出直接等于24MHZ的晶振
     */
    CLR_REG_BIT(CCM_ANALOG->PLL_ARM, BIT16);
    /* 设置PLL1_Clk = 1056MHZ */
    SET_REG_FIELD(CCM_ANALOG->PLL_ARM, BIT6, BIT0, 0x58);
    /* 打开时钟 */
    SET_REG_BIT(CCM_ANALOG->PLL_ARM, BIT13);
    /* 设置分频系数 /2*/
    SET_REG_FIELD(CCM->CACRR, BIT2, BIT0, 0x1);
    /*切换到主时钟ppl_clk*/
    CLR_REG_BIT(CCM->CCSR, BIT2);
    pll2_pfd_clock_init();
    pll3_pfd_clock_init();
    ahb_clk_root_init();
    ipg_clk_root_init();
    perclk_clk_root_init();
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
    /* 清除BYPASS位 
     * 0 -> 走PLL琐相环，也就是设置的倍频时钟
     * 1 -> 跳过琐相环，输出直接等于24MHZ的晶振
     */
    CLR_REG_BIT(CCM_ANALOG->PLL_ARM, BIT16);
    /* 设置PLL1_Clk = 1056MHZ */
    SET_REG_FIELD(CCM_ANALOG->PLL_ARM, BIT6, BIT0, 0x3A);
    /* 打开时钟 */
    SET_REG_BIT(CCM_ANALOG->PLL_ARM, BIT13);
    /* 设置分频系数 /1*/
    SET_REG_FIELD(CCM->CACRR, BIT2, BIT0, 0x0);
    /*切换到主时钟ppl_clk*/
    CLR_REG_BIT(CCM->CCSR, BIT2);
    pll2_pfd_clock_init();
    pll3_pfd_clock_init();
    ahb_clk_root_init();
    ipg_clk_root_init();
    perclk_clk_root_init();
}