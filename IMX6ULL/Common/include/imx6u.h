#ifndef __IMX6U_H_
#define __IMX6U_H_

#include "type.h"

/* 
 * 外设寄存器组的基地址 
 */
#define CCM_BASE					(0X020C4000)
#define CCM_ANALOG_BASE				(0X020C8000)
#define IOMUX_SW_MUX_BASE			(0X020E0044)
#define IOMUX_SW_PAD_BASE			(0X020E0204)
#define GPIO1_BASE                  (0x0209C000)
#define GPIO2_BASE                  (0x020A0000)
#define GPIO3_BASE                  (0x020A4000)
#define GPIO4_BASE                  (0x020A8000)
#define GPIO5_BASE                  (0x020AC000)

/* 
 * CCM寄存器结构体定义，分为CCM和CCM_ANALOG 
 */
typedef struct 
{
	volatile uint32_t CCR;
	volatile uint32_t CCDR;
	volatile uint32_t CSR;
	volatile uint32_t CCSR;
	volatile uint32_t CACRR;
	volatile uint32_t CBCDR;
	volatile uint32_t CBCMR;
	volatile uint32_t CSCMR1;
	volatile uint32_t CSCMR2;
	volatile uint32_t CSCDR1;
	volatile uint32_t CS1CDR;
	volatile uint32_t CS2CDR;
	volatile uint32_t CDCDR;
	volatile uint32_t CHSCCDR;
	volatile uint32_t CSCDR2;
	volatile uint32_t CSCDR3;	
	volatile uint32_t RESERVED_1[2];
	volatile uint32_t CDHIPR;  
	volatile uint32_t RESERVED_2[2];
	volatile uint32_t CLPCR;
	volatile uint32_t CISR;
	volatile uint32_t CIMR;
	volatile uint32_t CCOSR;
	volatile uint32_t CGPR;
	volatile uint32_t CCGR0;
	volatile uint32_t CCGR1;
	volatile uint32_t CCGR2;
	volatile uint32_t CCGR3;
	volatile uint32_t CCGR4;
	volatile uint32_t CCGR5;
	volatile uint32_t CCGR6;
	volatile uint32_t RESERVED_3[1];
	volatile uint32_t CMEOR;	
} CCM_Type; 

typedef struct 
{
	volatile uint32_t PLL_ARM;
	volatile uint32_t PLL_ARM_SET;
	volatile uint32_t PLL_ARM_CLR;
	volatile uint32_t PLL_ARM_TOG;
	volatile uint32_t PLL_USB1;
	volatile uint32_t PLL_USB1_SET;
	volatile uint32_t PLL_USB1_CLR;
	volatile uint32_t PLL_USB1_TOG;
	volatile uint32_t PLL_USB2;
	volatile uint32_t PLL_USB2_SET;
	volatile uint32_t PLL_USB2_CLR;
	volatile uint32_t PLL_USB2_TOG;
	volatile uint32_t PLL_SYS;
	volatile uint32_t PLL_SYS_SET;
	volatile uint32_t PLL_SYS_CLR;
	volatile uint32_t PLL_SYS_TOG;
	volatile uint32_t PLL_SYS_SS;
	volatile uint32_t RESERVED_1[3];
	volatile uint32_t PLL_SYS_NUM;
	volatile uint32_t RESERVED_2[3];
	volatile uint32_t PLL_SYS_DENOM; 
	volatile uint32_t RESERVED_3[3];
	volatile uint32_t PLL_AUDIO;
	volatile uint32_t PLL_AUDIO_SET;
	volatile uint32_t PLL_AUDIO_CLR;
	volatile uint32_t PLL_AUDIO_TOG;
	volatile uint32_t PLL_AUDIO_DENOM;
	volatile uint32_t RESERVED_4[3];
	volatile uint32_t PLL_VIDEO;
	volatile uint32_t PLL_VIDEO_SET;
	volatile uint32_t PLL_VIDEO_CLR;
	volatile uint32_t PLL_VIDEO_TOG;
	volatile uint32_t PLL_VIDEO_NUM;
	volatile uint32_t RESERVED_5[3];
	volatile uint32_t PLL_VIDEO_DENOM;
	volatile uint32_t RESERVED_6[7];
	volatile uint32_t PLL_ENET;
	volatile uint32_t PLL_ENET_SET;
	volatile uint32_t PLL_ENET_CLR;
	volatile uint32_t PLL_ENET_TOG;
	volatile uint32_t PFD_480;
	volatile uint32_t PFD_480_SET;
	volatile uint32_t PFD_480_CLR;
	volatile uint32_t PFD_480_TOG;
	volatile uint32_t PFD_528;
	volatile uint32_t PFD_528_SET;
	volatile uint32_t PFD_528_CLR;
	volatile uint32_t PFD_528_TOG;
	volatile uint32_t RESERVED_7[16];
	volatile uint32_t MISC0;
	volatile uint32_t MISC0_SET;
	volatile uint32_t MISC0_CLR;
	volatile uint32_t MISC0_TOG;
	volatile uint32_t MISC1;
	volatile uint32_t MISC1_SET;
	volatile uint32_t MISC1_CLR;
	volatile uint32_t MISC1_TOG;
	volatile uint32_t MISC2;
	volatile uint32_t MISC2_SET;
	volatile uint32_t MISC2_CLR;
	volatile uint32_t MISC2_TOG;
} CCM_ANALOG_Type; 

