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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "backlight.h"

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

/* Backlight pin configuration
 * PWM: PC6(OC3A)
 */
void backlight_set(uint8_t level)
{
    if (level > 0) {
        // Turn on PWM
        cli();
        DDRC |= (1<<PC6);
	//TCCR3A = 0b10101001;
	//TCCR3B = 0b00000011;
        TCCR3A |= ( (1<<WGM30) | (1<<COM3A1) | (1<<COM3B1) | (1<<COM3C1) );
        TCCR3B |= ( (1<<CS31) | (1<<CS30) );
        sei();
        // Set PWM
        OCR3A = pgm_read_byte(&backlight_table[level]);
        OCR3B = pgm_read_byte(&backlight_table[level]);
    }
    else {
        // Turn off PWM
        cli();
        DDRC &= ~(1<<PC6);
	//TCCR3A = 0b00000000;
	//TCCR3B = 0b00000000;
        TCCR3A &= ~( (1<<WGM30) | (1<<COM3A1) | (1<<COM3B1) | (1<<COM3C1) );
        TCCR3B &= ~( (1<<CS31) | (1<<CS30) );
        sei();
        // Set PWM
        OCR3A = 0;
        OCR3B = 0;
    }
}
