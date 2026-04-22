#include "mathHelper.h"
#include "math.h"




void DerivatorInit(Derivator *d,float dt,float hpf)
{
	d->dt=dt;	
	d->val=0;
	d->hpf=hpf;
	d->lastData=0;
}

float NumDiff(Derivator *d,float v)
{
	d->val=d->hpf*(v-d->lastData)+d->val;
	d->val/=(1+d->hpf);
	d->lastData=v;	
	return d->val;
}



void Binomial(s32 n,s8 sign,float *res)
{
	u8 i;
	for(i=0;i<n+1;i++)
	{
		res[i]=BinomialCoefficients[n][i];		
	}
	if(sign<0)
	{
		for(i=1;i<n+1;i+=2)
			res[i]*=-1;
	}
}

void PolynomialMul(float *p1,float *p2,u8 n1,u8 n2,float *res)
{
	u8 i,j;
	for(i=0;i<n1+n2-1;i++)
		res[i]=0;
	for(i=0;i<n1;i++)
	{
		for(j=0;j<n2;j++)
		{
			res[i+j]+=p1[i]*p2[j];
		}
	}
}

u8 GetDeadtimeConfig(u32 dt)
{
	if(dt<=128)
		return dt;
	if(dt<=256)
		return ((dt+1)>>1)+64;
	if(dt<=512)
		return ((dt+7)>>3)+160;
	if(dt>1008)
		dt=1008;
	return ((dt+15)>>4)+192;
}

const float BinomialCoefficients[][11]={
	{1,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,0},
	{1,2,1,0,0,0,0,0,0,0,0},
	{1,3,3,1,0,0,0,0,0,0,0},
	{1,4,6,4,1,0,0,0,0,0,0},
	{1,5,10,10,5,1,0,0,0,0,0},
	{1,6,15,20,15,6,1,0,0,0,0},
	{1,7,21,35,35,21,7,1,0,0,0},
	{1,8,28,56,70,56,28,8,1,0,0},
	{1,9,36,84,126,126,84,36,9,1,0},
	{1,10,45,120,210,252,210,120,45,10,1}
};

const float FactorialTable[] = {
    1.0f, 1.0f, 2.0f, 6.0f, 24.0f,
    120.0f, 720.0f, 5040.0f, 40320.0f, 362880.0f
};
