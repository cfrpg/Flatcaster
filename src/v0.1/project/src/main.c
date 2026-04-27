#include <stdio.h>
#include "sys.h"
#include "sys_config.h"
#include "delay.h"
#include "debug_usart.h"
#include "timer.h"
#include "led.h"
#include "parameter.h"
#include "pptlink.h"
#include "max98357a.h"
#include "signalGen.h"
#include "ks_engine.h"
#include "touch.h"
#include "midi.h"
#include "adc.h"
#include "norflash.h"
#include "instrument_data.h"
#include "mathHelper.h"
#include "spl_engine.h"
#include "keys.h"


void show_logo(void);

volatile u32 timecnt[4];

float freq_table[6][7];
u8 note_table[6][7];

KS_Engine my_guitar;
SPL_Engine spl_guitar;

float volume=0;
u8 low_batt=0;

u8 cnt=0;

u8 adc_ch=0;

s16 string_buff[6][1024];
s32 string_pos[6];
s32 string_note[6];
float outbuff[I2S_BUF_SIZE];

u8 source=0;

void set_LED(void)
{
	if(low_batt==1)
	{
		LEDSetPattern(LED_1Hz,LED_OFF,LED_OFF);
	}
	else
	{
		if(source==0)
			LEDSetPattern(LED_OFF,LED_OFF,LED_1Hz);
		else
			LEDSetPattern(LED_OFF,LED_1Hz,LED_OFF);
	}
}

