#include "qspicmd.h"

/**
  * @brief  cmd read config
  * @param  qspi_cmd_struct: the pointer for qspi_cmd_type parameter
  * @param  addr: read start address
  * @param  counter: read data counter
  * @retval none
  */
void qspi_cmd_read_config(qspi_cmd_type *qspi_cmd_struct, uint32_t addr, uint32_t counter)
{
  qspi_cmd_struct->pe_mode_enable = FALSE;
  qspi_cmd_struct->pe_mode_operate_code = 0;
  qspi_cmd_struct->instruction_code = 0xEB;
  qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
  qspi_cmd_struct->address_code = addr;
  qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_3_BYTE;
  qspi_cmd_struct->data_counter = counter;
  qspi_cmd_struct->second_dummy_cycle_num = 6;
  qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_144;
  qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
  qspi_cmd_struct->read_status_enable = FALSE;
  qspi_cmd_struct->write_data_enable = FALSE;
}

/**
  * @brief  cmd write config
  * @param  qspi_cmd_struct: the pointer for qspi_cmd_type parameter
  * @param  addr: write start address
  * @param  counter: write data counter
  * @retval none
  */
void qspi_cmd_write_config(qspi_cmd_type *qspi_cmd_struct, uint32_t addr, uint32_t counter)
{
  qspi_cmd_struct->pe_mode_enable = FALSE;
  qspi_cmd_struct->pe_mode_operate_code = 0;
  qspi_cmd_struct->instruction_code = 0x32;
  qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
  qspi_cmd_struct->address_code = addr;
  qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_4_BYTE;
  qspi_cmd_struct->data_counter = counter;
  qspi_cmd_struct->second_dummy_cycle_num = 0;
  qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_114;
  qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
  qspi_cmd_struct->read_status_enable = FALSE;
  qspi_cmd_struct->write_data_enable = TRUE;
}

/**
  * @brief  cmd erase config
  * @param  qspi_cmd_struct: the pointer for qspi_cmd_type parameter
  * @param  addr: erase address
  * @retval none
  */
void qspi_cmd_erase_config(qspi_cmd_type *qspi_cmd_struct, uint32_t addr)
{
  qspi_cmd_struct->pe_mode_enable = FALSE;
  qspi_cmd_struct->pe_mode_operate_code = 0;
  qspi_cmd_struct->instruction_code = 0x20;
  qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
  qspi_cmd_struct->address_code = addr;
  qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_4_BYTE;
  qspi_cmd_struct->data_counter = 0;
  qspi_cmd_struct->second_dummy_cycle_num = 0;
  qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
  qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
  qspi_cmd_struct->read_status_enable = FALSE;
  qspi_cmd_struct->write_data_enable = TRUE;
}

/**
  * @brief  cmd wren config
  * @param  qspi_cmd_struct: the pointer for qspi_cmd_type parameter
  * @retval none
  */
void qspi_cmd_wren_config(qspi_cmd_type *qspi_cmd_struct)
{
  qspi_cmd_struct->pe_mode_enable = FALSE;
  qspi_cmd_struct->pe_mode_operate_code = 0;
  qspi_cmd_struct->instruction_code = 0x06;
  qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
  qspi_cmd_struct->address_code = 0;
  qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
  qspi_cmd_struct->data_counter = 0;
  qspi_cmd_struct->second_dummy_cycle_num = 0;
  qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
  qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
  qspi_cmd_struct->read_status_enable = FALSE;
  qspi_cmd_struct->write_data_enable = TRUE;
}

/**
  * @brief  cmd en4b config
  * @param  qspi_cmd_struct: the pointer for qspi_cmd_type parameter
  * @retval none
  */
void qspi_cmd_en4b_config(qspi_cmd_type *qspi_cmd_struct)
{
  qspi_cmd_struct->pe_mode_enable = FALSE;
  qspi_cmd_struct->pe_mode_operate_code = 0;
  qspi_cmd_struct->instruction_code = 0xB7;
  qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
  qspi_cmd_struct->address_code = 0;
  qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
  qspi_cmd_struct->data_counter = 0;
  qspi_cmd_struct->second_dummy_cycle_num = 0;
  qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
  qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
  qspi_cmd_struct->read_status_enable = FALSE;
  qspi_cmd_struct->write_data_enable = TRUE;
}

/**
  * @brief  cmd rdsr config
  * @param  qspi_cmd_struct: the pointer for qspi_cmd_type parameter
  * @retval none
  */
void qspi_cmd_rdsr_config(qspi_cmd_type *qspi_cmd_struct)
{
	qspi_cmd_struct->pe_mode_enable = FALSE;
	qspi_cmd_struct->pe_mode_operate_code = 0;
	qspi_cmd_struct->instruction_code = 0x05;
	qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
	qspi_cmd_struct->address_code = 0;
	qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
	qspi_cmd_struct->data_counter = 0;
	qspi_cmd_struct->second_dummy_cycle_num = 0;
	qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
	qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
	qspi_cmd_struct->read_status_enable = TRUE;
	qspi_cmd_struct->write_data_enable = FALSE;
}

void qspi_cmd_rdsr2_config(qspi_cmd_type *qspi_cmd_struct,u8 cmd)
{
	qspi_cmd_struct->pe_mode_enable = FALSE;
	qspi_cmd_struct->pe_mode_operate_code = 0;
	qspi_cmd_struct->instruction_code = cmd;
	qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
	qspi_cmd_struct->address_code = 0;
	qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
	qspi_cmd_struct->data_counter = 1;
	qspi_cmd_struct->second_dummy_cycle_num = 0;
	qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
	qspi_cmd_struct->read_status_config = QSPI_RSTSC_SW_ONCE;
	qspi_cmd_struct->read_status_enable = FALSE;
	qspi_cmd_struct->write_data_enable = FALSE;
}

void qspi_cmd_rdid_config(qspi_cmd_type *qspi_cmd_struct)
{
	qspi_cmd_struct->pe_mode_enable = FALSE;
	qspi_cmd_struct->pe_mode_operate_code = 0;
	qspi_cmd_struct->instruction_code = 0x9F;
	qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
	qspi_cmd_struct->address_code = 0;
	qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
	qspi_cmd_struct->data_counter = 3;
	qspi_cmd_struct->second_dummy_cycle_num = 0;
	qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
	qspi_cmd_struct->read_status_config = QSPI_RSTSC_SW_ONCE;
	qspi_cmd_struct->read_status_enable = FALSE;
	qspi_cmd_struct->write_data_enable = FALSE;
}

/**
  * @brief  cmd wrsr config
  * @param  qspi_cmd_struct: the pointer for qspi_cmd_type parameter
  * @retval none
  */
void qspi_cmd_wrsr_config(qspi_cmd_type *qspi_cmd_struct)
{
  qspi_cmd_struct->pe_mode_enable = FALSE;
  qspi_cmd_struct->pe_mode_operate_code = 0;
  qspi_cmd_struct->instruction_code = 0x01;
  qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
  qspi_cmd_struct->address_code = 0;
  qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
  qspi_cmd_struct->data_counter = 1;
  qspi_cmd_struct->second_dummy_cycle_num = 0;
  qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
  qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
  qspi_cmd_struct->read_status_enable = FALSE;
  qspi_cmd_struct->write_data_enable = TRUE;
}
