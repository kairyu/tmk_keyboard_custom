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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#ifdef PS2_MOUSE_ENABLE
#include "ps2.h"
#endif


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix;
static matrix_row_t matrix_debouncing;

static matrix_row_t read_cols(void);
static void init_cols(void);

#ifdef PS2_MOUSE_ENABLE
static uint8_t ps2_mouse_detected;

uint8_t ps2_enabled(void)
{
    return ps2_mouse_detected;
}
#endif

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
#ifdef PS2_MOUSE_ENABLE
    // ps2 mouse detect
    DDRC &= ~(1<<PC2);
    PORTC |= (1<<PC2);
    if (PINC & (1<<PC2)) {
        ps2_mouse_detected = 0;
    }
    else {
        ps2_mouse_detected = 1;
    }
    PORTC &= ~(1<<PC2);
#endif

    // initialize cols
    init_cols();

    // initialize matrix state: all keys off
    matrix = 0;
    matrix_debouncing = 0;
}

uint8_t matrix_scan(void)
{
    matrix_row_t cols = read_cols();
    if (matrix_debouncing != cols) {
        matrix_debouncing = cols;
        if (debouncing) {
            debug("bounce!: "); debug_hex(debouncing); debug("\n");
        }
        debouncing = DEBOUNCE;
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            matrix = matrix_debouncing;
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix;
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    return bitpop16(matrix);
}

/* Column pin configuration
 * col: 0   1   2   3   4
 * pin: D1  D2  D5  D6  B3
 */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRD  &= ~(1<<PD1 | 1<<PD2 | 1<<PD5 | 1<<PD6);
    PORTD |=  (1<<PD1 | 1<<PD2 | 1<<PD5 | 1<<PD6);
    DDRB  &= ~(1<<PB3);
    PORTB |=  (1<<PB3);
}

/* Column pin configuration
 * col: 0   1   2   3   4
 * pin: D1  D2  D5  D6  B3
 */
static matrix_row_t read_cols(void)
{
    return (PIND&(1<<PD1) ? 0 : (1<<0)) |
           (PIND&(1<<PD2) ? 0 : (1<<1)) |
           (PIND&(1<<PD5) ? 0 : (1<<2)) |
           (PIND&(1<<PD6) ? 0 : (1<<3)) |
           (PINB&(1<<PB3) ? 0 : (1<<4));
}
