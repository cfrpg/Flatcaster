/* add user code begin Header */
/**
  **************************************************************************
  * @file     wk_tmr.c
  * @brief    work bench config program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "wk_tmr.h"

/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief  init tmr1 function.
  * @param  none
  * @retval none
  */
void wk_tmr1_init(void)
{
  /* add user code begin tmr1_init 0 */

  /* add user code end tmr1_init 0 */

  gpio_init_type gpio_init_struct;
  tmr_input_config_type  tmr_input_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr1_init 1 */

  /* add user code end tmr1_init 1 */

  /* configure the CH2 pin */
  gpio_pin_mux_config(FRET_0_GPIO_PORT, GPIO_PINS_SOURCE9, GPIO_MUX_1);
  gpio_init_struct.gpio_pins = FRET_0_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(FRET_0_GPIO_PORT, &gpio_init_struct);

  /* configure the CH3 pin */
  gpio_pin_mux_config(FRET_1_GPIO_PORT, GPIO_PINS_SOURCE10, GPIO_MUX_1);
  gpio_init_struct.gpio_pins = FRET_1_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(FRET_1_GPIO_PORT, &gpio_init_struct);

  /* configure the CH4 pin */
  gpio_pin_mux_config(FRET_2_GPIO_PORT, GPIO_PINS_SOURCE11, GPIO_MUX_1);
  gpio_init_struct.gpio_pins = FRET_2_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(FRET_2_GPIO_PORT, &gpio_init_struct);

  /* configure counter settings */
  tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR1, TMR_CLOCK_DIV1);
  tmr_repetition_counter_set(TMR1, 0);
  tmr_period_buffer_enable(TMR1, FALSE);
  tmr_base_init(TMR1, 65535, 1);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR1, TRUE);
  tmr_primary_mode_select(TMR1, TMR_PRIMARY_SEL_ENABLE);

  /* configure channel 2 input settings */
  tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_2;
  tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
  tmr_input_struct.input_filter_value = 0;
  tmr_input_channel_init(TMR1, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);

  /* configure channel 3 input settings */
  tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_3;
  tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
  tmr_input_struct.input_filter_value = 0;
  tmr_input_channel_init(TMR1, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);

  /* configure channel 4 input settings */
  tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_4;
  tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
  tmr_input_struct.input_filter_value = 0;
  tmr_input_channel_init(TMR1, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);

  tmr_counter_enable(TMR1, TRUE);

  /**
   * Users need to configure TMR1 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding TMR1 interrupt.
   *     --tmr_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
   *     --void TMR1_OVF_TMR10_IRQHandler(void)
   */

  /* add user code begin tmr1_init 2 */

  /* add user code end tmr1_init 2 */
}

/**
  * @brief  init tmr4 function.
  * @param  none
  * @retval none
  */
void wk_tmr4_init(void)
{
  /* add user code begin tmr4_init 0 */

  /* add user code end tmr4_init 0 */

  gpio_init_type gpio_init_struct;
  tmr_input_config_type  tmr_input_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr4_init 1 */

  /* add user code end tmr4_init 1 */

  /* configure the CH1 pin */
  gpio_pin_mux_config(FRET_3_GPIO_PORT, GPIO_PINS_SOURCE6, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = FRET_3_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(FRET_3_GPIO_PORT, &gpio_init_struct);

  /* configure the CH2 pin */
  gpio_pin_mux_config(FRET_4_GPIO_PORT, GPIO_PINS_SOURCE7, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = FRET_4_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(FRET_4_GPIO_PORT, &gpio_init_struct);

  /* configure the CH3 pin */
  gpio_pin_mux_config(FRET_5_GPIO_PORT, GPIO_PINS_SOURCE8, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = FRET_5_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(FRET_5_GPIO_PORT, &gpio_init_struct);

  /* configure the CH4 pin */
  gpio_pin_mux_config(FRET_6_GPIO_PORT, GPIO_PINS_SOURCE9, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = FRET_6_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(FRET_6_GPIO_PORT, &gpio_init_struct);

  /* configure counter settings */
  tmr_cnt_dir_set(TMR4, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR4, TMR_CLOCK_DIV1);
  tmr_period_buffer_enable(TMR4, FALSE);
  tmr_base_init(TMR4, 65535, 1);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR4, FALSE);
  tmr_primary_mode_select(TMR4, TMR_PRIMARY_SEL_RESET);

  /* configure sub-mode */
  tmr_sub_mode_select(TMR4, TMR_SUB_TRIGGER_MODE);

  /* configure sub-mode input */
  tmr_trigger_input_select(TMR4, TMR_SUB_INPUT_SEL_IS0);

  /* configure channel 1 input settings */
  tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_1;
  tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
  tmr_input_struct.input_filter_value = 0;
  tmr_input_channel_init(TMR4, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);

  /* configure channel 2 input settings */
  tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_2;
  tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
  tmr_input_struct.input_filter_value = 0;
  tmr_input_channel_init(TMR4, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);

  /* configure channel 3 input settings */
  tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_3;
  tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
  tmr_input_struct.input_filter_value = 0;
  tmr_input_channel_init(TMR4, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);

  /* configure channel 4 input settings */
  tmr_input_struct.input_channel_select = TMR_SELECT_CHANNEL_4;
  tmr_input_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct.input_polarity_select = TMR_INPUT_RISING_EDGE;
  tmr_input_struct.input_filter_value = 0;
  tmr_input_channel_init(TMR4, &tmr_input_struct, TMR_CHANNEL_INPUT_DIV_1);

  /* add user code begin tmr4_init 2 */

  /* add user code end tmr4_init 2 */
}

/* add user code begin 1 */

/* add user code end 1 */
