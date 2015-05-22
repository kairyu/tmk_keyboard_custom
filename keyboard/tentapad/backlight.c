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
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "backlight.h"
#include "softpwm_led.h"
#include "keymap_common.h"
#include "tentapad.h"

#ifdef BACKLIGHT_ENABLE

uint8_t backlight_mode;
const uint8_t backlight_brightness_mid = 64;
const uint8_t backlight_brightness_high = 255;

void backlight_set(uint8_t level)
{
    backlight_mode = level;
    softpwm_led_set_all(0);
    fading_led_set_duration(2);
    fading_led_set_direction_all(FADING_LED_FADE_OUT);
    breathing_led_set_duration(3);
    switch (level) {
        case 0:
            softpwm_led_disable();
            fading_led_disable_all();
            breathing_led_disable_all();
            softpwm_led_on(LED_KEY_SIDE);
            softpwm_led_on(LED_BOARD_SIDE);
            break;
        case 1:
            softpwm_led_set(LED_BOARD_SIDE, backlight_brightness_mid);
            fading_led_disable_all();
            fading_led_enable(LED_KEY_SIDE);
            breathing_led_disable_all();
            softpwm_led_enable();
            break;
        case 2:
            softpwm_led_set(LED_KEY_SIDE, backlight_brightness_mid);
            fading_led_disable_all();
            fading_led_enable(LED_BOARD_SIDE);
            breathing_led_disable_all();
            softpwm_led_enable();
            break;
        case 3:
            fading_led_disable_all();
            breathing_led_disable_all();
            breathing_led_enable(LED_KEY_SIDE);
            breathing_led_enable(LED_BOARD_SIDE);
            softpwm_led_enable();
            break;
        case 4:
            softpwm_led_set(LED_KEY_SIDE, backlight_brightness_mid);
            breathing_led_disable_all();
            breathing_led_enable(LED_BOARD_SIDE);
            fading_led_disable_all();
            softpwm_led_enable();
            break;
        case 5:
            softpwm_led_set(LED_BOARD_SIDE, backlight_brightness_mid);
            breathing_led_disable_all();
            breathing_led_enable(LED_KEY_SIDE);
            fading_led_disable_all();
            softpwm_led_enable();
            break;
        case 6:
            fading_led_disable_all();
            breathing_led_disable_all();
            softpwm_led_disable();
            break;
        case 7:
            fading_led_disable_all();
            breathing_led_disable_all();
            softpwm_led_disable();
            break;
        case 8:
            softpwm_led_set_all(16);
            fading_led_disable_all();
            breathing_led_disable_all();
            softpwm_led_enable();
            break;
    }
}

#ifndef LEDMAP_ENABLE
void softpwm_led_init(void)
{
#ifndef EXPERIMENTAL
    DDRD |= (1<<PD0);
    DDRB |= (1<<PB7);
    DDRC |= (1<<PD5 | 1<<PD6);
#else
    DDRB |= (1<<PB6);
#endif
}

void softpwm_led_on(uint8_t index)
{
#ifndef EXPERIMENTAL
    switch (index) {
        case LED_KEY_1:
            PORTC |= (1<<PC5);
            break;
        case LED_KEY_2:
            PORTC |= (1<<PC6);
            break;
        case LED_KEY_SIDE:
            PORTB |= (1<<PB7);
            break;
        case LED_BOARD_SIDE:
            PORTD |= (1<<PD0);
            break;
    }
#else
    PORTB |= (1<<PB6);
#endif
}

void softpwm_led_off(uint8_t index)
{
#ifndef EXPERIMENTAL
    switch (index) {
        case LED_KEY_1:
            PORTC &= ~(1<<PC5);
            break;
        case LED_KEY_2:
            PORTC &= ~(1<<PC6);
            break;
        case LED_KEY_SIDE:
            PORTB &= ~(1<<PB7);
            break;
        case LED_BOARD_SIDE:
            PORTD &= ~(1<<PD0);
            break;
    }
#else
    PORTB &= ~(1<<PB6);
#endif
}
#endif

#endif
