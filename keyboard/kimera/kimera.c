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
#include "action.h"
#include "i2cmaster.h"
#include "kimera.h"
#include "debug.h"
#include "print.h"

static uint8_t row_mapping[PX_COUNT] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED
};
static uint8_t col_mapping[PX_COUNT] = {
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED
};
static uint8_t row_count = 8;
static uint8_t col_count = 24;
static uint8_t row_left_count = 8;
static uint8_t col_left_count = 24;
static matrix_row_t col_left_mask;
static uint8_t combining = COMBINING_NONE;
static uint8_t data[EXP_COUNT][EXP_PORT_COUNT];
static uint8_t exp_in_use = 3;
static uint8_t exp_online = 0;

static uint8_t read_matrix_mapping(void);
static void write_matrix_mapping(void);
static void expander_init(uint8_t exp);
static uint8_t expander_write(uint8_t exp, uint8_t command, uint8_t *data);
static uint8_t expander_read(uint8_t exp, uint8_t command, uint8_t *data);
static uint8_t expander_write_output(uint8_t exp, uint8_t *data);
static uint8_t expander_write_inversion(uint8_t exp, uint8_t *data);
static uint8_t expander_write_config(uint8_t exp, uint8_t *data);
static uint8_t expander_read_input(uint8_t exp, uint8_t *data);
static void init_data(uint8_t value);

void kimera_init(void)
{
    /* read config */
    //write_matrix_mapping(); /* debug */
    if (read_matrix_mapping()) {
        xprintf("Matrix Mapping Error!\n");
        write_matrix_mapping();
    }

    /* init i/o expanders */
    kimera_scan();
}

uint8_t read_matrix_mapping(void)
{
    uint8_t error = 0;

    /* read number of rows and cols */
    uint8_t rows = eeprom_read_byte(EECONFIG_ROW_COUNT);
    uint8_t cols = eeprom_read_byte(EECONFIG_COL_COUNT);
    if (rows == 0) error++;
    else if (rows == UNCONFIGURED) error++;
    else if (rows & COMBINING_BIT) {
        if (combining != COMBINING_NONE) error++;
        combining = COMBINING_ROW;
        rows -= COMBINING_BIT;
    }
    if (cols == 0) error++;
    else if (cols == UNCONFIGURED) error++;
    else if (cols & COMBINING_BIT) {
        if (combining != COMBINING_NONE) error++;
        combining = COMBINING_COL;
        cols -= COMBINING_BIT;
    }
    if (rows + cols > PX_COUNT) error++;
    if (error) return error;
    row_count = rows;
    col_count = cols;
    if (combining != COMBINING_NONE) {
        row_left_count = (rows + 1) / 2;
        col_left_count = (cols + 1) / 2;
        col_left_mask = (1 << col_left_count) - 1;
    }

    /* read row mapping */
    uint8_t *mapping = EECONFIG_ROW_COL_MAPPING;
    uint8_t exp;
    for (uint8_t i = 0; i < PX_COUNT; i++) {
        if (i < row_count) {
            row_mapping[i] = eeprom_read_byte(mapping++);
            if (row_mapping[i] >= PX_COUNT) {
                error++;
            }
            else {
                exp = PX_TO_EXP(row_mapping[i]);
                exp_in_use |= (1<<exp);
            }
        }
        else {
            row_mapping[i] = UNCONFIGURED;
        }
    }
    /* read col mapping*/
    for (uint8_t i = 0; i < PX_COUNT; i++) {
        if (i < col_count) {
            col_mapping[i] = eeprom_read_byte(mapping++);
            if (col_mapping[i] >= PX_COUNT) {
                error++;
            }
            else {
                exp = PX_TO_EXP(col_mapping[i]);
                exp_in_use |= (1<<exp);
            }
        }
        else {
            col_mapping[i] = UNCONFIGURED;
        }
    }

    return error;
}

void write_matrix_mapping(void)
{
    /* write number of rows and cols */
    eeprom_write_byte(EECONFIG_ROW_COUNT, row_count);
    eeprom_write_byte(EECONFIG_COL_COUNT, col_count);

    /* write row mapping */
    uint8_t *mapping = EECONFIG_ROW_COL_MAPPING;
    for (uint8_t row = 0; row < row_count; row++) {
        eeprom_write_byte(mapping++, row_mapping[row]);
    }
    /* write col mapping */
    for (uint8_t col = 0; col < col_count; col++) {
        eeprom_write_byte(mapping++, col_mapping[col]);
    }
}

void kimera_scan(void)
{
    uint8_t ret;
    for (uint8_t exp = 0; exp < EXP_COUNT; exp++) {
        if (exp_in_use & (1<<exp)) {
            ret = i2c_start(EXP_ADDR(exp) | I2C_WRITE);
            if (ret == 0) {
                i2c_stop();
                if ((exp_online & (1<<exp)) == 0) {
                    xprintf("found: %d\n", exp);
                    exp_online |= (1<<exp);
                    expander_init(exp);
                    clear_keyboard();
                }
            }
            else {
                if ((exp_online & (1<<exp)) != 0) {
                    xprintf("lost: %d\n", exp);
                    exp_online &= ~(1<<exp);
                    clear_keyboard();
                }
            }
        }
    }
    print("Exp in use: "); pbin(exp_in_use); print("\n");
    print("Exp online: "); pbin(exp_online); print("\n");
}

