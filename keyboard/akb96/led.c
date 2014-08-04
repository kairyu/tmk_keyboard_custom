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
#include "stdint.h"
#include "led.h"
#include "action_layer.h"


/* LED pin configration
 *   REV_V2
 *     CapsLock  PB5 (D9)
 *     NumLock   PB2 (D16)
 *   REV_V3
 *     CapsLock  PC7
 *     NumLock   PC6
 */
void led_set(uint8_t usb_led)
{
#if defined(REV_V2)
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output high
        DDRB |= (1<<PB5);
        PORTB |= (1<<PB5);
    } else {
        // Hi-Z
        DDRB &= ~(1<<PB5);
        PORTB &= ~(1<<PB5);
    }
#elif defined(REV_V3)
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output high
        DDRC |= (1<<PC7);
        PORTC |= (1<<PC7);
    } else {
        // Hi-Z
        DDRC &= ~(1<<PC7);
        PORTC &= ~(1<<PC7);
    }
#endif
}

#ifdef ON_LAYER_CHANGE
void layer_change(uint32_t state)
{
#if defined(REV_V2)
    if (state & (1UL<<2)) {
        // output high
        DDRB |= (1<<PB2);
        PORTB |= (1<<PB2);
    } else {
        // Hi-Z
        DDRB &= ~(1<<PB2);
        PORTB &= ~(1<<PB2);
    }
#elif defined(REV_V3)
    if (state & (1UL<<2)) {
        // output high
        DDRC |= (1<<PC6);
        PORTC |= (1<<PC6);
    } else {
        // Hi-Z
        DDRC &= ~(1<<PC6);
        PORTC &= ~(1<<PC6);
    }
#endif
}
#endif
