#include "debug_usart.h"
#include <stdio.h>
#include <string.h>


u8 debug_usart_rx_buff[USART_BUF_LEN];
u8 debug_cmd_buff[USART_BUF_LEN];

volatile u8 debug_cmd_ready=0;
volatile s16 debug_rx_pos=0;
volatile s16 debug_frame_head=0;
volatile s16 debug_cmd_length=0;



int fputc(int ch, FILE *f)
{
	while((UART8->sts&0x80)==0);
	UART8->dt=(u8)ch;            
	return ch;
}

void _ttywrch(int ch)
{
	while((UART8->sts&0x80)==0);
	UART8->dt=(u8)ch;
}

void DebugUSARTInit(u32 baud)
{
	gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);

	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_UART8_PERIPH_CLOCK, TRUE);
	
    /* configure the TX pin */
	gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE2, GPIO_MUX_8);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = GPIO_PINS_2;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOC, &gpio_init_struct);

	/* configure the RX pin */
	gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE3, GPIO_MUX_8);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = GPIO_PINS_3;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOC, &gpio_init_struct);
	
	nvic_irq_enable(UART8_IRQn, 3, 3);

    /* configure param */
    usart_init(UART8, baud, USART_DATA_8BITS, USART_STOP_1_BIT);
    usart_transmitter_enable(UART8, TRUE);
	usart_receiver_enable(UART8, TRUE);
//	usart_receiver_enable(UART8, FALSE);

    usart_parity_selection_config(UART8, USART_PARITY_NONE);
	usart_transmit_receive_pin_swap(UART8,TRUE);

    usart_hardware_flow_control_set(UART8, USART_HARDWARE_FLOW_NONE);
	usart_interrupt_enable(UART8, USART_RDBF_INT, TRUE);

    usart_enable(UART8, TRUE);
}

void DebugUSARTSend(u8* data,u32 len)
{
	u32 i;
	
	for(i=0;i<len;i++)
	{	
		while(usart_flag_get(UART8, USART_TDBE_FLAG) == RESET);
		usart_data_transmit(UART8,data[i]);		
	}	
}

void DebugUSARTGetCmd(void)
{
	if(debug_cmd_ready == 0)
	{
		// no cmd
		return;
	}
	memcpy(debug_cmd_buff,&debug_usart_rx_buff[debug_frame_head],debug_cmd_length);
	if(debug_cmd_ready == 2)
	{
		debug_cmd_buff[debug_cmd_length] = '\0'; // add EOL for cli
	}
}

void UART8_IRQHandler(void)
{
	u8 c;
	if(usart_interrupt_flag_get(UART8, USART_RDBF_FLAG) != RESET)
	{
		c = usart_data_receive(UART8);
		if(debug_cmd_ready)
			return;
		
		debug_usart_rx_buff[debug_rx_pos] = c;
		debug_rx_pos++;
		
		// pptlink STA
		if(c == '*')
		{
			debug_frame_head = debug_rx_pos - 1;
			return;
		}
		//pptlink END
		if(c == '/')
		{
			debug_cmd_ready = 1;
			debug_frame_head += 1;
			debug_cmd_length = debug_rx_pos - debug_frame_head - 1;	
			debug_rx_pos = 0; // reset buff pointer
			return;
		}
		// cli end
		if(c == '\n')
		{
			debug_cmd_ready = 2;
			debug_cmd_length = debug_rx_pos - 1;
			// remove \r brfore \n
			if(debug_rx_pos > 1 && debug_usart_rx_buff[debug_rx_pos - 2] == '\r')
			{
				debug_cmd_length -= 1;
			}
			debug_frame_head = 0;
			debug_rx_pos = 0; // reset buff pointer
			return;
		}
    }
} 
