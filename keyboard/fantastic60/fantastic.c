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

#include "fantastic.h"

void shift_register_init(void)
{
    SR_DDR  |=  (1<<SR_CLK_BIT | 1<<SR_DATA_BIT | 1<<SR_LATCH_BIT);
    SR_PORT &= ~(1<<SR_CLK_BIT | 1<<SR_DATA_BIT | 1<<SR_LATCH_BIT);
}

void shift_register_write_byte(uint8_t byte)
{
    uint8_t i = 7;
    do {
        shift_register_data((byte >> i) & 1);
        shift_register_clk();
    } while (i--);
    shift_register_latch();
}

void shift_register_write_word(uint16_t word)
{
    uint8_t i = 15;
    do {
        shift_register_data((word >> i) & 1);
        shift_register_clk();
    } while (i--);
    shift_register_latch();
}

inline
void shift_register_clk(void)
{
    SR_PORT |=  (1<<SR_CLK_BIT);
    SR_PORT &= ~(1<<SR_CLK_BIT);
}

inline
void shift_register_data(uint8_t bit)
{
    if (bit) {
        SR_PORT |=  (1<<SR_DATA_BIT);
    }
    else {
        SR_PORT &= ~(1<<SR_DATA_BIT);
    }
}

inline
void shift_register_latch(void)
{
    SR_PORT &= ~(1<<SR_LATCH_BIT);
    SR_PORT |=  (1<<SR_LATCH_BIT);
}
