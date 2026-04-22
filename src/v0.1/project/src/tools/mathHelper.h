#ifndef __MATHHELPER_H
#define __MATHHELPER_H

#include "sys.h"
#include "math.h"

#ifndef PI
#define PI 		3.1415926f
#endif
#define TwoPI 	6.283185307f
#define PIOver2	1.570796326f
#define PIOver4	0.7853981634f
#define PISquare 9.869604401f

#define R2D		57.2957795f
#define D2R		0.017453293f

extern const float BinomialCoefficients[][11];
extern const float FactorialTable[];

typedef struct
{
	float val;
	float lastData;
	float dt;
	float hpf;
} Derivator;

static inline float Lerp(float x0,float y0,float x1,float y1,float x)
{
	return y0+(x-x0)*(y1-y0)/(x1-x0);
}

static inline float AngleSub(float a,float b)
{
	if(a>b)
		return a-b;
	return a+TwoPI-b;
}


static inline float Clampf(float v,float min,float max)
{
	if(v<min)
		return min;
	if(v>max)
		return max;
	return v;
}

static inline s32 Clampi(s32 v,s32 min,s32 max)
{
	if(v<min)
		return min;
	if(v>max)
		return max;
	return v;
}

static inline float AngleNormalize(float a)
{
	if(a>PI)
		return a-TwoPI;
	if(a<-PI)
		return a+TwoPI;
	return a;
}

static inline float AngleToPostitve(float a)
{
	if(a<0)
		return a+TwoPI;
	return a;
}

static inline float Signf(float f)
{
	return copysignf(1.0,f);
}

static inline u32 UDivRound(u32 a,u32 b)
{
	return (a+(b>>1))/b;
}

static inline s32 DivRound(s32 a,s32 b)
{
	s32 sa=a>>31,sb=b>>31;
	a=(a^sa)-sa;
	b=(b^sb)-sb;
	if(sa^sb)
	{
		return -(a+(b>>1))/b;
	}
	return (a+(b>>1))/b;	
}

float NumDiff(Derivator *d,float v);
void DerivatorInit(Derivator *d,float dt,float hpf);

void Binomial(s32 n,s8 sign,float *res);
void PolynomialMul(float *p1,float *p2,u8 n1,u8 n2,float *res);

u8 GetDeadtimeConfig(u32 dt);
#endif
