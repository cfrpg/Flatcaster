#ifndef __PARAMETER_H
#define __PARAMETER_H
#include "sys.h"
#include "flash.h"

#define TGT_SECTOR_ADDR 0x001F0000

#define PARAM_TYPE_INT 0
#define PARAM_TYPE_FLOAT 1
#define PARAM_TYPE_BINARY -1

#define PARAM_NUM 2

#define PARAM_HEAD 0x00CFCF00
#define PARAM_TAIL 0x00FCFC00

typedef union
{
	s32 intValue;
	float floatValue;
} UnknowType;

typedef struct
{
	s32 intValue;
	float floatValue;
} BothType;

typedef struct
{
	s8 type;
	const char name[19];
	UnknowType defaultValue;	
	UnknowType minValue;	
	UnknowType maxValue;
} ParameterRecord;

typedef struct
{
	u32 headFlag;
	UnknowType values[PARAM_NUM];
	u32 tailFlag;
} ParameterSet;

extern const ParameterRecord parameterList[PARAM_NUM];
extern const u8 parameterRef[];
extern const u32 parameterRefSize;

extern ParameterSet params;

void ParamInit(void);
u16 ParamRead(void);
u8 ParamWrite(void);
void ParamReset(u16 first);
u8 ParamSet(u16 id,s32 v,u8 flush);
void ParamShow(void);
void* ParamGetFromName(const char* name);
void* ParamGetFromFormat(const char* name, ...);
u8 ParamSetWithName(const char* name,void* value,u8 flush);

#endif
