#include "norflash.h"
#include "qspicmd.h"
#include "delay.h"

qspi_cmd_type QSPI_WREN;
qspi_cmd_type QSPI_EN4B;
qspi_cmd_type QSPI_RDSR;
qspi_cmd_type QSPI_READ;
qspi_cmd_type QSPI_WRITE;
qspi_cmd_type QSPI_ERASE;

qspi_cmd_type QSPI_CMD;


void flash_gpio_init(void)
{
	gpio_init_type gpio_init_struct;
	gpio_default_para_init(&gpio_init_struct);
	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	
	/* configure the SCK pin */
	gpio_pin_mux_config(QSPI_SCK_GPIO_PORT, GPIO_PINS_SOURCE1, GPIO_MUX_9);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = QSPI_SCK_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(QSPI_SCK_GPIO_PORT, &gpio_init_struct);

	/* configure the CS pin */
	gpio_pin_mux_config(QSPI1_CS_GPIO_PORT, GPIO_PINS_SOURCE10, GPIO_MUX_9);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = QSPI1_CS_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(QSPI1_CS_GPIO_PORT, &gpio_init_struct);

	/* configure the IO0 pin */
	gpio_pin_mux_config(QSPI_IO0_GPIO_PORT, GPIO_PINS_SOURCE6, GPIO_MUX_10);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = QSPI_IO0_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(QSPI_IO0_GPIO_PORT, &gpio_init_struct);

	/* configure the IO1 pin */
	gpio_pin_mux_config(QSPI_IO1_GPIO_PORT, GPIO_PINS_SOURCE7, GPIO_MUX_10);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = QSPI_IO1_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(QSPI_IO1_GPIO_PORT, &gpio_init_struct);

	/* configure the IO2 pin */
	gpio_pin_mux_config(QSPI_IO2_GPIO_PORT, GPIO_PINS_SOURCE4, GPIO_MUX_10);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = QSPI_IO2_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(QSPI_IO2_GPIO_PORT, &gpio_init_struct);

	/* configure the IO3 pin */
	gpio_pin_mux_config(QSPI_IO3_GPIO_PORT, GPIO_PINS_SOURCE5, GPIO_MUX_10);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = QSPI_IO3_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(QSPI_IO3_GPIO_PORT, &gpio_init_struct);
}

void show_cmd_reg(void)
{
	printf("W0:%08x\r\n",QSPI1->cmd_w0);
	printf("W1:%08x\r\n",QSPI1->cmd_w1);
	printf("W2:%08x\r\n",QSPI1->cmd_w2);
	printf("W3:%08x\r\n",QSPI1->cmd_w3);
}

void flash_qspi_init(void)
{
	crm_periph_clock_enable(CRM_QSPI1_PERIPH_CLOCK, TRUE);
	
	qspi_xip_enable(QSPI1, FALSE);
	qspi_clk_division_set(QSPI1, QSPI_CLK_DIV_8);
	qspi_sck_mode_set(QSPI1, QSPI_SCK_MODE_0);
	qspi_busy_config(QSPI1, QSPI_BUSY_OFFSET_0);
	qspi_auto_ispc_enable(QSPI1);
	
	//Init cmd struct
	qspi_cmd_wren_config(&QSPI_WREN);
	qspi_cmd_en4b_config(&QSPI_EN4B);
	qspi_cmd_rdsr_config(&QSPI_RDSR);
	
	qspi_cmd_read_config(&QSPI_READ,0,0);
	qspi_cmd_write_config(&QSPI_WRITE,0,0);
	qspi_cmd_erase_config(&QSPI_ERASE,0);	
}

void flash_cmd_send(qspi_cmd_type* cmd)
{
	qspi_cmd_operation_kick(QSPI1, cmd);

	/* wait command completed */
	while(qspi_flag_get(QSPI1, QSPI_CMDSTS_FLAG) == RESET);
	qspi_flag_clear(QSPI1, QSPI_CMDSTS_FLAG);
}