/* 
 * IOMUX寄存器组
 */
typedef struct 
{
	volatile uint32_t JTAG_MOD;
	volatile uint32_t JTAG_TMS;
	volatile uint32_t JTAG_TDO;
	volatile uint32_t JTAG_TDI;
	volatile uint32_t JTAG_TCK;
	volatile uint32_t JTAG_TRST_B;
	volatile uint32_t GPIO1_IO00;
	volatile uint32_t GPIO1_IO01;
	volatile uint32_t GPIO1_IO02;
	volatile uint32_t GPIO1_IO03;
	volatile uint32_t GPIO1_IO04;
	volatile uint32_t GPIO1_IO05;
	volatile uint32_t GPIO1_IO06;
	volatile uint32_t GPIO1_IO07;
	volatile uint32_t GPIO1_IO08;
	volatile uint32_t GPIO1_IO09;
	volatile uint32_t UART1_TX_DATA;
	volatile uint32_t UART1_RX_DATA;
	volatile uint32_t UART1_CTS_B;
	volatile uint32_t UART1_RTS_B;
	volatile uint32_t UART2_TX_DATA;
	volatile uint32_t UART2_RX_DATA;
	volatile uint32_t UART2_CTS_B;
	volatile uint32_t UART2_RTS_B;
	volatile uint32_t UART3_TX_DATA;
	volatile uint32_t UART3_RX_DATA;
	volatile uint32_t UART3_CTS_B;
	volatile uint32_t UART3_RTS_B;
	volatile uint32_t UART4_TX_DATA;
	volatile uint32_t UART4_RX_DATA;
	volatile uint32_t UART5_TX_DATA;
	volatile uint32_t UART5_RX_DATA;
	volatile uint32_t ENET1_RX_DATA0;
	volatile uint32_t ENET1_RX_DATA1;
	volatile uint32_t ENET1_RX_EN;
	volatile uint32_t ENET1_TX_DATA0;
	volatile uint32_t ENET1_TX_DATA1;
	volatile uint32_t ENET1_TX_EN;
	volatile uint32_t ENET1_TX_CLK;
	volatile uint32_t ENET1_RX_ER;
	volatile uint32_t ENET2_RX_DATA0;
	volatile uint32_t ENET2_RX_DATA1;
	volatile uint32_t ENET2_RX_EN;
	volatile uint32_t ENET2_TX_DATA0;
	volatile uint32_t ENET2_TX_DATA1;
	volatile uint32_t ENET2_TX_EN;
	volatile uint32_t ENET2_TX_CLK;
	volatile uint32_t ENET2_RX_ER;
	volatile uint32_t LCD_CLK;
	volatile uint32_t LCD_ENABLE;
	volatile uint32_t LCD_HSYNC;
	volatile uint32_t LCD_VSYNC;
	volatile uint32_t LCD_RESET;
	volatile uint32_t LCD_DATA00;
	volatile uint32_t LCD_DATA01;
	volatile uint32_t LCD_DATA02;
	volatile uint32_t LCD_DATA03;
	volatile uint32_t LCD_DATA04;
	volatile uint32_t LCD_DATA05;
	volatile uint32_t LCD_DATA06;
	volatile uint32_t LCD_DATA07;
	volatile uint32_t LCD_DATA08;
	volatile uint32_t LCD_DATA09;
	volatile uint32_t LCD_DATA10;
	volatile uint32_t LCD_DATA11;
	volatile uint32_t LCD_DATA12;
	volatile uint32_t LCD_DATA13;
	volatile uint32_t LCD_DATA14;
	volatile uint32_t LCD_DATA15;
	volatile uint32_t LCD_DATA16;
	volatile uint32_t LCD_DATA17;
	volatile uint32_t LCD_DATA18;
	volatile uint32_t LCD_DATA19;
	volatile uint32_t LCD_DATA20;
	volatile uint32_t LCD_DATA21;
	volatile uint32_t LCD_DATA22;
	volatile uint32_t LCD_DATA23;
	volatile uint32_t NAND_RE_B;
	volatile uint32_t NAND_WE_B;
	volatile uint32_t NAND_DATA00;
	volatile uint32_t NAND_DATA01;
	volatile uint32_t NAND_DATA02;
	volatile uint32_t NAND_DATA03;
	volatile uint32_t NAND_DATA04;
	volatile uint32_t NAND_DATA05;
	volatile uint32_t NAND_DATA06;
	volatile uint32_t NAND_DATA07;
	volatile uint32_t NAND_ALE;
	volatile uint32_t NAND_WP_B;
	volatile uint32_t NAND_READY_B;
	volatile uint32_t NAND_CE0_B;
	volatile uint32_t NAND_CE1_B;
	volatile uint32_t NAND_CLE;
	volatile uint32_t NAND_DQS;
	volatile uint32_t SD1_CMD;
	volatile uint32_t SD1_CLK;
	volatile uint32_t SD1_DATA0;
	volatile uint32_t SD1_DATA1;
	volatile uint32_t SD1_DATA2;
	volatile uint32_t SD1_DATA3;
	volatile uint32_t CSI_MCLK;
	volatile uint32_t CSI_PIXCLK;
	volatile uint32_t CSI_VSYNC;
	volatile uint32_t CSI_HSYNC;
	volatile uint32_t CSI_DATA00;
	volatile uint32_t CSI_DATA01;
	volatile uint32_t CSI_DATA02;
	volatile uint32_t CSI_DATA03;
	volatile uint32_t CSI_DATA04;
	volatile uint32_t CSI_DATA05;
	volatile uint32_t CSI_DATA06;
	volatile uint32_t CSI_DATA07;
}IOMUX_SW_MUX_Type;