inline
uint8_t kimera_matrix_rows(void)
{
    if (combining == COMBINING_ROW) {
        return row_left_count;
    }
    else {
        return row_count;
    }
}

inline
uint8_t kimera_matrix_cols(void)
{
    if (combining == COMBINING_COL) {
        return col_left_count;
    }
    else {
        return col_count;
    }
}

void kimera_read_cols(void)
{
    /* read all input registers */
    init_data(0xFF);
    for (uint8_t exp = 0; exp < EXP_COUNT; exp++) {
        expander_read_input(exp, data[exp]);
    }
}

uint8_t kimera_get_col(uint8_t row, uint8_t col)
{
    if (combining == COMBINING_ROW) {
        if (row >= row_left_count) {
            col += col_left_count;
        }
    }

    uint8_t px = col_mapping[col];
    if (px != UNCONFIGURED) {
        if (!(data[PX_TO_EXP(px)][PX_TO_PORT(px)] & (1 << PX_TO_PIN(px)))) {
            return 1;
        }
    }
    return 0;
}

matrix_row_t kimera_read_row(uint8_t row)
{
    kimera_read_cols();

    /* make cols */
    matrix_row_t cols = 0;
    for (uint8_t col = 0; col < col_count; col++) {
        uint8_t px = col_mapping[col];
        if (px != UNCONFIGURED) {
            if (!(data[PX_TO_EXP(px)][PX_TO_PORT(px)] & (1 << PX_TO_PIN(px)))) {
                cols |= (1UL << col);
            }
        }
    }

    if (combining == COMBINING_COL) {
        if (row < row_left_count) {
            cols &= col_left_mask;
        }
        else {
            cols >>= col_left_count;
        }
    }

    return cols;
}

void kimera_unselect_rows(void)
{
    /* set all output registers to 0xFF */
    init_data(0xFF);
    for (uint8_t exp = 0; exp < EXP_COUNT; exp++) {
        expander_write_config(exp, data[exp]);
    }
}

void kimera_select_row(uint8_t row)
{
    /* set selected row to low */
    init_data(0xFF);
    uint8_t px = row_mapping[row];
    if (px != UNCONFIGURED) {
        uint8_t exp = PX_TO_EXP(px);
        data[exp][PX_TO_PORT(px)] &= ~(1 << PX_TO_PIN(px));
        expander_write_config(exp, data[exp]);
    }

    if (combining == COMBINING_ROW) {
        if (row < row_left_count) {
            kimera_select_row(row + row_left_count);
        }
    }
}

void expander_init(uint8_t exp)
{
    init_data(0x00);

    /* write inversion register */
    /*
    for (uint8_t exp = 0; exp < EXP_COUNT; exp++) {
        expander_write_inversion(exp, data[exp]);
    }
    */

    /* set output bit */
    /*
    for (uint8_t row = 0; row < row_count; row++) {
        uint8_t px = row_mapping[row];
        if (px != UNCONFIGURED) {
            data[PX_TO_EXP(px)][PX_TO_PORT(px)] &= ~(1 << PX_TO_PIN(px));
        }
    }
    */

    /* write config registers */
    //expander_write_config(exp, data[exp]);

    /* write output registers */
    expander_write_output(exp, data[exp]);
}

uint8_t expander_write(uint8_t exp, uint8_t command, uint8_t *data)
{
    if ((exp_online & (1<<exp)) == 0) {
        return 0;
    }
    uint8_t addr = EXP_ADDR(exp);
    uint8_t ret;
    ret = i2c_start(addr | I2C_WRITE);
    if (ret) goto stop;
    ret = i2c_write(command);
    if (ret) goto stop;
    ret = i2c_write(*data++);
    if (ret) goto stop;
    ret = i2c_write(*data);
stop:
    i2c_stop();
    return ret;
}

uint8_t expander_read(uint8_t exp, uint8_t command, uint8_t *data)
{
    if ((exp_online & (1<<exp)) == 0) {
        return 0;
    }
    uint8_t addr = EXP_ADDR(exp);
    uint8_t ret;
    ret = i2c_start(addr | I2C_WRITE);
    if (ret) goto stop;
    ret = i2c_write(command);
    if (ret) goto stop;
    ret = i2c_rep_start(addr | I2C_READ);
    if (ret) goto stop;
    *data++ = i2c_readAck();
    *data = i2c_readNak();
stop:
    i2c_stop();
    return ret;
}

inline
uint8_t expander_write_output(uint8_t exp, uint8_t *data)
{
    return expander_write(exp, EXP_COMM_OUTPUT_0, data);
}

inline
uint8_t expander_write_inversion(uint8_t exp, uint8_t *data)
{
    return expander_write(exp, EXP_COMM_INVERSION_0, data);
}

inline
uint8_t expander_write_config(uint8_t exp, uint8_t *data)
{
    return expander_write(exp, EXP_COMM_CONFIG_0, data);
}

inline
uint8_t expander_read_input(uint8_t exp, uint8_t *data)
{
    return expander_read(exp, EXP_COMM_INPUT_0, data);
}

void init_data(uint8_t value)
{
    for (uint8_t exp = 0; exp < EXP_COUNT; exp++) {
        for (uint8_t port = 0; port < EXP_PORT_COUNT; port++) {
            data[exp][port] = value;
        }
    }
}
