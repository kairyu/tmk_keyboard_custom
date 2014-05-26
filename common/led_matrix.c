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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led_matrix.h"

#define LED_MATRIX_TIMER_TOP F_CPU/(256*64)/LED_MATRIX_ROWS

static led_matrix_element_t led_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS];

void led_matrix_init(void)
{
    led_matrix_unselect_rows();
    led_matrix_write_cols(0);
    /* Timer1 setup */
    /* CTC mode */
    TCCR1B |= (1<<WGM12);
    /* Clock selelct: clk/1 */
    TCCR1B |= (1<<CS10);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR1AH = (LED_MATRIX_TIMER_TOP >> 8) & 0xFF;
    OCR1AL = LED_MATRIX_TIMER_TOP & 0xFF;
    SREG = sreg;
}

void led_matrix_enable(void)
{
    /* Enable Compare Match Interrupt */
    TIMSK1 |= _BV(OCIE1A);
}

void led_matrix_disable(void)
{
    /* Disable Compare Match Interrupt */
    TIMSK1 &= ~_BV(OCIE1A);
}

inline 
led_matrix_row_t led_matrix_make_cols(uint8_t row, uint8_t pwm)
{
    led_matrix_row_t cols = 0;
    for (uint8_t i = 0; i < LED_MATRIX_COLS; i++) {
        cols |= ((led_matrix[row][i].value < pwm ? 1 : 0) << i);
    }
    return cols;
}

inline
void led_matrix_set_value(uint8_t row, uint8_t col, uint8_t value)
{
    led_matrix[row][col].value = value;
}

inline
void led_matrix_set_delta(uint8_t row, uint8_t col, int8_t delta)
{
    led_matrix[row][col].delta = delta;
}

ISR(TIMER1_COMPA_vect)
{
    static uint8_t row = 0;
    static uint8_t pwm = 0;

    row = (row + 1) % LED_MATRIX_ROWS;
    pwm++;

    led_matrix_select_row(row);
    _delay_us(10);
    led_matrix_write_cols(led_matrix_make_cols(row, pwm));
    _delay_us(10);
    led_matrix_unselect_rows();
}
