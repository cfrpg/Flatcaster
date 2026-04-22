#include "delay.h"

u32 _delay_fac_us,_delay_fac_ms;

void DelayInit(u32 clk)
{
	systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_DIV8);
	_delay_fac_us=clk/8;
	_delay_fac_ms=_delay_fac_us*1000;	
}

void delay_us(u32 us)
{
	u32 t;
	SysTick->LOAD=(u32)(us*_delay_fac_us);
	SysTick->VAL=0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	do
	{
		t=SysTick->CTRL;
	}while((t&0x01) && !(t&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; 
	SysTick->VAL =0x00;
}

void delay_xms(u32 ms)
{
	u32 t;
	SysTick->LOAD=(u32)(ms*_delay_fac_ms);
	SysTick->VAL=0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	do
	{
		t=SysTick->CTRL;
	}while((t&0x01) && !(t&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; 
	SysTick->VAL =0x00;
}

void delay_ms(u32 ms)
{
	u32 cnt=ms/400;
	u32 rem=ms%400;
	while(cnt)
	{
		delay_xms(400);
		cnt--;
	}
	if(rem)
		delay_xms(rem);
}
