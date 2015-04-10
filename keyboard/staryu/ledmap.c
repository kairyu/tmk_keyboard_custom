/*
Copyright 2015 Kai Ryu <kai1103@gmail.com>

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

#include <avr/pgmspace.h>
#include "ledmap.h"


#ifdef LEDMAP_ENABLE

static const uint16_t ledmaps[LED_COUNT] PROGMEM = {
    [0] = LEDMAP_BACKLIGHT,
    [1] = LEDMAP_BACKLIGHT,
    [2] = LEDMAP_BACKLIGHT,
    [3] = LEDMAP_BACKLIGHT,
    [4] = LEDMAP_BACKLIGHT
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

void ledmap_led_init(void)
{
    DDRC |= (1<<PC2 | 1<<PC7);
    DDRD |= (1<<PD5 | 1<<PD6);
    DDRB |= (1<<PB0);
}

void ledmap_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            PORTC |= (1<<PC2);
            break;
        case 1:
            PORTC |= (1<<PC7);
            break;
        case 2:
            PORTD |= (1<<PD5);
            break;
        case 3:
            PORTD |= (1<<PD6);
            break;
        case 4:
            PORTB |= (1<<PB0);
            break;
    }
}

void ledmap_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            PORTC &= ~(1<<PC2);
            break;
        case 1:
            PORTC &= ~(1<<PC7);
            break;
        case 2:
            PORTD &= ~(1<<PD5);
            break;
        case 3:
            PORTD &= ~(1<<PD6);
            break;
        case 4:
            PORTB &= ~(1<<PB0);
            break;
    }
}

#endif

