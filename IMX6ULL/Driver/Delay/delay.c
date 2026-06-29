
#include "type.h"
#include "MCIMX6Y2.h"
#include "core_ca7.h"
#include "Interrupt.h"
#include "delay.h"

LOCAL system_irq_handler_func g_gpt_interrupt_handler_table[GPT_NUM] ={0};

/* gpt中断处理函数 */
__attribute__((weak)) void gpt1_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpt2_irq_handler(uint32_t gicciarr_num, void *param) {}
__attribute__((weak)) void gpt3_irq_handler(uint32_t gicciarr_num, void *param) {}

/* open gpt*/
LOCAL void open_gpt(GPT_Type *ptr)
{
	SET_REG_BIT(ptr->CR, BIT0);
}

/* close gpt */
LOCAL void close_gpt(GPT_Type *ptr)
{
	CLR_REG_BIT(ptr->CR, BIT0);
}

LOCAL void gpt_interrupt_hander_table_init()
{
	REGISTER_GPT_IRQ_HANDLER_FUNC(1, g_gpt_interrupt_handler_table);
	REGISTER_GPT_IRQ_HANDLER_FUNC(2, g_gpt_interrupt_handler_table);
	REGISTER_GPT_IRQ_HANDLER_FUNC(3, g_gpt_interrupt_handler_table);
}

system_irq_handler_func get_gpt_interrupt_hander_func(gpt_num_t num)
{
	return g_gpt_interrupt_handler_table[num];
}

/* 延时初始化函数 */
void delay_init(void)
{
	static gpt_parms_t parms = {0};
	gpt_interrupt_hander_table_init();

	/* 关闭定时器 */
	CLR_REG_BIT(GPT1->CR, BIT0);
	
	/* 软件复位 */
	SET_REG_BIT(GPT1->CR, BIT15);
	while(GET_REG_BIT(GPT1->CR, BIT15) == TRUE);
	SET_REG_BIT(GPT1->CR, BIT1);

	/* select clock resource */
	SET_REG_FIELD(GPT1->CR, BIT8, BIT6, 0x1);

	/* set mode*/
	CLR_REG_BIT(GPT1->CR, BIT9);

	/* set clock divide */
	SET_REG_FIELD(GPT1->PR, BIT11, BIT0, 65);		// 66MHZ / 66 = 1MHZ
	
	/* config output comapre channel 1 */
	SET_REG_FIELD(GPT1->OCR[0], BIT31, BIT0, 0xffffffff);	// 1ms interrupt
	
	// /*open gpt1 output comapre channel 1 interrupt*/
	// SET_REG_BIT(GPT1->IR, BIT0);

	// /* gic enable */
	// GIC_EnableIRQ(GPT1_IRQn);
	
	// /* register interrupt handler */
	// parms.count = 1000;
	// parms.divide = 65;
	// parms.ptr = GPT1;
	// system_register_irq_handler(GPT1_IRQn, get_gpt_interrupt_hander_func(GPT_1), &parms);

	/* open gpt */
	open_gpt(GPT1);
}

void delay(uint32_t value)
{
	uint32_t count_pre = GET_REG_VALUE(GPT1->CNT);
	uint32_t count_cur;
	do {
		count_cur = GET_REG_VALUE(GPT1->CNT);
	} while ((count_cur - count_pre) < value);
}
