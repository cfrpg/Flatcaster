#include "touch.h"
#include "string.h"

TouchState touch;

void touch_gpio_init(void)
{
	gpio_init_type gpio_init_struct;
	gpio_default_para_init(&gpio_init_struct);
	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	
	// Driver IO
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = DRV_C5_PIN | DRV_C4_PIN | DRV_C3_PIN | DRV_C2_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOC, &gpio_init_struct);
	
	gpio_init_struct.gpio_pins = DRV_C6_PIN;
	gpio_init(GPIOB, &gpio_init_struct);
	
	gpio_init_struct.gpio_pins = DRV_C1_PIN;
	gpio_init(GPIOA, &gpio_init_struct);

	// timer IO default
	gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE9, GPIO_MUX_1);
	gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE10, GPIO_MUX_1);
	gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE11, GPIO_MUX_1);
	
	gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_2);
	gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE7, GPIO_MUX_2);
	gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE8, GPIO_MUX_2);
	gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE9, GPIO_MUX_2);
	
	
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_pins = FRET_0_PIN | FRET_1_PIN | FRET_2_PIN;
	gpio_init(GPIOA, &gpio_init_struct);
	gpio_init_struct.gpio_pins = FRET_3_PIN | FRET_4_PIN | FRET_5_PIN | FRET_6_PIN;
	gpio_init(GPIOB, &gpio_init_struct);	
}

void touch_timer_init(void)
{
	tmr_input_config_type  tmr_input_struct;
	
	crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_TMR4_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
	
	// timer 1
	/* configure counter settings */
	tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);
	tmr_clock_source_div_set(TMR1, TMR_CLOCK_DIV1);
	tmr_period_buffer_enable(TMR1, FALSE);
	tmr_repetition_counter_set(TMR1, 0);	
	tmr_one_cycle_mode_enable(TMR1,TRUE);
	tmr_base_init(TMR1, 2880-1, 10-1);	//100us
	
	
	/* configure primary mode settings */
	tmr_primary_mode_select(TMR1, TMR_PRIMARY_SEL_ENABLE);
	tmr_sub_sync_mode_set(TMR1, TRUE);
	
	/* configure channel input settings */	
	tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
	tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
	tmr_input_struct.input_filter_value = 0;
	
	tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_2;
	tmr_input_channel_init(TMR1, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);
	tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_3;
	tmr_input_channel_init(TMR1, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);
	tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_4;
	tmr_input_channel_init(TMR1, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);
	
	//timer 4
	tmr_cnt_dir_set(TMR4, TMR_COUNT_UP);
	tmr_clock_source_div_set(TMR4, TMR_CLOCK_DIV1);
	tmr_period_buffer_enable(TMR4, FALSE);
	tmr_one_cycle_mode_enable(TMR4,TRUE);
	tmr_base_init(TMR4, 2880-1-1, 10-1);	//100us	
	
	/* configure primary mode settings */
	tmr_sub_sync_mode_set(TMR4, TRUE);
	tmr_sub_mode_select(TMR4, TMR_SUB_TRIGGER_MODE);

	/* configure sub-mode input */
	tmr_trigger_input_select(TMR4, TMR_SUB_INPUT_SEL_IS0);
	
	 /* configure channel input settings */
	tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
	tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
	tmr_input_struct.input_filter_value = 0;
	tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_1;
	tmr_input_channel_init(TMR4, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);
	tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_2;
	tmr_input_channel_init(TMR4, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);
	tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_3;
	tmr_input_channel_init(TMR4, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);
	tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_4;
	tmr_input_channel_init(TMR4, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);
	
	//timer 2 for discharge
	tmr_cnt_dir_set(TMR2, TMR_COUNT_UP);
	tmr_clock_source_div_set(TMR2, TMR_CLOCK_DIV1);
	tmr_period_buffer_enable(TMR2, FALSE);
	tmr_one_cycle_mode_enable(TMR2,TRUE);
	tmr_base_init(TMR2, 28800-1, 9-1);	//100us
	
	
	
	tmr_flag_clear(TMR2,TMR_OVF_FLAG);
	
	nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 0, 1);	
	nvic_irq_enable(TMR2_GLOBAL_IRQn, 0, 1);	
//	nvic_irq_enable(TMR4_GLOBAL_IRQn, 1, 1);	
	
	tmr_interrupt_enable(TMR1,TMR_OVF_INT,TRUE);
//	tmr_interrupt_enable(TMR4,TMR_OVF_INT,TRUE);
	tmr_interrupt_enable(TMR2,TMR_OVF_INT,TRUE);
	
	
}




void touch_start_discharge(void)
{
	u32 tmp;
	// set fert to out mode
	tmp =GPIOA->cfgr;
	tmp &= ~FERT_0_2_MASK;
	tmp |= FERT_0_2_MODE_OUT;
	GPIOA->cfgr=tmp;
	
	tmp =GPIOB->cfgr;
	tmp &= ~FERT_3_6_MASK;
	tmp |= FERT_3_6_MODE_OUT;
	GPIOB->cfgr=tmp;
	
	FERT_0_OUT=0;
	FERT_1_OUT=0;
	FERT_2_OUT=0;
	FERT_3_OUT=0;
	FERT_4_OUT=0;
	FERT_5_OUT=0;
}

void touch_stop_discharge(void)
{
	FERT_0_OUT=1;
	FERT_1_OUT=1;
	FERT_2_OUT=1;
	FERT_3_OUT=1;
	FERT_4_OUT=1;
	FERT_5_OUT=1;
	
	u32 tmp;
	// set fert to AF mode
	tmp =GPIOA->cfgr;
	tmp &= ~FERT_0_2_MASK;
	tmp |= FERT_0_2_MODE_AF;
	GPIOA->cfgr=tmp;
	
	tmp =GPIOB->cfgr;
	tmp &= ~FERT_3_6_MASK;
	tmp |= FERT_3_6_MODE_AF;
	GPIOB->cfgr=tmp;
}

