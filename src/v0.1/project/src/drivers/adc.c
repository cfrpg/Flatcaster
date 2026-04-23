#include "adc.h"



void ADCInit(void)
{
	gpio_init_type gpio_init_struct;
	adc_base_config_type adc_base_struct;
	adc_common_config_type adc_common_struct;
	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_ADC3_PERIPH_CLOCK, TRUE);

	gpio_default_para_init(&gpio_init_struct);
	gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
	gpio_init_struct.gpio_pins = GPIO_PINS_0;
	gpio_init(GPIOA, &gpio_init_struct);
	
	gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
	gpio_init_struct.gpio_pins = GPIO_PINS_3;
	gpio_init(GPIOA, &gpio_init_struct);
	
	adc_common_default_para_init(&adc_common_struct);
	adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;
	adc_common_struct.div = ADC_HCLK_DIV_4;
	adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;
	adc_common_struct.common_dma_request_repeat_state = FALSE;
	adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;
	adc_common_struct.tempervintrv_state = FALSE;
	adc_common_struct.vbat_state = FALSE;
	adc_common_config(&adc_common_struct);
	
	adc_base_default_para_init(&adc_base_struct);
	adc_base_struct.sequence_mode = TRUE;
	adc_base_struct.repeat_mode = FALSE;
	adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
	adc_base_struct.ordinary_channel_length = 1;
	adc_base_config(ADC3, &adc_base_struct);

	adc_resolution_set(ADC3, ADC_RESOLUTION_12B);
	
	adc_ordinary_channel_set(ADC3, ADC_CHANNEL_0, 1, ADC_SAMPLETIME_12_5);
	adc_ordinary_channel_set(ADC3, ADC_CHANNEL_3, 2, ADC_SAMPLETIME_12_5);
	
	adc_oversample_ratio_shift_set(ADC3, ADC_OVERSAMPLE_RATIO_8, ADC_OVERSAMPLE_SHIFT_3);
	adc_ordinary_oversample_trig_enable(ADC3, FALSE);
	adc_ordinary_oversample_restart_set(ADC3, ADC_OVERSAMPLE_CONTINUE);
	adc_ordinary_oversample_enable(ADC3, TRUE);

	adc_enable(ADC3, TRUE);
	while(adc_flag_get(ADC3, ADC_RDY_FLAG) == RESET);

	adc_calibration_init(ADC3);
	while(adc_calibration_init_status_get(ADC3));
	adc_calibration_start(ADC3);
	while(adc_calibration_status_get(ADC3));	
}

void ADCStartChannel(u8 ch)
{	
	adc_ordinary_channel_set(ADC3, ch, 1, ADC_SAMPLETIME_12_5);
	adc_ordinary_software_trigger_enable(ADC3, TRUE);
}

u16 ADCReadOut(void)
{
	while(adc_flag_get(ADC3, ADC_OCCE_FLAG) == RESET);
	return adc_ordinary_conversion_data_get(ADC3);
}

float ADCReadNormal(void)
{
	return ADCReadOut()/4096.0f;
}

float ADCReadVolt(void)
{
	return ADCReadOut()/4096.0f*3.3f;
}
