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
    [0] = LEDMAP_ACTIVE_LOW | LEDMAP_CAPS_LOCK | LEDMAP_BACKLIGHT,  // CapsLock  - PC6
    [1] = LEDMAP_ACTIVE_LOW | LEDMAP_LAYER(1)  | LEDMAP_BACKLIGHT,  // Esc       - PD1
    [2] = LEDMAP_ACTIVE_LOW | LEDMAP_BACKLIGHT,                     // Backlight - PD0
    [3] = LEDMAP_RGB_LED    | LEDMAP_RGB_LED_COUNT(RGB_LED_COUNT),  // RGB       - PC7
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

#ifndef LEDMAP_V2
/* LED pin configration
 */
void ledmap_led_init(void)
{
    DDRC  |= (1<<PC7 | 1<<PC6);
    PORTC |= (1<<PC7 | 1<<PC6);
    DDRD  |= (1<<PD1 | 1<<PC0);
    PORTD |= (1<<PD1 | 1<<PC0);
}

void ledmap_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            PORTC &= ~(1<<PC6);
            break;
        case 1:
            PORTD &= ~(1<<PD1);
            break;
        case 2:
            PORTD &= ~(1<<PD0);
            break;
    }
}

void ledmap_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            PORTC |=  (1<<PC6);
            break;
        case 1:
            PORTD |=  (1<<PD1);
            break;
        case 2:
            PORTD |=  (1<<PD0);
            break;
    }
}
#endif

#endif
