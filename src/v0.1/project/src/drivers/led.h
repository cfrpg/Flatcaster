#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED_R PCout(1)
#define LED_G PCout(0)
#define LED_B PCout(13)

#define LED_R_PIN    		GPIO_PINS_1
#define LED_R_GPIO_PORT    	GPIOC

#define LED_G_PIN    		GPIO_PINS_0
#define LED_G_GPIO_PORT    	GPIOC

#define LED_B_PIN    		GPIO_PINS_13
#define LED_B_GPIO_PORT    	GPIOC

#define LED_FLASH_T 100

#define LED_1Hz 0x0F83E0
#define LED_2Hz 0x0E739C
#define LED_5Hz 0x0AAAAA
#define LED_Half 0x0FFC00
#define LED_ON 0x000000
#define LED_OFF 0xFFFFFF
#define LED_1Hz_Double 0x0A0280

void LEDInit(void);
void LEDSet(u8 v);
void LEDFlip(void);
void LEDFlash(u8 t);
void LEDSetPattern(u32 r,u32 g,u32 b);
void LEDUpdate(void);
void LEDShutdown(void);
void LEDRestore(void);

#endif
