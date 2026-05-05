#include "parameter.h"

const ParameterRecord parameterList[PARAM_NUM]=
{
//Type	Name				default value			min value				max value					注释中禁用英文逗号！
	0,	"TOUCH_THD",		{.intValue=		200},	{.intValue=		50},	{.intValue=		4000},	//触摸触发的阈值
	0,	"TOUCH_LPF",		{.intValue=		100},	{.intValue=		10},	{.intValue=		4000},	//触摸自适应速度
	0,	"CAPO_POS",			{.intValue=		0},		{.intValue=		0},		{.intValue=		30},	//变调夹位置
	0,	"FERT_SHIFT",		{.intValue=		0},		{.intValue=		0},		{.intValue=		30},	//品位移动
	5,	"CTRL_CH1_RATE_FF",	{.floatValue=	0},		{.floatValue=	-1000},	{.floatValue=	1000},	//电磁铁控制通道1速率环前馈
	
};
