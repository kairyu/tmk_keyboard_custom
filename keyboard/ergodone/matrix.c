/*
Copyright 2016 Kai Ryu <kai1103@gmail.com>

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
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "expander.h"
#include "keymap_in_eeprom.h"
#include "timer.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

#define IMPROVED_DEBOUNCE 1

#if IMPROVED_DEBOUNCE
#define DEBOUNCE_MASK ((1 << DEBOUNCE) - 1)
static uint8_t matrix_current_row;
static uint16_t matrix_row_timestamp[MATRIX_ROWS];
static uint8_t matrix_debouncing[MATRIX_ROWS][MATRIX_COLS];
#else
static uint8_t debouncing = DEBOUNCE;
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static matrix_row_t read_row(void);
#endif

static uint16_t matrix_scan_timestamp;

static void read_cols(void);
static uint8_t get_col(uint8_t col);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

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

    timer_init();
    _delay_ms(1);

    matrix_scan_timestamp = timer_read();

    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
#if IMPROVED_DEBOUNCE
    for (uint8_t i = 0; i < matrix_rows(); i++) {
        matrix[i] = 0;
        matrix_current_row = 0;
        matrix_row_timestamp[i] = timer_read();
        for (uint8_t j = 0; j < matrix_cols(); j++) {
            matrix_debouncing[i][j] = 0;
        }
    }
#else
    for (uint8_t i=0; i < matrix_rows(); i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
#endif
}

uint8_t matrix_scan(void)
{
    if (timer_elapsed(matrix_scan_timestamp) >= 1000) {
        dprintf("======== 1s task ========\n");
        dprintf("Scan: %u\n", matrix_scan_timestamp);
        matrix_scan_timestamp = timer_read();
        expander_scan();
        dprintf("=========================\n");
    }

#if IMPROVED_DEBOUNCE
    uint16_t elapsed = timer_elapsed(matrix_row_timestamp[matrix_current_row]);
    if (elapsed >= 1) {
        matrix_row_timestamp[matrix_current_row] = timer_read();
        select_row(matrix_current_row);
        _delay_us(30);
        read_cols();
        for (uint8_t i = 0; i < matrix_cols(); i++) {
            uint8_t *debounce = &matrix_debouncing[matrix_current_row][i];
            uint8_t col = get_col(i);
            uint8_t count = elapsed;
            do {
                *debounce <<= 1;
                *debounce |= col;
            } while (--count);
            matrix_row_t *row = &matrix[matrix_current_row];
            matrix_row_t mask = ((matrix_row_t)1 << i);
            switch (*debounce & DEBOUNCE_MASK) {
                case DEBOUNCE_MASK:
#if DEBOUNCE > 1
                case (DEBOUNCE_MASK >> 1):
#if DEBOUNCE > 2
                case (DEBOUNCE_MASK >> 2):
#if DEBOUNCE > 3
                case (DEBOUNCE_MASK >> 3):
#if DEBOUNCE > 4
                case (DEBOUNCE_MASK >> 4):
#if DEBOUNCE > 5
                case (DEBOUNCE_MASK >> 5):
#if DEBOUNCE > 6
                case (DEBOUNCE_MASK >> 6):
#if DEBOUNCE > 7
                case (DEBOUNCE_MASK >> 7):
#if DEBOUNCE > 8
                case (DEBOUNCE_MASK >> 8):
#if DEBOUNCE > 9
                case (DEBOUNCE_MASK >> 9):
#if DEBOUNCE > 10
                case (DEBOUNCE_MASK >> 10):
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
                    if ((*row & mask) == 0) {
                        *row |= mask;
                    }
                    break;
#if DEBOUNCE > 1
                case ((DEBOUNCE_MASK << 1) & DEBOUNCE_MASK):
#if DEBOUNCE > 2
                case ((DEBOUNCE_MASK << 2) & DEBOUNCE_MASK):
#if DEBOUNCE > 3
                case ((DEBOUNCE_MASK << 3) & DEBOUNCE_MASK):
#if DEBOUNCE > 4
                case ((DEBOUNCE_MASK << 4) & DEBOUNCE_MASK):
#if DEBOUNCE > 5
                case ((DEBOUNCE_MASK << 5) & DEBOUNCE_MASK):
#if DEBOUNCE > 6
                case ((DEBOUNCE_MASK << 6) & DEBOUNCE_MASK):
#if DEBOUNCE > 7
                case ((DEBOUNCE_MASK << 7) & DEBOUNCE_MASK):
#if DEBOUNCE > 8
                case ((DEBOUNCE_MASK << 8) & DEBOUNCE_MASK):
#if DEBOUNCE > 9
                case ((DEBOUNCE_MASK << 9) & DEBOUNCE_MASK):
#if DEBOUNCE > 10
                case ((DEBOUNCE_MASK << 10) & DEBOUNCE_MASK):
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
                    break;
                case 0:
                    if ((*row & mask) != 0) {
                        *row &= ~mask;
                    }
                    break;
                default:
                    debug("bounce!: ");
                    debug_bin8(*debounce & DEBOUNCE_MASK);
                    debug("\n");
                    break;
            }
        }
        unselect_rows();
    }

    matrix_current_row++;
    if (matrix_current_row >= matrix_rows()) {
        matrix_current_row = 0;
    }
#else
    for (uint8_t i = 0; i < matrix_rows(); i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_row();
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
            for (uint8_t i = 0; i < matrix_rows(); i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
#endif

    return 1;
}

#if IMPROVED_DEBOUNCE
#else
bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}
#endif

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
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        print_bin_reverse32(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < matrix_rows(); i++) {
        count += bitpop32(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13
 * pin: EX  EX  EX  EX  EX  EX  EX  D3  D2  D4  C6  D7  E6  B4
 */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRE  &= ~(1<<PE6);
    PORTE |=  (1<<PE6);
    DDRD  &= ~(1<<PD2 | 1<<PD3 | 1<<PD4 | 1<<PD7);
    PORTD |=  (1<<PD2 | 1<<PD3 | 1<<PD4 | 1<<PD7);
    DDRC  &= ~(1<<PC6);
    PORTC |=  (1<<PC6);
    DDRB  &= ~(1<<PB4);
    PORTB |=  (1<<PB4);
    // Init I/O expander
    expander_init();
}