int main(void)
{  
	SystemConfigInit();
	DelayInit(288000000);
	DebugUSARTInit(2000000);
	MainClockInit();
	ParamInit();
	
	// Init hardware drivers
	LEDInit();
	LEDSetPattern(LED_OFF,LED_OFF,LED_1Hz);
	KeysInit();
	
	ADCInit();
	TouchInit();
	MAX98357AInit();
	FlashInit();	
	FlashXIPInit();
	
	// Init software modules
	ks_init(&my_guitar,48000);
	SPL_Init(&spl_guitar,&UI_guitar);
	u32 cnt=0;	
	u8 output=0;

	for(u8 i=0;i<6;i++)
	{
		string_pos[i]=-1;
		string_note[i]=0;
	}
	
	// Init freq table	
	s32 empty_fert=0;
	s32 first_fert=1;
	for(u8 i=0;i<6;i++)
	{
		s32 idx=guitar_empty_string[i]+empty_fert;
		note_table[i][0]=idx;		
		for(u8 j=1;j<7;j++)
		{
			u8 real_fert=6-j+first_fert;
			note_table[i][j]=idx+real_fert;			
		}
	}
	for(u8 i=0;i<6;i++)
	{
		for(u8 j=0;j<7;j++)
		{
			freq_table[i][j]=midi_frequencies[note_table[i][j]];
		}
	}	
	// Check vol
	ADCStartChannel(adc_ch);
	
	// Calibration
	LED_R=0;
	TouchScan();
	delay_ms(1000);
	TouchSetRef();
	LED_R=1;
	show_logo();
	
//	while(1);
	
	while(1)
	{
		// 10Hz update
		if(timecnt[0]>=10000)
		{
			timecnt[0]=0;
			LEDUpdate();
			if(adc_ch==0)
			{
				// vol data
				u16 vol=ADCReadOut()>>4;
				volume=vol*1.0f/256;
				adc_ch=3;
				
			}
			else if(adc_ch==3)
			{
				// batt data
				float volt=ADCReadVolt()*2;
				if(low_batt==0 && volt<3.68f)
				{
					low_batt=1;
					set_LED();
				}
				if(low_batt==1 && volt>3.68f)
				{
					low_batt=0;
					set_LED();
				}
				adc_ch=0;
				
			}
			ADCStartChannel(adc_ch);			
			
		}
		// 50Hz update
		if(timecnt[1]>=2000)
		{
			timecnt[1]=0;
			// check keys
			KeysUpdate();
			if((KeyStatus[0])==0x0F)
			{	
				source^=1;
				set_LED();
			}
			if(output==0)
			{
				printf("DATA:");
				for(u32 i=0;i<6;i++)
				{
					for(u32 j=0;j<8;j++)
					{					
						printf("%d,",touch.rawData[i][j]);					
					}
				}
			}
			else
			{
				printf("REF:");
				for(u32 i=0;i<6;i++)
				{
					for(u32 j=0;j<8;j++)
					{					
						printf("%d,",touch.refData[i][j]);					
					}
				}
			}			
			printf("\r\n");
			output^=1;
		}
		// 1000Hz update
		if(timecnt[2]>=100)
		{
			timecnt[2]=0;
			// get input
			TouchGetKey();
			
			// trigger note
			for(u8 str=0;str<6;str++)
			{
				if((touch.stringState[str]&0x3F)==1)
				{
					u8 note=note_table[str][touch.stringFert[str]];
					if(source==0)
					{
						stop_string_soft(&my_guitar.strings[str]);
						trig_note(&my_guitar,str,midi_frequencies[note],0.992f,0.2f);
					}
					else
					{
						SPL_Trig_note(&spl_guitar,str,note);
					}
					
					printf("TRIG:%d,%d,%d\r\n",str,touch.stringFert[str]==0?0:7-touch.stringFert[str],note);
				}
			}
			if(audioState.data_required!=0)
			{
				u32 pos=0;
				
				if(audioState.data_required==2)
					pos=I2S_BUF_SIZE;
				if(source==0)
				{
					for(u32 i=0;i<I2S_BUF_SIZE;i+=2)
					{
						float out=0;
						for(u32 j=0;j<6;j++)
						{
							out+=(update_string(&my_guitar.strings[j])*32768.0f)/6;
						}
						audioState.buff[i+pos]=(s16)(out*volume);
						audioState.buff[i+pos+1]=audioState.buff[i+pos];
					}
				}
				else
				{
					SPL_UpdateBuff(&spl_guitar);
					for(u32 i=0;i<I2S_BUF_SIZE;i+=2)
					{
						float out=0;
						for(u32 j=0;j<6;j++)
						{
							if(spl_guitar.strings[j].active>=0)
							{
								out+=((float)spl_guitar.strings[j].buff[i/2]);
							}						
						}
						out=Clampf(out/3*volume,-32767,32767);
						audioState.buff[i+pos]=(s16)(out*volume);
						audioState.buff[i+pos+1]=audioState.buff[i+pos];
					}
				}
				audioState.data_required=0;
			}
//			printf("%d\r\n",timecnt[2]);
		}
		// Slow work, 1Hz
		if(timecnt[3]>=100000)
		{
			timecnt[3]=0;
			
			if(debug_cmd_ready == 1)
			{
				//ppt link
				DebugUSARTGetCmd();
				AnalyzePkg(debug_cmd_buff, debug_cmd_length);
				debug_cmd_ready=0;
			}			
		}		
	}
}

void TMR1_BRK_TMR9_IRQHandler(void)
{
	u8 i;
	if(tmr_interrupt_flag_get(TMR9,TMR_OVF_FLAG)!=RESET)
	{
		tmr_flag_clear(TMR9,TMR_OVF_FLAG);
		for(i=0;i<4;i++)
		{
			timecnt[i]++;
		}
	}
}

void show_logo(void)
{	
	printf("___________.__          __                          __                \r\n");
	printf("\\_   _____/|  | _____ _/  |_  ____ _____    _______/  |_  ___________ \r\n");
	printf(" |    __)  |  | \\__  \\\\   __\\/ ___\\\\__  \\  /  ___/\\   __\\/ __ \\_  __ \\ \r\n");
	printf(" |     \\   |  |__/ __ \\|  | \\  \\___ / __ \\_\\___ \\  |  | \\  ___/|  | \\/ \r\n");
	printf(" \\___  /   |____(____  /__|  \\___  >____  /____  > |__|  \\___  >__|   \r\n");
	printf("     \\/              \\/          \\/     \\/     \\/            \\/       \r\n");
}