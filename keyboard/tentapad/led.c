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
#include "bootloader.h"
#include "timer.h"
#include "led.h"


#ifndef LEDMAP_ENABLE
void led_set(uint8_t usb_led)
{
    static uint16_t start = 0;
    static uint8_t count = 0;
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        if (timer_elapsed(start) > 250) {
            start = timer_read();
            count = 0;
        }
        count++;
        if (count >= 8) {
            bootloader_jump();
        }
    }
}
#endif
