#include "max98357a.h"
#include "string.h"

MAX98357AState audioState;

void max98357a_i2s_init(void)
{
	gpio_init_type gpio_init_struct;
	i2s_init_type i2s_init_struct;

	gpio_default_para_init(&gpio_init_struct);
	i2s_default_para_init(&i2s_init_struct);
	
	crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

	/* configure the WS pin */
	gpio_pin_mux_config(I2S_WS_GPIO_PORT, GPIO_PINS_SOURCE12, GPIO_MUX_5);
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	gpio_init_struct.gpio_pins = I2S_WS_PIN;
	gpio_init(I2S_WS_GPIO_PORT, &gpio_init_struct);

	/* configure the CK pin */
	gpio_pin_mux_config(I2S_CK_GPIO_PORT, GPIO_PINS_SOURCE13, GPIO_MUX_5);
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	gpio_init_struct.gpio_pins = I2S_CK_PIN;
	gpio_init(I2S_CK_GPIO_PORT, &gpio_init_struct);

	/* configure the SD pin */
	gpio_pin_mux_config(I2S_SD_GPIO_PORT, GPIO_PINS_SOURCE15, GPIO_MUX_5);
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	gpio_init_struct.gpio_pins = I2S_SD_PIN;
	gpio_init(I2S_SD_GPIO_PORT, &gpio_init_struct);

	/* configure the i2s_init_struct */
	i2s_init_struct.operation_mode = I2S_MODE_MASTER_TX;
	i2s_init_struct.audio_protocol = I2S_AUDIO_PROTOCOL_PHILLIPS;
	i2s_init_struct.data_channel_format = I2S_DATA_16BIT_CHANNEL_16BIT;
	i2s_init_struct.audio_sampling_freq = I2S_AUDIO_FREQUENCY_48K;
	i2s_init_struct.clock_polarity = I2S_CLOCK_POLARITY_LOW;
	i2s_init_struct.mclk_output_enable = FALSE;
	i2s_init(SPI2, &i2s_init_struct);

	spi_i2s_dma_transmitter_enable(SPI2, TRUE);	
}

void max98357a_dma_init(void)
{
    dma_init_type dma_init_struct;

    crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);

    dma_reset(DMA1_CHANNEL1);
	dmamux_enable(DMA1, TRUE);
    

	dma_default_para_init(&dma_init_struct);
	
	dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
	dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
	dma_init_struct.memory_inc_enable = TRUE;
	dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
	dma_init_struct.peripheral_inc_enable = FALSE;
	dma_init_struct.priority = DMA_PRIORITY_HIGH;
	dma_init_struct.loop_mode_enable = TRUE;
	
	dma_init_struct.peripheral_base_addr    = (uint32_t)&SPI2->dt;
	dma_init_struct.memory_base_addr        = (uint32_t)audioState.buff;
	dma_init_struct.buffer_size             = I2S_TOTAL_BUF_SIZE;
	
	dma_init(DMA1_CHANNEL1, &dma_init_struct);
	dmamux_init(DMA1MUX_CHANNEL1, DMAMUX_DMAREQ_ID_SPI2_TX);

	
    dma_interrupt_enable(DMA1_CHANNEL1, DMA_FDT_INT, TRUE); 
    dma_interrupt_enable(DMA1_CHANNEL1, DMA_HDT_INT, TRUE);

    nvic_irq_enable(DMA1_Channel1_IRQn, 1, 0);    
}



void MAX98357AInit(void)
{
	memset(audioState.buff,0,sizeof(audioState.buff));
	max98357a_i2s_init();
	max98357a_dma_init();
	
	audioState.data_required=0;
	dma_channel_enable(DMA1_CHANNEL1, TRUE);
	i2s_enable(SPI2, TRUE);
}

void DMA1_Channel1_IRQHandler(void)
{	

	if(dma_interrupt_flag_get(DMA1_HDT1_FLAG)!=RESET)
	{
		dma_flag_clear(DMA1_HDT1_FLAG);
//		memcpy(audioState.buff,audioState.next_data,I2S_BUF_SIZE);
		audioState.data_required=1;
	}
	if(dma_interrupt_flag_get(DMA1_FDT1_FLAG)!=RESET)
	{
		dma_flag_clear(DMA1_FDT1_FLAG);
//		memcpy(&audioState.buff[I2S_BUF_SIZE],audioState.next_data,I2S_BUF_SIZE);
		audioState.data_required=2;
	}
	
}
