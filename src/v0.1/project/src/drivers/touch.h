#ifndef _TOUCH_H
#define _TOUCH_H

#include "sys.h"

#define DRV_C6_PIN    GPIO_PINS_14
#define DRV_C5_PIN    GPIO_PINS_6
#define DRV_C4_PIN    GPIO_PINS_7
#define DRV_C3_PIN    GPIO_PINS_8
#define DRV_C2_PIN    GPIO_PINS_9
#define DRV_C1_PIN    GPIO_PINS_8

#define FRET_0_PIN    GPIO_PINS_9
#define FRET_1_PIN    GPIO_PINS_10
#define FRET_2_PIN    GPIO_PINS_11
#define FRET_3_PIN    GPIO_PINS_6
#define FRET_4_PIN    GPIO_PINS_7
#define FRET_5_PIN    GPIO_PINS_8
#define FRET_6_PIN    GPIO_PINS_9


#define DRV_C1		PAout(8)
#define DRV_C2		PCout(9)
#define DRV_C3		PCout(8)
#define DRV_C4		PCout(7)
#define DRV_C5		PCout(6)
#define DRV_C6		PBout(14)

#define FERT_0_OUT	PAout(9)
#define FERT_1_OUT	PAout(10)
#define FERT_2_OUT	PAout(11)
#define FERT_3_OUT	PBout(6)
#define FERT_4_OUT	PBout(7)
#define FERT_5_OUT	PBout(8)
#define FERT_6_OUT	PBout(9)

#define FERT_0_2_MASK		(0x3FU << 18)
#define FERT_0_2_MODE_OUT	(0x15U << 18)	//010101
#define FERT_0_2_MODE_AF	(0x2AU << 18)	//101010

#define FERT_3_6_MASK		(0xFFU << 12)
#define FERT_3_6_MODE_OUT	(0x55U << 12)	//01010101
#define FERT_3_6_MODE_AF	(0xAAU << 12)	//10101010

typedef struct
{
	s32 rawData[6][8];
	s32 refData[6][8];
	s8 trig[6][8];
	s8 stringState[6];
	s8 stringLastState[6];
	s8 stringFert[6];
	s32 lpf;
	s32 thd;
	volatile u8 currChannel;
} TouchState;

extern TouchState touch;

void TouchInit(void);
void TouchScan(void);
void TouchSetRef(void);
void TouchGetKey(void);

#endif