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
#include "breathing_led.h"

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

inline void backlight_set_raw(uint8_t raw);

/* Backlight pin configuration
 * PWM: PB7
 */
void backlight_enable(void)
{
    // Turn on PWM
    cli();
    DDRB |= (1<<PB7);
    TCCR1A |= ( (1<<WGM10) | (1<<COM1C1) );
    TCCR1B |= ( (1<<CS11) | (1<<CS10) );
    sei();
}
void backlight_disable(void)
{
    // Turn off PWM
    cli();
    DDRB &= ~(1<<PB7);
    TCCR1A &= ~( (1<<WGM10) | (1<<COM1C1) );
    TCCR1B &= ~( (1<<CS11) | (1<<CS10) );
    sei();
}

void backlight_set(uint8_t level)
{
#ifdef BREATHING_LED_ENABLE
    switch (level) {
        case 1:
        case 2:
        case 3:
            backlight_enable();
            breathing_led_disable();
            backlight_set_raw(pgm_read_byte(&backlight_table[level]));
            break;
        case 4:
        case 5:
        case 6:
            backlight_enable();
            breathing_led_enable();
            breathing_led_set_duration(6 - level);
            break;
        case 0:
        default:
            breathing_led_disable();
            backlight_disable();
            break;
    }
#else
    if (level > 0) {
        backlight_enable();
        backlight_set_raw(pgm_read_byte(&backlight_table[level]));
    }
    else {
        backlight_disable();
    }
#endif
}

#ifdef BREATHING_LED_ENABLE
void breathing_led_set_raw(uint8_t raw)
{
    backlight_set_raw(raw);
}
#endif

inline void backlight_set_raw(uint8_t raw)
{
    OCR1C = raw;
}
