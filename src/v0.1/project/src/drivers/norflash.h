#ifndef _NORFLASH_H
#define _NORFLASH_H

#include "sys.h"

#define QSPI_IO0_PIN    GPIO_PINS_6
#define QSPI_IO0_GPIO_PORT    GPIOA
#define QSPI_IO1_PIN    GPIO_PINS_7
#define QSPI_IO1_GPIO_PORT    GPIOA
#define QSPI_IO2_PIN    GPIO_PINS_4
#define QSPI_IO2_GPIO_PORT    GPIOC
#define QSPI_IO3_PIN    GPIO_PINS_5
#define QSPI_IO3_GPIO_PORT    GPIOC
#define QSPI_SCK_PIN    GPIO_PINS_1
#define QSPI_SCK_GPIO_PORT    GPIOB
#define QSPI1_CS_PIN    GPIO_PINS_10
#define QSPI1_CS_GPIO_PORT    GPIOB



void FlashInit(void);
void FlashXIPInit(void);

void FlashEarse(u32 addr);
void FlashWrite(u32 addr, u8* buff, u32 len);



#endif