#include "timer.h"

void MainClockInit(void)
{
	crm_periph_clock_enable(CRM_TMR9_PERIPH_CLOCK, TRUE);
	tmr_base_init(TMR9, 9, 287);//100k
    tmr_cnt_dir_set(TMR9, TMR_COUNT_UP);
    tmr_clock_source_div_set(TMR9, TMR_CLOCK_DIV1);
    tmr_period_buffer_enable(TMR9, FALSE);
	
	nvic_irq_enable(TMR1_BRK_TMR9_IRQn,0,0);
	
	tmr_interrupt_enable(TMR9,TMR_OVF_INT,TRUE);
	
    tmr_counter_enable(TMR9, TRUE);	
}
