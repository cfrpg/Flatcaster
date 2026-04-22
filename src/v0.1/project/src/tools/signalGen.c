#include "signalGen.h"
#include "math.h"
#include "mathHelper.h"

void SGInitSine(SignalWave *s,float f,float amp,float offset)
{
	s->freq=f;
	s->period=1.0f/f;
	s->amp=amp;
	s->offset=offset;
	s->type=SINE_WAVE;
	s->time=0;
	s->value=0;
}

void SGInitSquare(SignalWave *s,float period,float min,float max)
{
	s->freq=1.0f/period;
	s->period=period;
	s->amp=(max-min)/2.0f;
	s->offset=(max+min)/2.0f;
	s->type=SQUARE_WAVE;
	s->time=0;
	s->value=0;
}

void SGInitTriangle(SignalWave *s,float f,float amp,float offset)
{
	s->freq=f;
	s->period=1.0f/f;
	s->amp=amp;
	s->offset=offset;
	s->type=TRIANGLE_WAVE;
	s->time=0;
	s->value=0;
}

float sg_update_sine(SignalWave *s,float dt)
{
	s->time+=dt;
	s->value=s->amp*sinf(TwoPI*s->freq*s->time)+s->offset;
	if(s->time>s->period)
		s->time-=s->period;
	return s->value;
}

float sg_update_square(SignalWave *s,float dt)
{
	s->time+=dt;
	if(s->time>s->period)
		s->time-=s->period;
	if(s->time>s->period/2)
	{
		s->value=s->offset-s->amp;
	}
	else
	{
		s->value=s->offset+s->amp;
	}
	
	return s->value;
}

float sg_update_triangle(SignalWave *s,float dt)
{
	s->time+=dt;
	if(s->time>s->period)
		s->time-=s->period;
	if(s->time>s->period/2)
	{
		s->value=4*s->amp*s->freq*s->time-s->amp;
	}
	else
	{
		s->value=2*s->amp-4*s->amp*s->freq*s->time;
	}
	s->value+=s->offset;
	return s->value;
}

float SGUpdate(SignalWave *s,float dt)
{
	if(s->type == SINE_WAVE)
	{
		return sg_update_sine(s,dt);
	}
	if(s->type == SQUARE_WAVE)
	{
		return sg_update_square(s,dt);
	}
	if(s->type == TRIANGLE_WAVE)
	{
		return sg_update_triangle(s,dt);
	}
	return 0;
}
