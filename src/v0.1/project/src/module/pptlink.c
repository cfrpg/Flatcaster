#include "pptlink.h"
#include "debug_usart.h"
#include "stdio.h"
#include "parameter.h"
#include "led.h"
#include "flash.h"

#include "delay.h"




u8 cmdcmp(u8* data,const char *cmd)
{
	while(*cmd!=0)
	{
		if(*data!=*cmd)
			return 0;
		data++;
		cmd++;
	}
	return 1;
}

void AnalyzePkg(u8 *ppt_package_buf,u16 data_len)
{
	u16 len=data_len;	
	u8 i;
	s32 v;	
	
	// set parameter command
	// *setXXXSPPPPPPPP/	(flash after set)
	// *setmXXXSPPPPPPPP/	(no flash after set)
	// X : parameter ID
	// S : parameter sign
	// P : parameter value(8 digits)
	if(cmdcmp(ppt_package_buf,"set"))
	{
		u8 off=0;
		u16 paramid;
		if(ppt_package_buf[3]=='m')
		{
			off=1;
			printf("SETM CMD\r\n");
		}
		else
			printf("SET CMD\r\n");
		if(len!=15+off)
		{
			printf("Invalid length:%d.\r\n",len);		
			return;
		}
		paramid=ppt_package_buf[3+off]-'0';
		paramid*=10;
		paramid+=ppt_package_buf[4+off]-'0';
		paramid*=10;
		paramid+=ppt_package_buf[5+off]-'0';	
		
		printf("ID:%d\r\n",paramid);
		v=0;
		for(i=0;i<8;i++)
		{
			v*=10;
			v+=ppt_package_buf[7+i+off]-'0';
		}
		if(ppt_package_buf[6+off]=='-')
			v*=-1;
		printf("Value:%d\r\n",v);
		off=1-off;
		if(ParamSet(paramid,v,off)==0)
		{
			printf("Complete.\r\n");			
		}
		else
		{
			printf("Failed.\r\n");			
		}
		return;
	}
	
	// show parameter list command
	// *show/
	if(cmdcmp(ppt_package_buf,"show"))
	{
		printf("SHOW CMD\r\n");
		ParamShow();
		return;
	}
	
	// reset all parameters command
	// *rstp/
	if(cmdcmp(ppt_package_buf,"rstp"))
	{
		printf("RSTP CMD\r\n");
		ParamReset(0);
		ParamWrite();
		printf("Param reset complete.\r\n");
		ParamShow();
		return;
	}	
	
	// get internal parameter reference
	// *pref/
	if(cmdcmp(ppt_package_buf,"pref"))
	{		
		DebugUSARTSend((u8*)(&parameterRefSize),4);
		DebugUSARTSend((u8*)parameterRef,parameterRefSize);	
		return;
	}
	
}
