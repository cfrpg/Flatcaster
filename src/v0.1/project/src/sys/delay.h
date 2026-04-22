#ifndef __DELAY_H
#define __DELAY_H

#include "at32f435_437.h"

void DelayInit(u32 clk);
void delay_us(u32 us);
void delay_ms(u32 ms);

#endif
