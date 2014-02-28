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


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;
typedef uint8_t matrix_col_t;

/* matrix state(1:on, 0:off) */
static matrix_col_t matrix[MATRIX_COLS];
static matrix_col_t matrix_debouncing[MATRIX_COLS];

static matrix_col_t read_rows(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);


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
    // initialize row and col
    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        select_col(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_col_t rows = read_rows();
        if (matrix_debouncing[i] != rows) {
            matrix_debouncing[i] = rows;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_cols();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_COLS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
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
    return (matrix[col] & ((matrix_col_t)1<<row));
}

inline
matrix_col_t matrix_get_col(uint8_t col)
{
    return matrix[col];
}

void matrix_print(void)
{
    print("\nc/r 0123456789ABCDEF\n");
    for (uint8_t col = 0; row < MATRIX_COLS; col++) {
        phex(col); print(": ");
        pbin_reverse16(matrix_get_col(col));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Row pin configuration
 * pin: D0  D1  D2  D3  D4  D5  D6
 */
static void  init_rows(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRD  &= ~(1<<PD6 | 1<<PD5 | 1<<PD4 | 1<<PD3 | 1<<PD2 | 1<<PD1 | 1<<PD0);
    PORTD |=  (1<<PD6 | 1<<PD5 | 1<<PD4 | 1<<PD3 | 1<<PD2 | 1<<PD1 | 1<<PD0);
}

/* Row pin configuration
 * col: 0   1   2   3   4   5   6
 * pin: D0  D1  D2  D3  D4  D5  D6
 */
static matrix_col_t read_rows(void)
{
    return PINF & ~(1<<PF7);
}

/* Column pin configuration
 * pin:     F0  B4  E6  F1
 * col: 0    0   0   0   0
 *      1    0   0   0   1
 *      2    0   0   1   0
 *      3    0   0   1   1
 *      4    0   1   0   0
 *      5    0   1   0   1
 *      6    0   1   1   0
 *      7    0   1   1   1
 *      8    1   0   0   0
 *      9    1   0   0   1
 *      10   1   0   1   0
 *      11   1   0   1   1
 *      12   1   1   0   0
 *      13   1   1   0   1
 *      14   1   1   1   0
 *      15   1   1   1   1
 */
static void unselect_cols(void)
{
    // Output low(DDR:1, PORT:0) to unselect
    DDRB  |=  (1<<PB4);
    PORTB &= ~(1<<PB4);
    DDRE  |=  (1<<PE6);
    PORTE &= ~(1<<PE6);
    DDRF  |=  (1<<PF1 | 1<<PF0);
    PORTF &= ~(1<<PF1 | 1<<PF0);
}

static void select_cols(uint8_t col)
{
    if (col & (1<<0)) {
        PORTF |= (1<<PF1);
    }
    else {
        PORTF &= ~(1<<PF1);
    }
    if (col & (1<<1)) {
        PORTE |= (1<<PE6);
    }
    else {
        PORTE &= ~(1<<PE6);
    }
    if (col & (1<<2)) {
        PORTB |= (1<<PB4);
    }
    else {
        PORTB &= ~(1<<PB4);
    }
    if (col & (1<<3)) {
        PORTF |= (1<<PF0);
    }
    else {
        PORTF &= ~(1<<PF0);
    }
}
