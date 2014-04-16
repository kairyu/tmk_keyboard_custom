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
#include "debug.h"

#if defined(BREATHING_LED_ENABLE) || defined(BACKLIGHT_CUSTOM)
static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

/* Backlight pin configuration
 * PWM: PB6
 */
void backlight_enable(void)
{
#if defined(GH60_REV_CHN)
    // Turn on PWM
    cli();
    DDRB |= (1<<PB6);
    TCCR1A |= ( (1<<WGM10) | (1<<COM1B1) );
    TCCR1B |= ( (1<<CS11) | (1<<CS10) );
    sei();
#else
    DDRF  |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    cli();
    TCCR1A |= (1<<WGM10);
    TCCR1B |= ((1<<CS11) | (1<<CS10));
    TIMSK1 |= ((1<<OCIE1A) | (1<<TOIE1));
    TIFR1 |= (1<<TOV1);
    sei();
#endif
}

void backlight_disable(void)
{
#if defined(GH60_REV_CHN)
    // Turn off PWM
    cli();
    DDRB &= ~(1<<PB6);
    TCCR1A &= ~( (1<<WGM10) | (1<<COM1B1) );
    TCCR1B &= ~( (1<<CS11) | (1<<CS10) );
    sei();
    OCR1A = 0;
#else
    DDRF  &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    cli();
    TCCR1A &= ~(1<<WGM10);
    TCCR1B &= ~((1<<CS11) | (1<<CS10));
    TIMSK1 |= ((1<<OCIE1A) | (1<<TOIE1));
    TIFR1 |= (1<<TOV1);
    sei();
    OCR1A = 0;
#endif
}

void backlight_set(uint8_t level)
{
    if (level > 0) {
        backlight_set_raw(pgm_read_byte(&backlight_table[level]));
    }
}

void backlight_set_raw(uint8_t raw)
{
#if defined(GH60_REV_CHN)
    OCR1B = raw;
#else
    OCR1A = raw;
#endif
}

#ifndef GH60_REV_CHN
ISR(TIMER1_COMPA_vect)
{
    // LED off
    PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
}
ISR(TIMER1_OVF_vect)
{
    // LED on
    PORTF &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
}
#endif
#else
#if defined(GH60_REV_CHN)
static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

/* Backlight pin configuration
 * PWM: PB7
 */
void backlight_set(uint8_t level)
{
    if (level > 0) {
        // Turn on PWM
        cli();
        DDRB |= (1<<PB6);
        TCCR1A |= ( (1<<WGM10) | (1<<COM1B1) );
        TCCR1B |= ( (1<<CS11) | (1<<CS10) );
        sei();
        // Set PWM
        OCR1B = pgm_read_byte(&backlight_table[level]);
    }
    else {
        // Turn off PWM
        cli();
        DDRB &= ~(1<<PB6);
        TCCR1A &= ~( (1<<WGM10) | (1<<COM1B1) );
        TCCR1B &= ~( (1<<CS11) | (1<<CS10) );
        sei();
        // Set PWM
        OCR1B = 0;
    }
}
#elif #defined(GH60_REV_CNY)
static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

void backlight_set(uint8_t level)
{
    if (level > 0) {
        led_matrix_disable();
        for (uint8_t row = 0; row < LED_MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < LED_MATRIX_COLS; col++) {
                led_matrix_set_value(row, col, pgm_read_byte(&backlight_table[level]));
            }
        }
        led_matrix_enable();
    }
    else {
        led_matrix_disable();
    }
}
#else
static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

void backlight_set(uint8_t level)
{
    if (level > 0) {
        DDRF  |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
        PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
        cli();
        TCCR1A |= (1<<WGM10);
        TCCR1B |= ((1<<CS11) | (1<<CS10));
        TIMSK1 |= ((1<<OCIE1A) | (1<<TOIE1));
        TIFR1 |= (1<<TOV1);
        sei();
        OCR1A = pgm_read_byte(&backlight_table[level]);
    }
    else {
        DDRF  &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
        cli();
        TCCR1A &= ~(1<<WGM10);
        TCCR1B &= ~((1<<CS11) | (1<<CS10));
        TIMSK1 |= ((1<<OCIE1A) | (1<<TOIE1));
        TIFR1 |= (1<<TOV1);
        sei();
        OCR1A = 0;
    }
}

ISR(TIMER1_COMPA_vect)
{
    // LED off
    PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
}
ISR(TIMER1_OVF_vect)
{
    // LED on
    PORTF &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
}
#endif
#endif
