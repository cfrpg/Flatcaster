#ifndef _SPL_ENGINE_H
#define _SPL_ENGINE_H

#include "sys.h"
#include "max98357a.h"
#include "instrument_data.h"


typedef struct
{
	s16 buff[I2S_BUF_SIZE];
	s32 curr_pos;
	s32 note;
	u8 active;
} SPL_String;

typedef struct
{
	SPL_String strings[6];
	s32 max_note;
	s32 min_note;
	u32 data_per_note;
} SPL_Engine;


void SPL_Init(SPL_Engine *engine,const InstrumentConfig *ins);
void SPL_Trig_note(SPL_Engine *engine,u8 id,u8 note);

void SPL_UpdateBuff(SPL_Engine *engine);

#endif