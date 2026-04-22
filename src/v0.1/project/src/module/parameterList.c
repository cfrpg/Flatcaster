#include "parameter.h"

const ParameterRecord parameterList[PARAM_NUM]=
{
//Type	Name				default value			min value				max value					注释中禁用英文逗号！
	0,	"UPDATE_RATE",		{.intValue=		400},	{.intValue=		50},	{.intValue=		4000},	//控制运行的频率，Hz	
	5,	"CTRL_CH1_RATE_FF",	{.floatValue=	0},		{.floatValue=	-1000},	{.floatValue=	1000},	//电磁铁控制通道1速率环前馈
	
};
