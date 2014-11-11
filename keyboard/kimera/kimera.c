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
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "action.h"
#include "suspend.h"
#include "i2cmaster.h"
#include "kimera.h"
#include "debug.h"

#define SCL_CLOCK       400000L
#define SCL_DURATION    (1000000L/SCL_CLOCK)/2
extern uint8_t i2c_force_stop;

uint8_t row_mapping[PX_COUNT] = {
#ifndef TWO_HEADED_KIMERA
    0, 1, 2, 3, 4, 5, 6, 7,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED
#else
    0, 1, 2, 3, 4, 5, 6, 7,
    32, 33, 34, 35, 36, 37, 38, 39,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED
#endif
};
uint8_t col_mapping[PX_COUNT] = {
#ifndef TWO_HEADED_KIMERA
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31,
    UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED, UNCONFIGURED
#else
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55
#endif
};
#ifndef TWO_HEADED_KIMERA
uint8_t row_count = 8;
uint8_t col_count = 24;
#else
uint8_t row_count = 16;
uint8_t col_count = 32;
#endif
uint8_t data[EXP_COUNT][EXP_PORT_COUNT];
uint8_t exp_status = 0;

void kimera_init(void)
{
    /* read config */
    //write_matrix_mapping(); /* debug */
    if (read_matrix_mapping()) {
        write_matrix_mapping();
    }

    /* init i2c */
    i2c_init();

    /* init watch dog */
    wdt_init();

    /* init i/o expanders */
    kimera_scan();
}

void wdt_init(void)
{
    cli();
    wdt_reset();
    wdt_intr_enable(WDTO_1S);
    sei();
}

uint8_t read_matrix_mapping(void)
{
    uint8_t error = 0;

    /* read number of rows and cols */
    uint8_t rows = eeprom_read_byte(EECONFIG_ROW_COUNT);
    uint8_t cols = eeprom_read_byte(EECONFIG_COL_COUNT);
    if (rows == 0) error++;
    if (rows == UNCONFIGURED) error++;
    if (cols == 0) error++;
    if (cols == UNCONFIGURED) error++;
    if (rows + cols > PX_COUNT) error++;
    if (error) return error;
    row_count = rows;
    col_count = cols;

    /* read row mapping */
    uint8_t *mapping = EECONFIG_ROW_COL_MAPPING;
    for (uint8_t i = 0; i < PX_COUNT; i++) {
        if (i < row_count) {
            row_mapping[i] = eeprom_read_byte(mapping++);
            if (row_mapping[i] >= PX_COUNT) error++;
        }
        else {
            row_mapping[i] = UNCONFIGURED;
        }
    }
    /* read col mapping*/
    for (uint8_t i = 0; i < PX_COUNT; i++) {
        if (i < col_count) {
            col_mapping[i] = eeprom_read_byte(mapping++);
            if (col_mapping[i] >= PX_COUNT) error++;
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
    wdt_reset();
    uint8_t ret;
    for (uint8_t exp = 0; exp < EXP_COUNT; exp++) {
        ret = i2c_start(EXP_ADDR(exp) | I2C_READ);
        if (exp_status & (1<<exp)) {
            if (ret) {
                dprintf("lost: %d\n", exp);
                exp_status &= ~(1<<exp);
                clear_keyboard();
            }
        }
        else {
            if (!ret) {
                dprintf("found: %d\n", exp);
                exp_status |= (1<<exp);
                i2c_stop();
                expander_init(exp);
                clear_keyboard();
            }
        }
    }
}

matrix_row_t read_cols(void)
{
    init_data(0xFF);

    /* read all input registers */
    for (uint8_t exp = 0; exp < EXP_COUNT; exp++) {
        expander_read_input(exp, data[exp]);
    }

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
    return cols;
}

void unselect_rows(void)
{
    /* set all output registers to 0xFF */
    init_data(0xFF);
    for (uint8_t exp = 0; exp < EXP_COUNT; exp++) {
        expander_write_config(exp, data[exp]);
    }
}

void select_row(uint8_t row)
{
    /* set selected row to low */
    init_data(0xFF);
    uint8_t px = row_mapping[row];
    if (px != UNCONFIGURED) {
        uint8_t exp = PX_TO_EXP(px);
        data[exp][PX_TO_PORT(px)] &= ~(1 << PX_TO_PIN(px));
        expander_write_config(exp, data[exp]);
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
    wdt_reset();
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
    wdt_reset();
    uint8_t addr = EXP_ADDR(exp);
    uint8_t ret;
    ret = i2c_start(addr | I2C_WRITE);
    if (ret) goto stop;
    ret = i2c_write(command);
    if (ret) goto stop;
    ret = i2c_start(addr | I2C_READ);
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

ISR(WDT_vect)
{
    dprintf("i2c timeout\n");

    /* let slave to release SDA */
    TWCR = 0;
    DDRD |=  (1<<PD0);
    DDRD &= ~(1<<PD1);
    if (!(PIND & (1<<PD1))) {
        for (uint8_t i = 0; i < 9; i++) {
            PORTD &= ~(1<<PD0);
            _delay_us(SCL_DURATION);
            PORTD |= (1<<PD0);
            _delay_us(SCL_DURATION);
        }
    }

    /* send stop condition */
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

    /* escape from loop */
    i2c_force_stop = 1;
}