typedef struct 
{
	volatile uint32_t DRAM_ADDR00;
	volatile uint32_t DRAM_ADDR01;
	volatile uint32_t DRAM_ADDR02;
	volatile uint32_t DRAM_ADDR03;
	volatile uint32_t DRAM_ADDR04;
	volatile uint32_t DRAM_ADDR05;
	volatile uint32_t DRAM_ADDR06;
	volatile uint32_t DRAM_ADDR07;
	volatile uint32_t DRAM_ADDR08;
	volatile uint32_t DRAM_ADDR09;
	volatile uint32_t DRAM_ADDR10;
	volatile uint32_t DRAM_ADDR11;
	volatile uint32_t DRAM_ADDR12;
	volatile uint32_t DRAM_ADDR13;
	volatile uint32_t DRAM_ADDR14;
	volatile uint32_t DRAM_ADDR15;
	volatile uint32_t DRAM_DQM0;
	volatile uint32_t DRAM_DQM1;
	volatile uint32_t DRAM_RAS_B;
	volatile uint32_t DRAM_CAS_B;
	volatile uint32_t DRAM_CS0_B;
	volatile uint32_t DRAM_CS1_B;
	volatile uint32_t DRAM_SDWE_B;
	volatile uint32_t DRAM_ODT0;
	volatile uint32_t DRAM_ODT1;
	volatile uint32_t DRAM_SDBA0;
	volatile uint32_t DRAM_SDBA1;
	volatile uint32_t DRAM_SDBA2;
	volatile uint32_t DRAM_SDCKE0;
	volatile uint32_t DRAM_SDCKE1;
	volatile uint32_t DRAM_SDCLK0_P;
	volatile uint32_t DRAM_SDQS0_P;
	volatile uint32_t DRAM_SDQS1_P;
	volatile uint32_t DRAM_RESET;
	volatile uint32_t TEST_MODE;
	volatile uint32_t POR_B;
	volatile uint32_t ONOFF;
	volatile uint32_t SNVS_PMIC_ON_REQ;
	volatile uint32_t CCM_PMIC_STBY_REQ;
	volatile uint32_t BOOT_MODE0;
	volatile uint32_t BOOT_MODE1;
	volatile uint32_t SNVS_TAMPER0;
	volatile uint32_t SNVS_TAMPER1;
	volatile uint32_t SNVS_TAMPER2;
	volatile uint32_t SNVS_TAMPER3;
	volatile uint32_t SNVS_TAMPER4;
	volatile uint32_t SNVS_TAMPER5;
	volatile uint32_t SNVS_TAMPER6;
	volatile uint32_t SNVS_TAMPER7;
	volatile uint32_t SNVS_TAMPER8;
	volatile uint32_t SNVS_TAMPER9;
	volatile uint32_t JTAG_MOD;
	volatile uint32_t JTAG_TMS;
	volatile uint32_t JTAG_TDO;
	volatile uint32_t JTAG_TDI;
	volatile uint32_t JTAG_TCK;
	volatile uint32_t JTAG_TRST_B;
	volatile uint32_t GPIO1_IO00;
	volatile uint32_t GPIO1_IO01;
	volatile uint32_t GPIO1_IO02;
	volatile uint32_t GPIO1_IO03;
	volatile uint32_t GPIO1_IO04;
	volatile uint32_t GPIO1_IO05;
	volatile uint32_t GPIO1_IO06;
	volatile uint32_t GPIO1_IO07;
	volatile uint32_t GPIO1_IO08;
	volatile uint32_t GPIO1_IO09;
	volatile uint32_t UART1_TX_DATA;
	volatile uint32_t UART1_RX_DATA;
	volatile uint32_t UART1_CTS_B;
	volatile uint32_t UART1_RTS_B;
	volatile uint32_t UART2_TX_DATA;
	volatile uint32_t UART2_RX_DATA;
	volatile uint32_t UART2_CTS_B;
	volatile uint32_t UART2_RTS_B;
	volatile uint32_t UART3_TX_DATA;
	volatile uint32_t UART3_RX_DATA;
	volatile uint32_t UART3_CTS_B;
	volatile uint32_t UART3_RTS_B;
	volatile uint32_t UART4_TX_DATA;
	volatile uint32_t UART4_RX_DATA;
	volatile uint32_t UART5_TX_DATA;
	volatile uint32_t UART5_RX_DATA;
	volatile uint32_t ENET1_RX_DATA0;
	volatile uint32_t ENET1_RX_DATA1;
	volatile uint32_t ENET1_RX_EN;
	volatile uint32_t ENET1_TX_DATA0;
	volatile uint32_t ENET1_TX_DATA1;
	volatile uint32_t ENET1_TX_EN;
	volatile uint32_t ENET1_TX_CLK;
	volatile uint32_t ENET1_RX_ER;
	volatile uint32_t ENET2_RX_DATA0;
	volatile uint32_t ENET2_RX_DATA1;
	volatile uint32_t ENET2_RX_EN;
	volatile uint32_t ENET2_TX_DATA0;
	volatile uint32_t ENET2_TX_DATA1;
	volatile uint32_t ENET2_TX_EN;
	volatile uint32_t ENET2_TX_CLK;
	volatile uint32_t ENET2_RX_ER;
	volatile uint32_t LCD_CLK;
	volatile uint32_t LCD_ENABLE;
	volatile uint32_t LCD_HSYNC;
	volatile uint32_t LCD_VSYNC;
	volatile uint32_t LCD_RESET;
	volatile uint32_t LCD_DATA00;
	volatile uint32_t LCD_DATA01;
	volatile uint32_t LCD_DATA02;
	volatile uint32_t LCD_DATA03;
	volatile uint32_t LCD_DATA04;
	volatile uint32_t LCD_DATA05;
	volatile uint32_t LCD_DATA06;
	volatile uint32_t LCD_DATA07;
	volatile uint32_t LCD_DATA08;
	volatile uint32_t LCD_DATA09;
	volatile uint32_t LCD_DATA10;
	volatile uint32_t LCD_DATA11;
	volatile uint32_t LCD_DATA12;
	volatile uint32_t LCD_DATA13;
	volatile uint32_t LCD_DATA14;
	volatile uint32_t LCD_DATA15;
	volatile uint32_t LCD_DATA16;
	volatile uint32_t LCD_DATA17;
	volatile uint32_t LCD_DATA18;
	volatile uint32_t LCD_DATA19;
	volatile uint32_t LCD_DATA20;
	volatile uint32_t LCD_DATA21;
	volatile uint32_t LCD_DATA22;
	volatile uint32_t LCD_DATA23;
	volatile uint32_t NAND_RE_B;
	volatile uint32_t NAND_WE_B;
	volatile uint32_t NAND_DATA00;
	volatile uint32_t NAND_DATA01;
	volatile uint32_t NAND_DATA02;
	volatile uint32_t NAND_DATA03;
	volatile uint32_t NAND_DATA04;
	volatile uint32_t NAND_DATA05;
	volatile uint32_t NAND_DATA06;
	volatile uint32_t NAND_DATA07;
	volatile uint32_t NAND_ALE;
	volatile uint32_t NAND_WP_B;
	volatile uint32_t NAND_READY_B;
	volatile uint32_t NAND_CE0_B;
	volatile uint32_t NAND_CE1_B;
	volatile uint32_t NAND_CLE;
	volatile uint32_t NAND_DQS;
	volatile uint32_t SD1_CMD;
	volatile uint32_t SD1_CLK;
	volatile uint32_t SD1_DATA0;
	volatile uint32_t SD1_DATA1;
	volatile uint32_t SD1_DATA2;
	volatile uint32_t SD1_DATA3;
	volatile uint32_t CSI_MCLK;
	volatile uint32_t CSI_PIXCLK;
	volatile uint32_t CSI_VSYNC;
	volatile uint32_t CSI_HSYNC;
	volatile uint32_t CSI_DATA00;
	volatile uint32_t CSI_DATA01;
	volatile uint32_t CSI_DATA02;
	volatile uint32_t CSI_DATA03;
	volatile uint32_t CSI_DATA04;
	volatile uint32_t CSI_DATA05;
	volatile uint32_t CSI_DATA06;
	volatile uint32_t CSI_DATA07;
	volatile uint32_t GRP_ADDDS;
	volatile uint32_t GRP_DDRMODE_CTL;
	volatile uint32_t GRP_B0DS;
	volatile uint32_t GRP_DDRPK;
	volatile uint32_t GRP_CTLDS;
	volatile uint32_t GRP_B1DS;
	volatile uint32_t GRP_DDRHYS;
	volatile uint32_t GRP_DDRPKE;
	volatile uint32_t GRP_DDRMODE;
	volatile uint32_t GRP_DDR_TYPE;
}IOMUX_SW_PAD_Type;