void flash_write_enable(void)
{
	flash_cmd_send(&QSPI_WREN);	
}

void flash_busy_check(void)
{
	flash_cmd_send(&QSPI_RDSR);	
}

void flash_write_status(u8 data)
{
	flash_write_enable();
	
	qspi_cmd_wrsr_config(&QSPI_CMD);
	QSPI_CMD.instruction_code=0x31;
	qspi_cmd_operation_kick(QSPI1,&QSPI_CMD);
	while(qspi_flag_get(QSPI1, QSPI_TXFIFORDY_FLAG) == RESET);
	qspi_byte_write(QSPI1, data);
	while(qspi_flag_get(QSPI1, QSPI_CMDSTS_FLAG) == RESET);
	qspi_flag_clear(QSPI1, QSPI_CMDSTS_FLAG);
}

void flash_read_status(void)
{
	u8 data;
	qspi_cmd_rdsr2_config(&QSPI_CMD,0x05);
	qspi_cmd_operation_kick(QSPI1,&QSPI_CMD);	
	while(qspi_flag_get(QSPI1, QSPI_RXFIFORDY_FLAG) == RESET);
	data=qspi_byte_read(QSPI1);
	while(qspi_flag_get(QSPI1, QSPI_CMDSTS_FLAG) == RESET);
	qspi_flag_clear(QSPI1, QSPI_CMDSTS_FLAG);
	printf("ST1:%x\r\n",data);
	
	
	qspi_cmd_rdsr2_config(&QSPI_CMD,0x35);
	qspi_cmd_operation_kick(QSPI1,&QSPI_CMD);	
	while(qspi_flag_get(QSPI1, QSPI_RXFIFORDY_FLAG) == RESET);
	data=qspi_byte_read(QSPI1);
	while(qspi_flag_get(QSPI1, QSPI_CMDSTS_FLAG) == RESET);
	qspi_flag_clear(QSPI1, QSPI_CMDSTS_FLAG);
	printf("ST2:%x\r\n",data);
	
	qspi_cmd_rdsr2_config(&QSPI_CMD,0x15);
	qspi_cmd_operation_kick(QSPI1,&QSPI_CMD);	
	while(qspi_flag_get(QSPI1, QSPI_RXFIFORDY_FLAG) == RESET);
	data=qspi_byte_read(QSPI1);
	while(qspi_flag_get(QSPI1, QSPI_CMDSTS_FLAG) == RESET);
	qspi_flag_clear(QSPI1, QSPI_CMDSTS_FLAG);
	printf("ST3:%x\r\n",data);
}


void flash_read_id(void)
{
	qspi_cmd_rdid_config(&QSPI_CMD);
	qspi_cmd_operation_kick(QSPI1,&QSPI_CMD);
	u8 data[3];
	while(qspi_flag_get(QSPI1, QSPI_RXFIFORDY_FLAG) == RESET);
	for(u8 i=0;i<3;i++)
	{
		
		data[i] = qspi_byte_read(QSPI1);
	}
	
	while(qspi_flag_get(QSPI1, QSPI_CMDSTS_FLAG) == RESET);
	qspi_flag_clear(QSPI1, QSPI_CMDSTS_FLAG);
	printf("id:%x %x %x\r\n",data[0],data[1],data[2]);
}

void flash_set_4byte_addr(void)
{
	qspi_cmd_en4b_config(&QSPI_CMD);
	qspi_cmd_operation_kick(QSPI1,&QSPI_CMD);

	while(qspi_flag_get(QSPI1, QSPI_CMDSTS_FLAG) == RESET);
	qspi_flag_clear(QSPI1, QSPI_CMDSTS_FLAG);
}

void FlashInit(void)
{
	flash_gpio_init();
	flash_qspi_init();
	delay_ms(1);
	flash_busy_check();
	
//	flash_read_status();	
	flash_set_4byte_addr();
	flash_write_status(0x02);
//	flash_read_status();
}

