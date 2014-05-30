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
#include <util/delay.h>
#include "kimera.h"
#include "debug.h"

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
    write_matrix_mapping();
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
    if (mux_config == 0 || (mux_config & (1<<7))) {
        error++;
        return error;
    }

    for (uint8_t mux = 0; mux < MUX_COUNT; mux++) {
        mux_mapping[mux] = mux_config & (1 << mux);
        if (mux_mapping[mux] == MUX_FOR_COL) {
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
    for (uint8_t row = 0; row < row_max_count; row++) {
        row_mapping[row] = eeprom_read_byte(mapping++);
        if (row_mapping[row] != UNCONFIGURED) {
            if (mux_mapping[PX_TO_MUX(row_mapping[row])] != MUX_FOR_ROW) {
                row_mapping[row] = UNCONFIGURED;
                error++;
            }
        }
    }
    for (uint8_t col = 0; col < col_max_count; col++) {
        col_mapping[col] = eeprom_read_byte(mapping++);
        if (col_mapping[col] != UNCONFIGURED) {
            if (mux_mapping[PX_TO_MUX(col_mapping[col])] != MUX_FOR_COL) {
                col_mapping[col] = UNCONFIGURED;
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

    for (uint8_t mux = 0; mux < MUX_COUNT; mux++) {
        mux_config |= (mux_mapping[mux] << mux);
        if (mux_mapping[mux] == MUX_FOR_COL) {
            col_max_count += MUX_PORTS;
        }
        else {
            row_max_count += MUX_PORTS;
        }
    }
    eeprom_write_byte(EECONFIG_MUX_MAPPING, mux_config);

    uint8_t *mapping = EECONFIG_ROW_COL_MAPPING;
    for (uint8_t row = 0; row < row_max_count; row++) {
        eeprom_write_byte(mapping++, row_mapping[row]);
    }
    for (uint8_t col = 0; col < col_max_count; col++) {
        eeprom_write_byte(mapping++, col_mapping[col]);
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
    for (uint8_t mux = 0; mux < MUX_COUNT; mux++) {
        uint8_t bit = MUX_TO_ZX_BIT(mux);
        if (mux_mapping[mux] == MUX_FOR_COL) {
            ZX_DDR  &= ~(1 << bit);
            ZX_PORT |=  (1 << bit);
        }
        else {
            ZX_DDR  |=  (1 << bit);
            ZX_PORT |=  (1 << bit);
        }
    }
}

matrix_row_t read_cols(void)
{
    matrix_row_t cols = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        uint8_t px = col_mapping[col];
        if (px != UNCONFIGURED) {
            shift_out_word(shift_out_cache | PX_TO_SHIFT_OUT(px));
            _delay_us(10);
            if (!(ZX_PIN & (1 << MUX_TO_ZX_BIT(PX_TO_MUX(px))))) {
                cols |= (1 << col);
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
        ZX_PORT &= ~(1 << MUX_TO_ZX_BIT(PX_TO_MUX(row)));
        shift_out_cache = PX_TO_SHIFT_OUT(px) | MUX_INH_TO_SHIFT_OUT(PX_TO_MUX(px));
        shift_out_word(shift_out_cache);
    }
}
