/*
Copyright 2013,2014 Kai Ryu <kai1103@gmail.com>

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

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdint.h>
#include <stdbool.h>

#if (LED_MATRIX_COLS <= 8)
typedef  uint8_t    led_matrix_row_t;
#elif (LED_MATRIX_COLS <= 16)
typedef  uint16_t   led_matrix_row_t;
#elif (LED_MATRIX_COLS <= 32)
typedef  uint32_t   led_matrix_row_t;
#else
#error "LED_MATRIX_COLS: invalid value"
#endif

typedef struct {
    union {
        int8_t delta;
        struct {
            bool direction:1;
        };
    };
    uint8_t value;
} led_matrix_element_t;

#ifdef LED_MATRIX_ENABLE
void led_matrix_init(void);
void led_matrix_enable(void);
void led_matrix_disable(void);
void led_matrix_init_cols(void);
led_matrix_row_t led_matrix_make_cols(uint8_t row, uint8_t pwm);
void led_matrix_set_value(uint8_t row, uint8_t col, uint8_t value);
void led_matrix_set_delta(uint8_t row, uint8_t col, int8_t delta);
extern void led_matrix_write_cols(led_matrix_row_t cols);
extern void led_matrix_unselect_rows(void);
extern void led_matrix_select_row(uint8_t row);
#else
#define led_matrix_init()
#define led_matrix_enable()
#define led_matrix_disable()
#define led_matrix_init_cols()
#define led_matrix_write_cols()
#define led_matrix_unselect_rows()
#define led_matrix_select_row()
#endif

#endif
