/*
Copyright 2014 Kai Ryu <kai1103@gmail.com>

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

#ifndef FANTASTIC_H
#define FANTASTIC_H

#include <avr/io.h>
#include <stdint.h>

#define SR_PORT         PORTF
#define SR_DDR          DDRF
#define SR_CLK_BIT      PF6
#define SR_DATA_BIT     PF5
#define SR_LATCH_BIT    PF4

void shift_register_init(void);
void shift_register_write_byte(uint8_t byte);
void shift_register_write_word(uint16_t word);
void shift_register_clk(void);
void shift_register_data(uint8_t bit);
void shift_register_latch(void);

#endif
