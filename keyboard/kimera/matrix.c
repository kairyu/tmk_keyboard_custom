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
#include "i2c_wrapper.h"
#include "kimera.h"
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
#endif

static uint16_t kimera_scan_timestamp;

inline
uint8_t matrix_rows(void)
{
    return kimera_matrix_rows();
}

inline
uint8_t matrix_cols(void)
{
    return kimera_matrix_cols();
}

void matrix_init(void)
{
    // disable JTAG
    MCUCR = (1<<JTD);
    MCUCR = (1<<JTD);

    i2c_wrapper_init();
    _delay_ms(1);

    kimera_init();
    kimera_scan_timestamp = timer_read();

    // initialize row and col
    kimera_unselect_rows();

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
    i2c_wrapper_task();

    if (timer_elapsed(kimera_scan_timestamp) >= 1000) {
        xprintf("======== 1s task ========\n");
        xprintf("Scan, %u\n", kimera_scan_timestamp);
        kimera_scan_timestamp = timer_read();
        kimera_scan();
        xprintf("=========================\n");
    }

#if IMPROVED_DEBOUNCE
    uint16_t elapsed = timer_elapsed(matrix_row_timestamp[matrix_current_row]);
    if (elapsed >= 1) {
        matrix_row_timestamp[matrix_current_row] = timer_read();
        kimera_select_row(matrix_current_row);
        _delay_us(30);
        kimera_read_cols();
        for (uint8_t i = 0; i < matrix_cols(); i++) {
            uint8_t *debounce = &matrix_debouncing[matrix_current_row][i];
            uint8_t col = kimera_get_col(matrix_current_row, i);
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
        kimera_unselect_rows();
    }

    matrix_current_row++;
    if (matrix_current_row >= matrix_rows()) {
        matrix_current_row = 0;
    }
#else
    for (uint8_t i = 0; i < matrix_rows(); i++) {
        kimera_select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = kimera_read_row(i);
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        kimera_unselect_rows();
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
    print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n");
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
