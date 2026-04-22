#ifndef __DEBUG_USART_H
#define __DEBUG_USART_H

#include "sys.h"

#define USART_BUF_LEN  	512

extern u8 debug_cmd_buff[USART_BUF_LEN];
extern volatile s16 debug_cmd_length;
extern volatile u8 debug_cmd_ready;

void DebugUSARTInit(u32 baud);
void DebugUSARTSend(u8* data,u32 len);
void DebugUSARTGetCmd(void);


#endif
