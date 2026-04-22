#ifndef __SIGNALGEN_H
#define __SIGNALGEN_H

#include "sys.h"

#define SINE_WAVE 		0
#define SQUARE_WAVE 	1
#define TRIANGLE_WAVE	2


typedef struct
{
	float freq;
	float amp;
	float offset;
	float dt;
	float time;
	float period;
	float value;
	u8 type;
} SignalWave;

void SGInitSine(SignalWave *s,float f,float amp,float offset);
void SGInitSquare(SignalWave *s,float period,float min,float max);
void SGInitTriangle(SignalWave *s,float f,float amp,float offset);
float SGUpdate(SignalWave *s,float dt);

#endif
