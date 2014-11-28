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
#include "kimera.h"

#ifdef LEDMAP_ENABLE

static const uint16_t ledmaps[LED_COUNT] PROGMEM = {
    [0] = LEDMAP_NUM_LOCK,              // LED1
    [1] = LEDMAP_CAPS_LOCK,             // LED2
    [2] = LEDMAP_SCROLL_LOCK,           // LED3
    [3] = LEDMAP_BACKLIGHT,             // LED4
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

void ledmap_led_init(void)
{
    LED1_DDR  |=  (1<<LED1_BIT);
    LED1_PORT |=  (1<<LED1_BIT);
    LED2_DDR  |=  (1<<LED2_BIT);
    LED2_PORT |=  (1<<LED2_BIT);
    LED3_DDR  |=  (1<<LED3_BIT);
    LED3_PORT |=  (1<<LED3_BIT);
    LED4_DDR  |=  (1<<LED4_BIT);
    LED4_PORT &= ~(1<<LED4_BIT);
}

void ledmap_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            LED1_PORT &= ~(1<<LED1_BIT);
            break;
        case 1:
            LED2_PORT &= ~(1<<LED2_BIT);
            break;
        case 2:
            LED3_PORT &= ~(1<<LED3_BIT);
            break;
        case 3:
            LED4_PORT |=  (1<<LED4_BIT);
            break;
    }
}

void ledmap_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            LED1_PORT |=  (1<<LED1_BIT);
            break;
        case 1:
            LED2_PORT |=  (1<<LED2_BIT);
            break;
        case 2:
            LED3_PORT |=  (1<<LED3_BIT);
            break;
        case 3:
            LED4_PORT &= ~(1<<LED4_BIT);
            break;
    }
}

#endif
