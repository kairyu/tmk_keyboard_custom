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
    [0] = LEDMAP_CAPS_LOCK | LEDMAP_BACKLIGHT,  // CapsLock  - PC6
    [1] = LEDMAP_LAYER(3)  | LEDMAP_BACKLIGHT,  // Esc       - PD7
    [2] = LEDMAP_LAYER(1)  | LEDMAP_BACKLIGHT,  // WASD      - PD6
    [3] = LEDMAP_BACKLIGHT,                     // Backlight - PE6
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

/* LED pin configration
 */
void ledmap_led_init(void)
{
#ifdef VER_PROTOTYPE
    DDRC  |=  (1<<PC6);
    PORTC &= ~(1<<PC6);
    DDRD  |=  (1<<PD7 | 1<<PC6);
    PORTD &= ~(1<<PD7 | 1<<PC6);
    DDRE  |=  (1<<PE6);
    PORTE |=  (1<<PE6);
#else
    DDRC  |= (1<<PC6);
    PORTC |= (1<<PC6);
    DDRD  |= (1<<PD7 | 1<<PC6);
    PORTD |= (1<<PD7 | 1<<PC6);
    DDRE  |= (1<<PE6);
    PORTE |= (1<<PE6);
#endif
}

void ledmap_led_on(uint8_t index)
{
    switch (index) {
#ifdef VER_PROTOTYPE
        case 0:
            PORTC |=  (1<<PC6);
            break;
        case 1:
            PORTD |=  (1<<PD7);
            break;
        case 2:
            PORTD |=  (1<<PD6);
            break;
#else
        case 0:
            PORTC &= ~(1<<PC6);
            break;
        case 1:
            PORTD &= ~(1<<PD7);
            break;
        case 2:
            PORTD &= ~(1<<PD6);
            break;
#endif
        case 3:
            PORTE &= ~(1<<PE6);
            break;
    }
}

void ledmap_led_off(uint8_t index)
{
    switch (index) {
#ifdef VER_PROTOTYPE
        case 0:
            PORTC &= ~(1<<PC6);
            break;
        case 1:
            PORTD &= ~(1<<PD7);
            break;
        case 2:
            PORTD &= ~(1<<PD6);
            break;
#else
        case 0:
            PORTC |=  (1<<PC6);
            break;
        case 1:
            PORTD |=  (1<<PD7);
            break;
        case 2:
            PORTD |=  (1<<PD6);
            break;
#endif
        case 3:
            PORTE |=  (1<<PE6);
            break;
    }
}

#endif