/* 
 * GPIO寄存器结构体
 */
typedef struct 
{
	volatile uint32_t DR;							
	volatile uint32_t GDIR; 							
	volatile uint32_t PSR;								
	volatile uint32_t ICR1; 							
	volatile uint32_t ICR2; 							 
	volatile uint32_t IMR;								 
	volatile uint32_t ISR;			
	volatile uint32_t EDGE_SEL;  
}GPIO_Type;

/* 
 * 外设指针 
 */
#define CCM					((CCM_Type *)CCM_BASE)
#define CCM_ANALOG			((CCM_ANALOG_Type *)CCM_ANALOG_BASE)
#define IOMUX_SW_MUX		((IOMUX_SW_MUX_Type *)IOMUX_SW_MUX_BASE)
#define IOMUX_SW_PAD		((IOMUX_SW_PAD_Type *)IOMUX_SW_PAD_BASE)
#define GPIO1				((GPIO_Type *)GPIO1_BASE)
#define GPIO2				((GPIO_Type *)GPIO2_BASE)
#define GPIO3				((GPIO_Type *)GPIO3_BASE)
#define GPIO4				((GPIO_Type *)GPIO4_BASE)
#define GPIO5				((GPIO_Type *)GPIO5_BASE)

#endif //  !__IMX6U_H_

