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
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#ifdef PS2_MOUSE_ENABLE
#include "ps2.h"
#endif
#include "vibration.h"
#include "buzzer.h"
#include "keymap_common.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix = 0;
static matrix_row_t matrix_debouncing = 0;
static matrix_row_t debouncing = 0;
static uint16_t debouncing_last[MATRIX_COLS];

static matrix_row_t read_cols(void);
static void init_cols(void);

#ifdef PS2_MOUSE_ENABLE
uint8_t ps2_mouse_enabled;
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
    DDRD &= ~(1<<PD3);
    PORTD |= (1<<PD3);
    _delay_us(30);
    if (PIND & (1<<PD3)) {
        ps2_mouse_enabled = 0;
    }
    else {
        ps2_mouse_enabled = 1;
    }
    PORTD &= ~(1<<PD3);
#endif

    keymaps_cache_init();

    vibration_init();
    buzzer_init();

    // initialize cols
    init_cols();
}

uint8_t matrix_scan(void)
{
    matrix_row_t cols = read_cols();
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        if (debouncing & (1<<col)) {
            if (timer_elapsed(debouncing_last[col]) > DEBOUNCE) {
                debouncing &= ~(1<<col);
                if (!(cols & (1<<col))) {
                    matrix &= ~(1<<col);
                }
            }
        }
        if ((cols & (1<<col)) != (matrix_debouncing & (1<<col))) {
            if (!(debouncing & (1<<col)) && (cols & (1<<col))) {
                matrix |= (1<<col);
            }
            else {
                debouncing_last[col] = timer_read();
                debouncing |= (1<<col);
            }
        }
    }
    matrix_debouncing = cols;

    /*
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
    */

    vibration_task();

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
 * pin: B0  B1  B2  B3  B4
 */
static void  init_cols(void)
{
#ifndef EXPERIMENTAL
    // Input with pull-up(DDR:0, PORT:1)
    /*
    DDRD  &= ~(1<<PD1 | 1<<PD2 | 1<<PD5 | 1<<PD6);
    PORTD |=  (1<<PD1 | 1<<PD2 | 1<<PD5 | 1<<PD6);
    DDRB  &= ~(1<<PB3);
    PORTB |=  (1<<PB3);
    */
    DDRB  &= ~(1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3 | 1<<PB4);
    PORTB |=  (1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3 | 1<<PB4);
    DDRB  |=  (1<<PB5);
    PORTB |=  (1<<PB5);
#else
    DDRD  |=  (1<<PD3);
    PORTD &= ~(1<<PD3);
    DDRE  &= ~(1<<PE6);
    PORTE |=  (1<<PE6);
    DDRC  &= ~(1<<PC7 | 1<<PC6);
    PORTC |=  (1<<PC7 | 1<<PC6);
    DDRB  &= ~(1<<PB7);
    PORTB |=  (1<<PB7);
    DDRD  &= ~(1<<PD4);
    PORTD |=  (1<<PD4);
#endif
}

/* Column pin configuration
 * col: 0   1   2   3   4
 * pin: B0  B1  B2  B3  B4
 */
static matrix_row_t read_cols(void)
{
#ifndef EXPERIMENTAL
    /*
    return (PIND&(1<<PD1) ? 0 : (1<<0)) |
           (PIND&(1<<PD2) ? 0 : (1<<1)) |
           (PIND&(1<<PD5) ? 0 : (1<<2)) |
           (PIND&(1<<PD6) ? 0 : (1<<3)) |
           (PINB&(1<<PB3) ? 0 : (1<<4));
    */
    /*
    return (PINB&(1<<PB0) ? 0 : (1<<0)) |
           (PINB&(1<<PB1) ? 0 : (1<<1)) |
           (PINB&(1<<PB3) ? 0 : (1<<2)) |
           (PINB&(1<<PB2) ? 0 : (1<<3)) |
           (PINB&(1<<PB4) ? 0 : (1<<4));
   */
    return (~PINB) & 0b00011111;
#else
    return (PINE&(1<<PE6) ? 0 : (1<<0)) |
           (PINC&(1<<PC7) ? 0 : (1<<1)) |
           (PINC&(1<<PC6) ? 0 : (1<<2)) |
           (PINB&(1<<PB7) ? 0 : (1<<3)) |
           (PIND&(1<<PD4) ? 0 : (1<<4));
#endif
}
