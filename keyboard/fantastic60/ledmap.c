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

#include <avr/pgmspace.h>
#include "ledmap.h"
#include "fantastic.h"

#ifdef LEDMAP_ENABLE

static const uint16_t ledmaps[LED_COUNT] PROGMEM = {
    [0] = LEDMAP_CAPS_LOCK | LEDMAP_BACKLIGHT,      // CapsLock
    [1] = LEDMAP_BACKLIGHT,                         // Backlight
    [2] = LEDMAP_BACKLIGHT,                         // RGB Light
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

/* LED pin configration
 *   CapsLock:  PE6
 *   Backlight: PF7
 *   RGB R:     PE2
 *   RGB G:     PC6
 *   RGB B:     PC7
 */
void ledmap_led_init(void)
{
    DDRE  |=  (1<<PE6 | 1<<PE2);
    PORTE |=  (1<<PE6 | 1<<PE2);
    DDRF  |=  (1<<PF7);
    PORTF |=  (1<<PF7);
    DDRC  |=  (1<<PC7 | 1<<PC6);
    PORTF |=  (1<<PC7 | 1<<PC6);
    shift_register_init();
    shift_register_write_word(0x0000);
}

void ledmap_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            PORTE &= ~(1<<PE6);
            break;
        case 1:
            PORTF &= ~(1<<PF7);
            break;
        case 2:
            PORTE &= ~(1<<PE2);
            PORTC &= ~(1<<PC7 | 1<<PC6);
            break;
    }
}

void ledmap_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            PORTE |=  (1<<PE6);
            break;
        case 1:
            PORTF |=  (1<<PF7);
            break;
        case 2:
            PORTE |=  (1<<PE2);
            PORTC |=  (1<<PC7 | 1<<PC6);
            break;
    }
}

#endif
