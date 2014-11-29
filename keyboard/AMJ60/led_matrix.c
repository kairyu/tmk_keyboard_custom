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
#include "led_matrix.h"

#ifdef LED_MATRIX_ENABLE
#if defined(GH60_REV_CNY)

/* LED Column pin configuration
 * pin: F0  F1  E6  C7  C6  B7  D4  B0  B1  B5  B4  D7  D6  B3  (Rev.CNY)
 */
void led_matrix_write_cols(led_matrix_row_t cols)
{
    (cols & (1<<0))  ? (PORTF |= (1<<PF0)) : (PORTF &= ~(1<<PF0));
    (cols & (1<<1))  ? (PORTF |= (1<<PF1)) : (PORTF &= ~(1<<PF1));
    (cols & (1<<2))  ? (PORTE |= (1<<PE6)) : (PORTE &= ~(1<<PE6));
    (cols & (1<<3))  ? (PORTC |= (1<<PC7)) : (PORTC &= ~(1<<PC7));
    (cols & (1<<4))  ? (PORTC |= (1<<PC6)) : (PORTC &= ~(1<<PC6));
    (cols & (1<<5))  ? (PORTB |= (1<<PB7)) : (PORTB &= ~(1<<PB7));
    (cols & (1<<6))  ? (PORTD |= (1<<PD4)) : (PORTD &= ~(1<<PD4));
    (cols & (1<<7))  ? (PORTB |= (1<<PB0)) : (PORTB &= ~(1<<PB0));
    (cols & (1<<8))  ? (PORTB |= (1<<PB1)) : (PORTB &= ~(1<<PB1));
    (cols & (1<<9))  ? (PORTB |= (1<<PB5)) : (PORTB &= ~(1<<PB5));
    (cols & (1<<10)) ? (PORTB |= (1<<PB4)) : (PORTB &= ~(1<<PB4));
    (cols & (1<<11)) ? (PORTD |= (1<<PD7)) : (PORTD &= ~(1<<PD7));
    (cols & (1<<12)) ? (PORTD |= (1<<PD6)) : (PORTD &= ~(1<<PD6));
    (cols & (1<<13)) ? (PORTB |= (1<<PB3)) : (PORTB &= ~(1<<PB3));
}

/* LED Row pin configuration
 * row: 0   1   2   3   4   5
 * pin: B6  F5  F6  F7  F4  B2
 */
void led_matrix_unselect_rows(void)
{
    // unselect key matrix rows
    //DDRD  &= ~0b00101111;
    //PORTD &= ~0b00101111;

    //      bit 76543210
    DDRB  &= ~0b01000100;
    PORTB &= ~0b01000100;
    //      bit 76543210
    DDRF  &= ~0b11110000;
    PORTF &= ~0b11110000;
}

/* LED Row pin configuration
 * row: 0   1   2   3   4   5
 * pin: B6  F5  F6  F7  F4  B2
 */
void led_matrix_select_row(uint8_t row)
{
    switch (row) {
        case 0:
            DDRB  |= (1<<PB6);
            PORTB |= (1<<PB6);
            break;
        case 1:
            DDRF  |= (1<<PF5);
            PORTF |= (1<<PF5);
            break;
        case 2:
            DDRF  |= (1<<PF6);
            PORTF |= (1<<PF6);
            break;
        case 3:
            DDRF  |= (1<<PF7);
            PORTF |= (1<<PF7);
            break;
        case 4:
            DDRF  |= (1<<PF4);
            PORTF |= (1<<PF4);
            break;
        case 5:
            DDRB  |= (1<<PB2);
            PORTB |= (1<<PB2);
            break;
    }
}

#endif
#endif
