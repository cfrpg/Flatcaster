#include "ks_engine.h"

void ks_init(KS_Engine *engine, float fs) 
{
    engine->sample_rate = fs;
    engine->noise_ptr = 0;
    
    for (int i = 0; i < NUM_STRINGS; i++) 
	{
        engine->strings[i].active = false;
        engine->strings[i].ptr = 0;
        engine->strings[i].L = 0;
        memset(engine->strings[i].delay_line, 0, sizeof(float) * MAX_DELAY_LINE_LENGTH);
    }
}

void trig_note(KS_Engine *engine, uint8_t string_idx, float freq, float alpha, float factor) 
{
    if (string_idx >= NUM_STRINGS) return;

    KS_String *s = &engine->strings[string_idx];
    
	float L=engine->sample_rate / freq;
	s->L=L;
	s->L_int=(uint32_t)L;
	s->L_frac=L-s->L_int;        
   
    s->ptr = 0;
    s->alpha = alpha;
    s->filter_factor = factor;
    s->active = true;
	
	uint32_t fill_len = s->L_int + 1;
    if (fill_len > MAX_DELAY_LINE_LENGTH) 
		fill_len = MAX_DELAY_LINE_LENGTH;

    for (uint32_t i = 0; i < fill_len; i++)
	{
        s->delay_line[i] = noise_table[engine->noise_ptr];
        engine->noise_ptr++;
        if (engine->noise_ptr >= noise_table_size) 
		{
            engine->noise_ptr = 0;
        }
    }
}

float update_string(KS_String *s) 
{
    if (!s->active) return 0.0f;

    float v0 = s->delay_line[s->ptr];

    uint32_t next_idx = s->ptr + 1;
    if (next_idx >= s->L_int) next_idx = 0;
    float v1 = s->delay_line[next_idx];

    float output = v0 + s->L_frac * (v1 - v0);


    float filtered = (v0 * s->filter_factor + v1 * (1.0f - s->filter_factor));
    s->delay_line[s->ptr] = filtered * s->alpha;

    s->ptr = next_idx;

    return output;
}


void stop_string_soft(KS_String *s) 
{    
    s->alpha *= 0.1f; 
}
