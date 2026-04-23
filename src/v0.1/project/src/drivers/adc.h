#ifndef _ADC_H
#define _ADC_H

#include "sys.h"


void ADCInit(void);
void ADCStartChannel(u8 ch);
u16 ADCReadOut(void);
float ADCReadNormal(void);
float ADCReadVolt(void);
#endif