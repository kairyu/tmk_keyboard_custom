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

#define KIMERA_C

#include <stdbool.h>
#include <avr/eeprom.h>
#include "kimera.h"

uint8_t mux_mapping[MUX_COUNT] = {
    MUX_FOR_ROW, MUX_FOR_COL, MUX_FOR_COL, MUX_FOR_COL
};
uint8_t row_mapping[MATRIX_ROWS] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED
};
uint8_t col_mapping[MATRIX_COLS] = {
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31
};
uint8_t row_max_count = MUX_PORTS * 1;
uint8_t col_max_count = MUX_PORTS * (MUX_COUNT - 1);
uint16_t shift_out_cache = 0;

void kimera_init(void)
{
    // read config
    if (read_matrix_mapping()) {
        write_matrix_mapping();
    }

    // init shift out pins
    MOSI_DDR |= (1<<MOSI_BIT);
    SCK_DDR  |= (1<<SCK_BIT);
    RCK_DDR  |= (1<<RCK_BIT);
    RCK_PORT |= (1<<RCK_BIT);

    // init spi
    SPCR |= ((1<<SPE) | (1<<MSTR));
    SPSR |= ((1<<SPI2X));
}

uint8_t read_matrix_mapping(void)
{
    uint8_t error = 0;
    uint8_t mux_config = 0;
    row_max_count = 0;
    col_max_count = 0;

    mux_config = eeprom_read_byte(EECONFIG_MUX_MAPPING);
    if (mux_config & (1<<7)) {
        error++;
        return error;
    }

    for (uint8_t i = 0; i < MUX_COUNT; i++) {
        mux_mapping[i] = mux_config & (1<<i);
        if (mux_mapping[i] == MUX_FOR_COL) {
            col_max_count += MUX_PORTS;
        }
        else {
            row_max_count += MUX_PORTS;
        }
    }
    if ((col_max_count == 0) || (row_max_count == 0)) {
        error++;
    }

    uint8_t *mapping = EECONFIG_ROW_COL_MAPPING;
    for (uint8_t i = 0; i < row_max_count; i++) {
        row_mapping[i] = eeprom_read_byte(mapping++);
        if (row_mapping[i] != UNCONFIGURED) {
            if (mux_mapping[PX_TO_MUX(row_mapping[i])] != MUX_FOR_ROW) {
                row_mapping[i] = UNCONFIGURED;
                error++;
            }
        }
    }
    for (uint8_t i = 0; i < col_max_count; i++) {
        col_mapping[i] = eeprom_read_byte(mapping++);
        if (col_mapping[i] != UNCONFIGURED) {
            if (mux_mapping[PX_TO_MUX(col_mapping[i])] != MUX_FOR_COL) {
                col_mapping[i] = UNCONFIGURED;
                error++;
            }
        }
    }

    return error;
}

void write_matrix_mapping(void)
{
    uint8_t mux_config = 0;
    row_max_count = 0;
    col_max_count = 0;

    for (uint8_t i = 0; i < MUX_COUNT; i++) {
        mux_config |= (mux_mapping[i] << i);
        if (mux_mapping[i] == MUX_FOR_COL) {
            col_max_count += MUX_PORTS;
        }
        else {
            row_max_count += MUX_PORTS;
        }
    }
    eeprom_write_byte(EECONFIG_MUX_MAPPING, mux_config);

    uint8_t *mapping = EECONFIG_ROW_COL_MAPPING;
    for (uint8_t i = 0; i < row_max_count; i++) {
        eeprom_write_byte(mapping++, row_mapping[i]);
    }
    for (uint8_t i = 0; i < col_max_count; i++) {
        eeprom_write_byte(mapping++, col_mapping[i]);
    }
}

void shift_out_word(uint16_t data)
{
    SPDR = (data & 0xFF);
    while (!(SPSR & (1<<SPIF)));
    SPDR = ((data>>8) & 0xFF);
    while (!(SPSR & (1<<SPIF)));
    RCK_PORT &= ~(1<<RCK_BIT);
    RCK_PORT |=  (1<<RCK_BIT);
}

void  init_cols(void)
{
    // init mux io pins
    for (uint8_t i = 0; i < MUX_COUNT; i++) {
        if (mux_mapping[i] == MUX_FOR_COL) {
            ZX_DDR  &= ~(1 << zx_bit[i]);
            ZX_PORT |=  (1 << zx_bit[i]);
        }
        else {
            ZX_DDR  |=  (1 << zx_bit[i]);
            ZX_PORT |=  (1 << zx_bit[i]);
        }
    }
}

matrix_row_t read_cols(void)
{
    matrix_row_t cols = 0;
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        uint8_t px = col_mapping[i];
        if (px != UNCONFIGURED) {
            shift_out_word(shift_out_cache | px_to_shift_out[px]);
            // TODO: delay
            if (!(ZX_PIN & (1 << zx_bit[PX_TO_MUX(px)]))) {
                cols |= (1 << i);
            }
        }
    }
    return cols;
}

void unselect_rows(void)
{
    shift_out_word(0);
}

void select_row(uint8_t row)
{
    uint8_t px = row_mapping[row];
    if (px != UNCONFIGURED) {
        ZX_PORT &= ~(1 << zx_bit[PX_TO_MUX(px)]);
        shift_out_cache = px_to_shift_out[px] | mux_inh_to_shift_out[PX_TO_MUX(px)];
        shift_out_word(shift_out_cache);
    }
}
