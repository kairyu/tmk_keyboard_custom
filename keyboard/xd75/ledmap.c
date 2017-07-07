/*
Copyright 2017 Kai Ryu <kai1103@gmail.com>

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
#ifdef LEDMAP_V2
    [0] = LEDMAP_ACTIVE_LOW  | LEDMAP_CAPS_LOCK,                     // CapsLock  - PB2
    [1] = LEDMAP_ACTIVE_LOW  | LEDMAP_LAYER(3),                      // ????      - GPIO0 - PF7
    [2] = LEDMAP_RGB_LED     | LEDMAP_RGB_LED_COUNT(7),              // RGB       - GPIO1 - PF6
    [3] = LEDMAP_ACTIVE_LOW  | LEDMAP_BACKLIGHT,                     // Backlight - GPIO2 - PF5
    [4] = LEDMAP_ACTIVE_HIGH | LEDMAP_NUM_LOCK,                      // ???       - GPIO3 - PF4
#endif
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

#ifndef LEDMAP_V2
void ledmap_led_init(void)
{
    DDRB  |= (1<<PB2);
    PORTB |= (1<<PB2);
    DDRF  |= (1<<PF7 | 1<<PF6 | 1<<PF5);
    PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5);
}

void ledmap_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            PORTB &= ~(1<<PB2);
            break;
        case 1:
            PORTF &= ~(1<<PF6);
            break;
        case 2:
            PORTF &= ~(1<<PF7);
            break;
        case 3:
            PORTF &= ~(1<<PF4);
            break;
    }
}

void ledmap_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            PORTB |= (1<<PB2);
            break;
        case 1:
            PORTF |= (1<<PF6);
            break;
        case 2:
            PORTF |= (1<<PF7);
            break;
        case 3:
            PORTF |= (1<<PF4);
            break;
    }
}
#endif

#endif
