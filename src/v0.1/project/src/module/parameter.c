#include "parameter.h"
#include "stdio.h"
#include "string.h"
#include "delay.h"
#include "led.h"
#include "stdarg.h"

u8 paramReadFromSoC(void);
u16 checkParams(u8 r);

ParameterSet params;

u16 readHalfWord(u32 addr)
{
	return *(__IO uint16_t*)addr;
}
u32 readWord(u32 addr)
{
	return *(__IO uint32_t*)addr;
}


void ParamInit(void)
{
	u16 t;	
	PRINT_INFO("Loading parameters...");
	t=ParamRead();
	if(t)
	{
		if(t==0xFFFF)
		{
			PRINT_INFO("Reset all parameters.");
			LEDFlash(3);
		}
		else
		{
			PRINT_INFO("Reset %d parameter(s).",t);
			LEDFlash(5);
		}
	}
	PRINT_INFO("%d parameters loaded from Flash.",PARAM_NUM);	
}

u8 paramReadFromSoC(void)
{	
	u32 addr=FLASH_BASE+TGT_SECTOR_ADDR;
	memcpy((void*)(&params),(void*)addr,sizeof(params));	
	return 0;
}

u16 checkParams(u8 r)
{
	PRINT_INFO("Check parameters.");
	u16 i;		
	if(params.headFlag!=PARAM_HEAD)
	{
		PRINT_INFO("Header not found.");
		if(r)
		{
			ParamReset(0);
			ParamWrite();
		}
		return 255;
	}
	if(params.tailFlag!=PARAM_TAIL)
	{		
		PRINT_INFO("Tail not found.");
		for(i=0;i<PARAM_NUM;i++)
		{
			if(params.values[i].intValue==PARAM_TAIL)
			{
				PRINT_INFO("Found tail at %d.",i);
				params.values[i].intValue=0;
				if(r)
				{
					ParamReset(i);
					ParamWrite();	
				}				
				return PARAM_NUM-i;
			}
		}
		PRINT_INFO("No tail.");
		if(r)
		{			
			ParamReset(0);
			ParamWrite();
		}
		return 0xFFFF;
	}
	PRINT_INFO("Parameter check ok.");
	return 0;
}

u16 ParamRead(void)
{
	u8 res;		
	res = paramReadFromSoC();	
	if(res!=0)
		return res;	
	return checkParams(1);
}

u8 paramWriteToSoC(void)
{
	u16 *data=(u16*)&params;
	u32 sectorAddr=FLASH_BASE+TGT_SECTOR_ADDR;
	flash_write(sectorAddr,data,sizeof(params)/2);
	LEDFlash(3);
	return 0;
}

u8 ParamWrite(void)
{	
	return paramWriteToSoC();	
}

void ParamReset(u16 first)
{	
	u16 i;
	params.headFlag=PARAM_HEAD;
	for(i=first;i<PARAM_NUM;i++)
	{
		if(parameterList[i].type>0)
			params.values[i].floatValue=parameterList[i].defaultValue.floatValue;
		if(parameterList[i].type<=0)
			params.values[i].intValue=parameterList[i].defaultValue.intValue;
	}
	params.tailFlag=PARAM_TAIL;
}

float paramReadFixed(s32 v,u8 n)
{
	float res=v;
	while(n--)
	{
		res/=10;
	}
	return res;
}
u32 paramReadBinary(s32 v)
{
	u32 res=0;
	u32 mask=1;
	while(v>0)
	{
		if(v%10==1)
		{
			res|=mask;
		}
		mask<<=1;
		v/=10;
	}
	return res;
}

u8 ParamSet(u16 id,s32 v,u8 flush)
{
	s8 type;
	
	if(id>=PARAM_NUM)
		return 1;
	type=parameterList[id].type;
	if(type>0)
	{
		params.values[id].floatValue=paramReadFixed(v,type);
		if(params.values[id].floatValue>parameterList[id].maxValue.floatValue)
		{
			params.values[id].floatValue=parameterList[id].maxValue.floatValue;
		}
		if(params.values[id].floatValue<parameterList[id].minValue.floatValue)
		{
			params.values[id].floatValue=parameterList[id].minValue.floatValue;
		}
	}
	else
	{
		if(type==0)
		{
			params.values[id].intValue=v;
		}
		else
		{
			params.values[id].intValue=paramReadBinary(v);
		}
		if(params.values[id].intValue>parameterList[id].maxValue.intValue)
		{
			params.values[id].intValue=parameterList[id].maxValue.intValue;
		}
		if(params.values[id].intValue<parameterList[id].minValue.intValue)
		{
			params.values[id].intValue=parameterList[id].minValue.intValue;
		}
	}
	if(flush)
		return ParamWrite();
	return 0;	
}

void ParamShow(void)
{
	u8 i;
	for(i=0;i<PARAM_NUM;i++)
	{
		if(parameterList[i].type<=0)
		{
			PRINTLN("#%d:%s(%d):%d",i,parameterList[i].name,parameterList[i].type,params.values[i].intValue);
		}
		if(parameterList[i].type>0)
		{
			PRINTLN("#%d:%s(%d):%f",i,parameterList[i].name,parameterList[i].type,params.values[i].floatValue);
		}		
	}
	PRINTLN("Param end.");
}

void* ParamGetFromName(const char* name)
{
	//find parameter id
	u8 flag=0;
	u8 i=0;	
	for(i=0;i<PARAM_NUM;i++)
	{
		if(strcmp(name,parameterList[i].name)==0)
		{
			flag=1;			
			break;
		}
	}
	if(flag)
	{
		if(parameterList[i].type==0)
		{
			return &(params.values[i].intValue);
		}
		if(parameterList[i].type<0)
		{
			return &(params.values[i].intValue);
		}
		if(parameterList[i].type>0)
		{
			return &(params.values[i].floatValue);
		}
	}
	PRINT_INFO("parameter missing: %s",name);
	return 0;
}

void* ParamGetFromFormat(const char* name, ...)
{
	char buf[20];
	va_list args;
	va_start(args,name);
	vsnprintf(buf,sizeof(buf),name,args);
	va_end(args);
	return ParamGetFromName(buf);
}

u8 ParamSetWithName(const char* name,void* value,u8 flush)
{
	u8 flag=0;
	u8 i=0;	
	for(i=0;i<PARAM_NUM;i++)
	{
		if(strcmp(name,parameterList[i].name)==0)
		{
			flag=1;			
			break;
		}
	}
	if(flag)
	{
		if(parameterList[i].type<=0)
		{
			params.values[i].intValue=*((s32*)value);
			if(params.values[i].intValue>parameterList[i].maxValue.intValue)
			{
				params.values[i].intValue=parameterList[i].maxValue.intValue;
			}
			if(params.values[i].intValue<parameterList[i].minValue.intValue)
			{
				params.values[i].intValue=parameterList[i].minValue.intValue;
			}				
		}
		if(parameterList[i].type>0)
		{
			params.values[i].floatValue=*((float*)value);
			if(params.values[i].floatValue>parameterList[i].maxValue.floatValue)
			{
				params.values[i].floatValue=parameterList[i].maxValue.floatValue;
			}
			if(params.values[i].floatValue<parameterList[i].minValue.floatValue)
			{
				params.values[i].floatValue=parameterList[i].minValue.floatValue;
			}
		}
	}
	if(flush)
		return ParamWrite();
	return 0;
}