#if !IMPROVED_DEBOUNCE
static matrix_row_t read_row(void)
{
    return expander_read_row() |
           (PIND&(1<<PD3) ? 0 : (1<<7)) |
           (PIND&(1<<PD2) ? 0 : (1<<8)) |
           (PIND&(1<<PD4) ? 0 : (1<<9)) |
           (PINC&(1<<PC6) ? 0 : (1<<10)) |
           (PIND&(1<<PD7) ? 0 : (1<<11)) |
           (PINE&(1<<PE6) ? 0 : (1<<12)) |
           (PINB&(1<<PB4) ? 0 : (1<<13));
}
#endif

static void read_cols(void)
{
    expander_read_cols();
}

static uint8_t get_col(uint8_t col)
{
    switch (col) {
#ifdef VER_PROTOTYPE
        case 0 ... 6:
            return expander_get_col(col);
        case 7:
            return PIND&(1<<PD3) ? 0 : 1;
        case 8:
            return PIND&(1<<PD2) ? 0 : 1;
        case 9:
            return PIND&(1<<PD4) ? 0 : 1;
        case 10:
            return PINC&(1<<PC6) ? 0 : 1;
        case 11:
            return PIND&(1<<PD7) ? 0 : 1;
        case 12:
            return PINE&(1<<PE6) ? 0 : 1;
        case 13:
            return PINB&(1<<PB4) ? 0 : 1;
#else
        case 0:
            return PINB&(1<<PB4) ? 0 : 1;
        case 1:
            return PINE&(1<<PE6) ? 0 : 1;
        case 2:
            return PIND&(1<<PD7) ? 0 : 1;
        case 3:
            return PINC&(1<<PC6) ? 0 : 1;
        case 4:
            return PIND&(1<<PD4) ? 0 : 1;
        case 5:
            return PIND&(1<<PD2) ? 0 : 1;
        case 6:
            return PIND&(1<<PD3) ? 0 : 1;
        case 7 ... 13:
            return expander_get_col(13 - col);
#endif
        default:
            return 0;
    }
}

/* Row pin configuration
 * row: 0   1   2   3   4   5
 * pin: F4  F5  F6  F7  B1  B2
 */
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRF  &= ~(1<<PF4 | 1<<PF5 | 1<<PF6 | 1<<PF7);
    PORTF &= ~(1<<PF4 | 1<<PF5 | 1<<PF6 | 1<<PF7);
    DDRB  &= ~(1<<PB1 | 1<<PB2);
    PORTB &= ~(1<<PB1 | 1<<PB2);
    // I/O expander
    expander_unselect_rows();
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
        case 0:
            DDRF  |=  (1<<PF4);
            PORTF &= ~(1<<PF4);
            break;
        case 1:
            DDRF  |=  (1<<PF5);
            PORTF &= ~(1<<PF5);
            break;
        case 2:
            DDRF  |=  (1<<PF6);
            PORTF &= ~(1<<PF6);
            break;
        case 3:
            DDRF  |=  (1<<PF7);
            PORTF &= ~(1<<PF7);
            break;
        case 4:
            DDRB  |=  (1<<PB1);
            PORTB &= ~(1<<PB1);
            break;
        case 5:
            DDRB  |=  (1<<PB2);
            PORTB &= ~(1<<PB2);
            break;
    }
    // I/O expander
    expander_select_row(row);
}
