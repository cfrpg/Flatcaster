#include "keys.h"

u32 KeyStatus[2];

void KeysInit(void)
{
	gpio_init_type gpio_init_struct;
	gpio_default_para_init(&gpio_init_struct);
	
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_14 | GPIO_PINS_15;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOC, &gpio_init_struct);
	
	KeyStatus[0]=0;
	KeyStatus[1]=0;
}

void KeysUpdate(void)
{
	KeyStatus[0]<<=1;
	KeyStatus[1]<<=1;
	if(KEY_A == 0)
		KeyStatus[0]|=1;
	if(KEY_B == 0)
		KeyStatus[1]|=1;
}
