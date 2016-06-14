/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#ifndef LED_H
#define LED_H
#include "stdint.h"

#ifndef LED_COUNT
#define LED_COUNT 1
#endif

#if (LED_COUNT <= 8)
typedef uint8_t  led_pack_t;
#elif (LED_COUNT <= 16)
typedef uint16_t led_pack_t;
#elif (LED_COUNT <= 32)
typedef uint32_t led_pack_t;
#else
#error "LED_COUNT: invalid value"
#endif

#if (LED_COUNT <= 16)
#define LED_BIT(i) (1U<<(i))
#elif (LED_COUNT <= 32)
#define LED_BIT(i) (1UL<<(i))
#else
#error "LED_COUNT: invalid value"
#endif

#define LED_BIT_SET(x, i) ((x) |= LED_BIT(i))
#define LED_BIT_CLEAR(x, i) ((x) &= ~LED_BIT(i))
#define LED_BIT_XOR(x, i) ((x) ^= LED_BIT(i))
#define LED_BIT_IS_SET(x, i) ((x) & LED_BIT(i))

/* keyboard LEDs */
#define USB_LED_NUM_LOCK                0
#define USB_LED_CAPS_LOCK               1
#define USB_LED_SCROLL_LOCK             2
#define USB_LED_COMPOSE                 3
#define USB_LED_KANA                    4


#ifdef __cplusplus
extern "C" {
#endif

void led_set(uint8_t usb_led);

#ifdef __cplusplus
}
#endif

#endif
