/*
Copyright 2016 Kai Ryu <kai1103@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EXPANDER_H
#define EXPANDER_H

#include <stdint.h>
#include "matrix.h"

#define MCP23017
#define MCP23017_A0 0
#define MCP23017_A1 0
#define MCP23017_A2 0

#ifdef MCP23017
#define EXPANDER_ADDR ((0x20|(MCP23017_A0<<0)|(MCP23017_A1<<1)|(MCP23017_A2<<2)) << 1)
enum EXPANDER_REG_BANK0 {
    EXPANDER_REG_IODIRA = 0,
    EXPANDER_REG_IODIRB,
    EXPANDER_REG_IPOLA,
    EXPANDER_REG_IPOLB,
    EXPANDER_REG_GPINTENA,
    EXPANDER_REG_GPINTENB,
    EXPANDER_REG_DEFVALA,
    EXPANDER_REG_DEFVALB,
    EXPANDER_REG_INTCONA,
    EXPANDER_REG_INTCONB,
    EXPANDER_REG_IOCONA,
    EXPANDER_REG_IOCONB,
    EXPANDER_REG_GPPUA,
    EXPANDER_REG_GPPUB,
    EXPANDER_REG_INTFA,
    EXPANDER_REG_INTFB,
    EXPANDER_REG_INTCAPA,
    EXPANDER_REG_INTCAPB,
    EXPANDER_REG_GPIOA,
    EXPANDER_REG_GPIOB,
    EXPANDER_REG_OLATA,
    EXPANDER_REG_OLATB
};
#endif

void expander_init(void);
void expander_scan(void);
void expander_read_cols(void);
uint8_t expander_get_col(uint8_t col);
matrix_row_t expander_read_row(void);
void expander_unselect_rows(void);
void expander_select_row(uint8_t row);

#endif
