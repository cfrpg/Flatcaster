#include "spl_engine.h"
#include "string.h"
#include "mathHelper.h"

void SPL_Init(SPL_Engine *engine,const InstrumentConfig *ins)
{
	engine->data_per_note=ins->bytes_per_note/2;
	engine->max_note=ins->max_midi_note;
	engine->min_note=ins->min_midi_note;
	
	for(u8 i=0;i<6;i++)
	{
		engine->strings[i].active=0;
		engine->strings[i].curr_pos=0;
		engine->strings[i].note=0;
		memset(engine->strings[i].buff,0,I2S_BUF_SIZE*2);
	}
}

void SPL_Trig_note(SPL_Engine *engine,u8 id,u8 note)
{
	if(note>=engine->min_note&&note<=engine->max_note)
	{
		note-=engine->min_note;
		engine->strings[id].curr_pos=0;
		engine->strings[id].note=note;
		engine->strings[id].active=1;
		memset(engine->strings[id].buff,0,I2S_BUF_SIZE*2);
	}
}

void SPL_UpdateBuff(SPL_Engine *engine)
{
	u32 len;
	SPL_String *string;
	for(u8 str=0;str<6;str++)
	{
		string=&engine->strings[str];
		
		if(string->active==1)
		{
			len=I2S_BUF_SIZE/2;
			if(string->curr_pos+len >= engine->data_per_note)
			{
				string->active=0;
				string->curr_pos=0;
				memset(string->buff,0,I2S_BUF_SIZE*2);
			}
			else
			{
				memcpy(string->buff,&(guitar_sus_down[string->note][string->curr_pos]),len*2);
				string->curr_pos+=len;
			}
		}
	}
	
}