void FlashEarse(u32 addr)
{
	flash_write_enable();
	
	QSPI_ERASE.address_code=addr;
	flash_cmd_send(&QSPI_ERASE);
	flash_busy_check();
}

void FlashWrite(u32 addr, u8* buff, u32 len)
{
	flash_write_enable();
	qspi_cmd_write_config(&QSPI_WRITE,addr,len);
	qspi_cmd_operation_kick(QSPI1,&QSPI_WRITE);
	show_cmd_reg();
	for(u16 i=0;i<len;i++)
	{
		while(qspi_flag_get(QSPI1, QSPI_TXFIFORDY_FLAG) == RESET);
		qspi_byte_write(QSPI1, *buff++);
	}	
	
	while(qspi_flag_get(QSPI1, QSPI_CMDSTS_FLAG) == RESET);
	qspi_flag_clear(QSPI1, QSPI_CMDSTS_FLAG);

	flash_busy_check();
}

void FlashXIPInit(void)
{
	qspi_xip_enable(QSPI1,FALSE);
	qspi_cmd_type *qspi_cmd_struct = &QSPI_CMD;
//	// set rsten
//	qspi_cmd_struct->pe_mode_enable = FALSE;
//	qspi_cmd_struct->pe_mode_operate_code = 0;
//	qspi_cmd_struct->instruction_code = 0x66;
//	qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
//	qspi_cmd_struct->address_code = 0;
//	qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
//	qspi_cmd_struct->data_counter = 0;
//	qspi_cmd_struct->second_dummy_cycle_num = 0;
//	qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
//	qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
//	qspi_cmd_struct->read_status_enable = FALSE;
//	qspi_cmd_struct->write_data_enable = TRUE;
//	flash_cmd_send(qspi_cmd_struct);

//	
//	// set rst
//	qspi_cmd_struct->pe_mode_enable = FALSE;
//	qspi_cmd_struct->pe_mode_operate_code = 0;
//	qspi_cmd_struct->instruction_code = 0x99;
//	qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
//	qspi_cmd_struct->address_code = 0;
//	qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
//	qspi_cmd_struct->data_counter = 0;
//	qspi_cmd_struct->second_dummy_cycle_num = 0;
//	qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
//	qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
//	qspi_cmd_struct->read_status_enable = FALSE;
//	qspi_cmd_struct->write_data_enable = TRUE;
//	flash_cmd_send(qspi_cmd_struct);
//	printf("reset\r\n");
//	flash_read_status();
	
	// init xip
	qspi_xip_type qspi_xip_struct;
	qspi_xip_struct.read_instruction_code = 0xEB; 
	qspi_xip_struct.read_address_length = QSPI_XIP_ADDRLEN_4_BYTE;
	qspi_xip_struct.read_operation_mode = QSPI_OPERATE_MODE_144;
	qspi_xip_struct.read_second_dummy_cycle_num = 6;
	qspi_xip_struct.write_instruction_code = 0x32;
	qspi_xip_struct.write_address_length = QSPI_XIP_ADDRLEN_4_BYTE;
	qspi_xip_struct.write_operation_mode = QSPI_OPERATE_MODE_114;
	qspi_xip_struct.write_second_dummy_cycle_num = 0;
	qspi_xip_struct.write_select_mode = QSPI_XIPW_SEL_MODED;
	qspi_xip_struct.write_time_counter = 0x7F;
	qspi_xip_struct.write_data_counter = 0x1F;
	qspi_xip_struct.read_select_mode = QSPI_XIPR_SEL_MODED;
	qspi_xip_struct.read_time_counter = 0x7F;
	qspi_xip_struct.read_data_counter = 0x1F;
	
	qspi_xip_init(QSPI1, &qspi_xip_struct);
	qspi_xip_enable(QSPI1, TRUE);
	
}