#include "led.h"
#include "delay.h"

u8 _led_state;
u8 _led_r,_led_g,_led_b;
u32 led_patterns[3];
u32 led_backup[3];
s8 led_phase;
u8 _led_shutdown;

void ledSetOut(void)
{
	if(_led_state)
	{
		LED_R=1;
		LED_G=1;
		LED_B=1;
	}
	else
	{
		LED_R=_led_r;
		LED_G=_led_g;
		LED_B=_led_b;
	}
}

void LEDInit(void)
{
	gpio_init_type gpio_init_struct;
    
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_init_struct);	
	gpio_bits_reset(GPIOC, LED_R_PIN | LED_G_PIN | LED_B_PIN);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = LED_R_PIN | LED_G_PIN | LED_B_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOC, &gpio_init_struct);
	
	_led_state=0;
	_led_r=1;
	_led_g=1;
	_led_b=1;
	
	ledSetOut();
	
	led_patterns[0]=0;
	led_patterns[1]=0;
	led_patterns[2]=0;
	
	led_backup[0]=0;
	led_backup[1]=0;
	led_backup[2]=0;
	
	led_phase=0;	
	_led_shutdown=0;
}

void LEDSet(u8 v)
{
	if(v)
	{
		_led_state=0;		
	}
	else
	{
		_led_state=1;		
	}
	ledSetOut();
}

void LEDFlip(void)
{
	_led_state^=1;
	ledSetOut();
}

void LEDFlash(u8 t)
{
	u8 tmp=_led_state;
	if(_led_shutdown)
		return;	
	_led_state=1;	
	ledSetOut();
	delay_ms(LED_FLASH_T);	
	while(t--)
	{
		_led_state=0;
		ledSetOut();
		delay_ms(LED_FLASH_T);	
		_led_state=1;
		ledSetOut();
		delay_ms(LED_FLASH_T);		
	}
	_led_state=1;
	ledSetOut();
	delay_ms(LED_FLASH_T);	
	_led_state=tmp;
	ledSetOut();
}


void LEDSetPattern(u32 r,u32 g,u32 b)
{
	led_patterns[0]=r;
	led_patterns[1]=g;
	led_patterns[2]=b;
	led_backup[0]=r;
	led_backup[1]=g;
	led_backup[2]=b;
	led_phase=20;
}

void LEDUpdate(void)
{
	if(_led_shutdown)
		return;
	LED_R=(led_backup[0]&0x00000001);
	LED_G=(led_backup[1]&0x00000001);
	LED_B=(led_backup[2]&0x00000001);
	led_backup[0]>>=1;
	led_backup[1]>>=1;
	led_backup[2]>>=1;
	led_phase--;
	if(!led_phase)
	{
		led_backup[0]=led_patterns[0];
		led_backup[1]=led_patterns[1];
		led_backup[2]=led_patterns[2];
		led_phase=20;
	}
}

void LEDShutdown(void)
{
	_led_shutdown=1;
	LED_R=1;
	LED_G=1;
	LED_B=1;
}

void LEDRestore(void)
{
	_led_shutdown=0;
	ledSetOut();
	LEDUpdate();
}

void LEDSetRGB(u8 r,u8 g,u8 b)
{
	_led_r=r;
	_led_g=g;
	_led_b=b;
}
