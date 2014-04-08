/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

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
    // disable JTAG
    MCUCR = (1<<JTD);
    MCUCR = (1<<JTD);

#ifdef PS2_MOUSE_ENABLE
    // ps2 mouse detect
    DDRF &= ~(1<<PF5 | 1<<PF4);
    PORTF |= (1<<PF5 | 1<<PF4);
    if (PINF & (1<<PF5 | 1 <<PF4)) {
        ps2_mouse_detected = 0;
    }
    else {
        ps2_mouse_detected = 1;
    }
    DDRF |= (1<<PF5 | 1<<PF4);
#endif

    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
#ifdef HYBRID_MATRIX
        init_cols();
#endif
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
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
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
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
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 * pin: F1  F0  E6  D7  D6  D4  C7  C6  B6  B5  B4  B3  B1  B0  (Rev.A)
 * pin: F1  F0  E6  D7  D6  D4  C7  C6  B7  B6  B5  B4  B3  B1  (Rev.B)
 * pin: F1  F0  E6  D7  D6  D4  C7  C6  B7  B5  B4  B3  B1  B0  (Rev.CHN/CNY)
 */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRF  &= ~(1<<PF1 | 1<<PF0);
    PORTF |=  (1<<PF1 | 1<<PF0);
    DDRE  &= ~(1<<PE6);
    PORTE |=  (1<<PE6);
    DDRD  &= ~(1<<PD7 | 1<<PD6 | 1<<PD4);
    PORTD |=  (1<<PD7 | 1<<PD6 | 1<<PD4);
    DDRC  &= ~(1<<PC7 | 1<<PC6);
    PORTC |=  (1<<PC7 | 1<<PC6);
#if defined(GH60_REV_CHN) || defined(GH60_REV_CNY)
    DDRB  &= ~(1<<PB7 | 1<<PB5 | 1<<PB4 | 1<<PB3 | 1<<PB1 | 1<<PB0);
    PORTB |=  (1<<PB7 | 1<<PB5 | 1<<PB4 | 1<<PB3 | 1<<PB1 | 1<<PB0);
#else
    DDRB  &= ~(1<<PB7 | 1<<PB6 | 1<<PB5 | 1<<PB4 | 1<<PB3 | 1<<PB1 | 1<<PB0);
    PORTB |=  (1<<PB7 | 1<<PB6 | 1<<PB5 | 1<<PB4 | 1<<PB3 | 1<<PB1 | 1<<PB0);
#endif
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13
 * pin: F0  F1  E6  C7  C6  B6  D4  B1  B0  B5  B4  D7  D6  B3  (Rev.A)
 * pin: F0  F1  E6  C7  C6  B6  D4  B1  B7  B5  B4  D7  D6  B3  (Rev.B)
 * pin: F0  F1  E6  C7  C6  B7  D4  B1  B0  B5  B4  D7  D6  B3  (Rev.CHN)
 * pin: F0  F1  E6  C7  C6  B7  D4  B0  B1  B5  B4  D7  D6  B3  (Rev.CNY)
 */
static matrix_row_t read_cols(void)
{
#if defined(GH60_REV_CHN)
    return (PINF&(1<<PF0) ? 0 : (1<<0)) |
           (PINF&(1<<PF1) ? 0 : (1<<1)) |
           (PINE&(1<<PE6) ? 0 : (1<<2)) |
           (PINC&(1<<PC7) ? 0 : (1<<3)) |
           (PINC&(1<<PC6) ? 0 : (1<<4)) |
           (PINB&(1<<PB7) ? 0 : (1<<5)) |
           (PIND&(1<<PD4) ? 0 : (1<<6)) |
           (PINB&(1<<PB1) ? 0 : (1<<7)) |
           (PINB&(1<<PB0) ? 0 : (1<<8)) |
           (PINB&(1<<PB5) ? 0 : (1<<9)) |
           (PINB&(1<<PB4) ? 0 : (1<<10)) |
           (PIND&(1<<PD7) ? 0 : (1<<11)) |
           (PIND&(1<<PD6) ? 0 : (1<<12)) |
           (PINB&(1<<PB3) ? 0 : (1<<13));
#elif defined(GH60_REV_CNY)
    return (PINF&(1<<PF0) ? 0 : (1<<0)) |
           (PINF&(1<<PF1) ? 0 : (1<<1)) |
           (PINE&(1<<PE6) ? 0 : (1<<2)) |
           (PINC&(1<<PC7) ? 0 : (1<<3)) |
           (PINC&(1<<PC6) ? 0 : (1<<4)) |
           (PINB&(1<<PB7) ? 0 : (1<<5)) |
           (PIND&(1<<PD4) ? 0 : (1<<6)) |
           (PINB&(1<<PB0) ? 0 : (1<<7)) |
           (PINB&(1<<PB1) ? 0 : (1<<8)) |
           (PINB&(1<<PB5) ? 0 : (1<<9)) |
           (PINB&(1<<PB4) ? 0 : (1<<10)) |
           (PIND&(1<<PD7) ? 0 : (1<<11)) |
           (PIND&(1<<PD6) ? 0 : (1<<12)) |
           (PINB&(1<<PB3) ? 0 : (1<<13));
#else
    return (PINF&(1<<0) ? 0 : (1<<0)) |
           (PINF&(1<<1) ? 0 : (1<<1)) |
           (PINE&(1<<6) ? 0 : (1<<2)) |
           (PINC&(1<<7) ? 0 : (1<<3)) |
           (PINC&(1<<6) ? 0 : (1<<4)) |
           (PINB&(1<<6) ? 0 : (1<<5)) |
           (PIND&(1<<4) ? 0 : (1<<6)) |
           (PINB&(1<<1) ? 0 : (1<<7)) |
           ((PINB&(1<<0) && PINB&(1<<7)) ? 0 : (1<<8)) |     // Rev.A and B
           (PINB&(1<<5) ? 0 : (1<<9)) |
           (PINB&(1<<4) ? 0 : (1<<10)) |
           (PIND&(1<<7) ? 0 : (1<<11)) |
           (PIND&(1<<6) ? 0 : (1<<12)) |
           (PINB&(1<<3) ? 0 : (1<<13));
#endif
}

/* Row pin configuration
 * row: 0   1   2   3   4
 * pin: D0  D1  D2  D3  D5
 */
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRD  &= ~0b00101111;
    PORTD &= ~0b00101111;
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
        case 0:
            DDRD  |= (1<<0);
            PORTD &= ~(1<<0);
            break;
        case 1:
            DDRD  |= (1<<1);
            PORTD &= ~(1<<1);
            break;
        case 2:
            DDRD  |= (1<<2);
            PORTD &= ~(1<<2);
            break;
        case 3:
            DDRD  |= (1<<3);
            PORTD &= ~(1<<3);
            break;
        case 4:
            DDRD  |= (1<<5);
            PORTD &= ~(1<<5);
            break;
    }
}
