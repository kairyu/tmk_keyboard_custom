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

typedef struct {
    union {
        int8_t delta;
        struct {
            bool direction:1;
        }
    }
    uint8_t value;
} led_matrix_element_t;

uint8_t led_matrix_rows(void);
uint8_t led_matrix_cols(void);
void led_matrix_init(void);
void led_matrix_enable(void);
void led_matrix_disable(void);
uint8_t led_matrix_scan(void);

#endif
