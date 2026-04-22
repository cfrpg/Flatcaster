#ifndef __MAX98357A_H
#define __MAX98357A_H

#include "sys.h"

#define I2S_WS_PIN    GPIO_PINS_12
#define I2S_WS_GPIO_PORT    GPIOB
#define I2S_CK_PIN    GPIO_PINS_13
#define I2S_CK_GPIO_PORT    GPIOB
#define I2S_SD_PIN    GPIO_PINS_15
#define I2S_SD_GPIO_PORT    GPIOB

#define I2S_BUF_SIZE        512
#define I2S_TOTAL_BUF_SIZE  (I2S_BUF_SIZE * 2)

typedef struct 
{
	s16 buff[I2S_TOTAL_BUF_SIZE];
	s16 *next_data;
	uint8_t data_required;
} MAX98357AState;

extern MAX98357AState audioState;

void MAX98357AInit(void);

#endif