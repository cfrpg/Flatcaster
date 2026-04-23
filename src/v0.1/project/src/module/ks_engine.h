#ifndef _KS_ENGINE_H
#define _KS_ENGINE_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_DELAY_LINE_LENGTH 700 
#define NUM_STRINGS 6


extern const float noise_table[];
extern const uint32_t noise_table_size;


typedef struct 
{
    float delay_line[MAX_DELAY_LINE_LENGTH]; 
    float L;             	 
	float L_frac;
	uint32_t L_int;
    uint32_t ptr;
    float alpha;
    float filter_factor;
    bool active;
} KS_String;


typedef struct 
{
    KS_String strings[NUM_STRINGS];
    float sample_rate;
    uint32_t noise_ptr; 
} KS_Engine;


void ks_init(KS_Engine *engine, float fs);
void trig_note(KS_Engine *engine, uint8_t string_idx, float freq, float alpha, float factor);
float update_string(KS_String *s);
void stop_string_soft(KS_String *s);

#endif