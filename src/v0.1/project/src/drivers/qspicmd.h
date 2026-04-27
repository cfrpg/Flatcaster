#ifndef _QSPICMD_H
#define _QSPICMD_H

#include "sys.h"

void qspi_cmd_rdsr_config(qspi_cmd_type *qspi_cmd_struct);
void qspi_cmd_wren_config(qspi_cmd_type *qspi_cmd_struct);
void qspi_cmd_erase_config(qspi_cmd_type *qspi_cmd_struct, uint32_t addr);
void qspi_cmd_write_config(qspi_cmd_type *qspi_cmd_struct, uint32_t addr, uint32_t counter);
void qspi_cmd_read_config(qspi_cmd_type *qspi_cmd_struct, uint32_t addr, uint32_t counter);
void qspi_cmd_en4b_config(qspi_cmd_type *qspi_cmd_struct);
void qspi_cmd_wrsr_config(qspi_cmd_type *qspi_cmd_struct);
void qspi_cmd_rdid_config(qspi_cmd_type *qspi_cmd_struct);
void qspi_cmd_rdsr2_config(qspi_cmd_type *qspi_cmd_struct,u8 cmd);


#endif