void touch_driver_on(u8 ch)
{
	switch(ch)
	{
		case 0: 
			DRV_C1=1;
			break;
		case 1: 
			DRV_C2=1;
			break;
		case 2: 
			DRV_C3=1;
			break;
		case 3: 
			DRV_C4=1;
			break;
		case 4: 
			DRV_C5=1;
			break;
		case 5: 
			DRV_C6=1;
			break;
	}
}
void touch_driver_off(u8 ch)
{
	switch(ch)
	{
		case 0: 
			DRV_C1=0;
			break;
		case 1: 
			DRV_C2=0;
			break;
		case 2: 
			DRV_C3=0;
			break;
		case 3: 
			DRV_C4=0;
			break;
		case 4: 
			DRV_C5=0;
			break;
		case 5: 
			DRV_C6=0;
			break;
	}
}

void TouchInit(void)
{
	touch.currChannel=0;
	
	touch_gpio_init();
	touch_timer_init();
	touch.lpf=50;
	touch.thd=200;
	
}

void TouchScan(void)
{
	touch_stop_discharge();
	for(u8 i=0;i<6;i++)
		touch_driver_off(i);
	touch.currChannel=0;
	touch_driver_on(0);
	tmr_counter_enable(TMR1,TRUE);
}

void TouchSetRef(void)
{
	memcpy(touch.refData,touch.rawData,sizeof(touch.rawData));	
}

void TouchGetKey(void)
{
	for(u8 i=0;i<6;i++)
	{		
		for(u8 j=0;j<7;j++)
		{
			if(touch.rawData[i][j]-touch.refData[i][j]>touch.thd)
				touch.trig[i][j]=1;
			else
			{
				touch.trig[i][j]=0;
				// auto cali
				touch.refData[i][j]=touch.refData[i][j]*touch.lpf+touch.rawData[i][j];
				touch.refData[i][j]/=(1+touch.lpf);
				
			}
		}
	}
	
	for(u8 i=0;i<6;i++)
	{
		touch.stringFert[i]=0;
		touch.stringState[i]<<=1;
		if(touch.trig[i][0])
		{			
			touch.stringState[i]|=0x01;
			
		}
		
		for(u8 j=1;j<7;j++)
		{
			if(touch.trig[i][j])
			{
				touch.stringFert[i]=j;
				break;
			}
		}
	}
}


void TMR1_OVF_TMR10_IRQHandler(void)
{	
	if(tmr_interrupt_flag_get(TMR1,TMR_OVF_FLAG)!=RESET)
	{		
		tmr_flag_clear(TMR1,TMR_OVF_FLAG);
		touch_driver_off(touch.currChannel);
		touch_start_discharge();
		u8 currch=touch.currChannel;
//		if(tmr_flag_get(TMR1,TMR_C2_FLAG)==SET)
		if(TMR1->ists_bit.c2if)
			touch.rawData[currch][0]=TMR1->c2dt;
		else			
			touch.rawData[currch][0]=99999;
		
		if(TMR1->ists_bit.c3if)
			touch.rawData[currch][1]=TMR1->c3dt;
		else			
			touch.rawData[currch][1]=99999;
		
		if(TMR1->ists_bit.c4if)
			touch.rawData[currch][2]=TMR1->c4dt;
		else			
			touch.rawData[currch][2]=99999;
		
		if(TMR4->ists_bit.c1if)
			touch.rawData[currch][3]=TMR4->c1dt;
		else			
			touch.rawData[currch][3]=99999;
		
		if(TMR4->ists_bit.c2if)
			touch.rawData[currch][4]=TMR4->c2dt;
		else			
			touch.rawData[currch][4]=99999;
		
		if(TMR4->ists_bit.c3if)
			touch.rawData[currch][5]=TMR4->c3dt;
		else			
			touch.rawData[currch][5]=99999;
		
		if(TMR4->ists_bit.c4if)
			touch.rawData[currch][6]=TMR4->c4dt;
		else			
			touch.rawData[currch][6]=99999;
		
//		touch.rawData[currch][0]=TMR1->c2dt;
//		touch.rawData[currch][1]=TMR1->c3dt;
//		touch.rawData[currch][2]=TMR1->c4dt;
//		touch.rawData[currch][3]=TMR4->c1dt;
//		touch.rawData[currch][4]=TMR4->c2dt;
//		touch.rawData[currch][5]=TMR4->c3dt;		
//		touch.rawData[currch][6]=TMR4->c4dt;
		tmr_counter_enable(TMR2,TRUE);
	}
}
void TMR4_GLOBAL_IRQHandler(void)
{
	if(tmr_interrupt_flag_get(TMR4,TMR_OVF_FLAG)!=RESET)
	{
//		touch_stop_discharge();
		tmr_counter_enable(TMR4,FALSE);		
		tmr_flag_clear(TMR4,TMR_OVF_FLAG);		
	}
}
void TMR2_GLOBAL_IRQHandler(void)
{
	if(tmr_interrupt_flag_get(TMR2,TMR_OVF_FLAG)!=RESET)
	{
		tmr_flag_clear(TMR2,TMR_OVF_FLAG);		
		touch_stop_discharge();
//		tmr_counter_enable(TMR7,FALSE);	
		touch.currChannel++;
		if(touch.currChannel>=6)
			touch.currChannel=0;
		touch_driver_on(touch.currChannel);
		tmr_counter_enable(TMR1,TRUE);
		
		
	}
}

