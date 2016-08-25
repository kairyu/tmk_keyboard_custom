/*
Copyright 2016 Kai Ryu <kai1103@gmail.com>

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
    [0] = LEDMAP_NUM_LOCK,              // LED_A - PB5
    [1] = LEDMAP_CAPS_LOCK,             // LED_B - PB6
    [2] = LEDMAP_SCROLL_LOCK,           // LED_C - PB3
    [3] = LEDMAP_LAYER(1),              // RX    - PB0
    [4] = LEDMAP_LAYER(2),              // TX    - PD5
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

void ledmap_led_init(void)
{
    DDRB  |=  (1<<PB5 | 1<<PB6 | 1<<PB3);
    PORTB &= ~(1<<PB5 | 1<<PB6 | 1<<PB3);
    DDRB  |=  (1<<PB0);
    PORTB |=  (1<<PB0);
    DDRD  |=  (1<<PD5);
    PORTD |=  (1<<PD5);
}

void ledmap_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            PORTB |=  (1<<PB5);
            break;
        case 1:
            PORTB |=  (1<<PB6);
            break;
        case 2:
            PORTB |=  (1<<PB3);
            break;
        case 3:
            PORTB &= ~(1<<PB0);
            break;
        case 4:
            PORTD &= ~(1<<PD5);
            break;
    }
}

void ledmap_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            PORTB &= ~(1<<PB5);
            break;
        case 1:
            PORTB &= ~(1<<PB6);
            break;
        case 2:
            PORTB &= ~(1<<PB3);
            break;
        case 3:
            PORTB |=  (1<<PB0);
            break;
        case 4:
            PORTD |=  (1<<PD5);
            break;
    }
}

#endif
