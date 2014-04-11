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
#include <avr/pgmspace.h>
#include "backlight.h"

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

uint8_t softpwm_ocr = 0;

/* Backlight pin configuration
 * PWM:  PB5            (RevRS)
 * GPIO: PF7  PF6  PF5
 */
void backlight_set(uint8_t level)
{
    if (level > 0) {
        // Turn on PWM
        cli();
        // Hard PWM
        DDRB |= (1<<PB5);
        PORTB |= (1<<PB5);
        TCCR1A |= ((1<<WGM10) | (1<<COM1A1));
        TCCR1B |= ((1<<CS11) | (1<<CS10));
        // Soft PWM
        DDRF |= ((1<<PF7) | (1<<PF6) | (1<<PF5));
        PORTF |= ((1<<PF7) | (1<<PF6) | (1<<PF5));
        TIMSK1 |= ((1<<OCIE1A) | (1<<TOIE1));
        TIFR1 |= (1<<TOV1);
        sei();
        // Set PWM
        OCR1A = pgm_read_byte(&backlight_table[level]);
        softpwm_ocr = pgm_read_byte(&backlight_table[level]);
    }
    else {
        // Turn off PWM
        cli();
        // Hard PWM
        DDRB |= (1<<PB5);
        PORTB &= ~(1<<PB5);
        TCCR1A &= ~((1<<WGM10) | (1<<COM1A1));
        TCCR1B &= ~((1<<CS11) | (1<<CS10));
        // Soft PWM
        DDRF |= ((1<<PF7) | (1<<PF6) | (1<<PF5));
        PORTF |= ((1<<PF7) | (1<<PF6) | (1<<PF5));
        TIMSK1 |= ((1<<OCIE1A) | (1<<TOIE1));
        TIFR1 |= (1<<TOV1);
        sei();
        // Set PWM
        OCR1A = 0;
        softpwm_ocr = 0;
    }
}

ISR(TIMER1_COMPA_vect)
{
    // LED off
    PORTF |= ((1<<PF7) | (1<<PF6) | (1<<PF5));
}
ISR(TIMER1_OVF_vect)
{
    // LED on
    PORTF &= ~((1<<PF7) | (1<<PF6) | (1<<PF5));
}
