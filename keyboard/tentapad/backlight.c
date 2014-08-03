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
#include "softpwm_led.h"

#ifdef BACKLIGHT_ENABLE

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

void backlight_set(uint8_t level)
{
    switch (level) {
        case 1:
        case 2:
        case 3:
            softpwm_led_enable();
            breathing_led_disable_all();
            softpwm_led_set_all(pgm_read_byte(&backlight_table[level]));
            break;
        case 4:
        case 5:
        case 6:
            softpwm_led_enable();
            breathing_led_enable_all();
            breathing_led_set_duration_all(6 - level);
            break;
        case 0:
        default:
            breathing_led_disable_all();
            softpwm_led_disable();
            break;
    }
}

#ifndef LEDMAP_ENABLE
void softpwm_led_init(void)
{
    DDRD |= (1<<PD0);
    DDRB |= (1<<PB7);
    DDRC |= (1<<PD5 | 1<<PD6);
}

void softpwm_led_on(uint8_t index)
{
    PORTD |= (1<<PD0);
    PORTB |= (1<<PB7);
    PORTC |= (1<<PD5 | 1<<PD6);
}

void softpwm_led_off(uint8_t index)
{
    PORTD &= ~(1<<PD0);
    PORTB &= ~(1<<PB7);
    PORTC &= ~(1<<PD5 | 1<<PD6);
}
#endif

#endif
