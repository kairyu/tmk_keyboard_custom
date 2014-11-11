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
#include "kimera.h"

#ifndef LEDMAP_ENABLE

void led_set(uint8_t usb_led)
{
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // output low
        LED1_DDR  |=  (1<<LED1_BIT);
        LED1_PORT &= ~(1<<LED1_BIT);
    } else {
        // Hi-Z
        LED1_DDR  &= ~(1<<LED1_BIT);
        LED1_PORT &= ~(1<<LED1_BIT);
    }
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        LED2_DDR  |=  (1<<LED2_BIT);
        LED2_PORT &= ~(1<<LED2_BIT);
    } else {
        // Hi-Z
        LED2_DDR  &= ~(1<<LED2_BIT);
        LED2_PORT &= ~(1<<LED2_BIT);
    }
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        // output low
        LED3_DDR  |=  (1<<LED3_BIT);
        LED3_PORT &= ~(1<<LED3_BIT);
    } else {
        // Hi-Z
        LED3_DDR  &= ~(1<<LED3_BIT);
        LED3_PORT &= ~(1<<LED3_BIT);
    }
}

#endif
