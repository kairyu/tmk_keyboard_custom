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
#include "action.h"

#ifdef BACKLIGHT_ENABLE

static uint8_t backlight_mode;

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

void backlight_enable(void);
void backlight_disable(void);

/* Backlight pin configuration
 * PWM: PF7
 */
void backlight_enable(void)
{
    DDRF |= (1<<PF7);
    softpwm_led_enable();
}

void backlight_disable(void)
{
    DDRF &= ~(1<<PF7);
    softpwm_led_disable();
}

void backlight_set(uint8_t level)
{
#ifdef BREATHING_LED_ENABLE
    switch (level) {
        case 1:
        case 2:
        case 3:
            backlight_enable();
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_disable_all();
            softpwm_led_set_all(pgm_read_byte(&backlight_table[level]));
            break;
        case 4:
        case 5:
        case 6:
            backlight_enable();
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_enable_all();
            breathing_led_set_duration(6 - level);
            break;
#ifdef FADING_LED_ENABLE
        case 7:
            backlight_enable();
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction(FADING_LED_FADE_IN);
            fading_led_set_duration(3);
        case 8:
            backlight_enable();
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction(FADING_LED_FADE_OUT);
            fading_led_set_duration(3);
#endif
        case 0:
        default:
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_disable_all();
            backlight_disable();
            break;
    }
#else
    if (level > 0) {
        backlight_enable();
        softpwm_led_set_all(pgm_read_byte(&backlight_table[level]));
    }
    else {
        backlight_disable();
    }
#endif
}

#ifndef LEDMAP_ENABLE
#ifdef SOFTPWM_LED_ENABLE
void softpwm_led_on(uint8_t index)
{
    PORTF |= (1<<PF7);
}

void softpwm_led_off(uint8_t index)
{
    PORTF &= ~(1<<PF7);
}
#endif
#endif

#ifdef FADING_LED_ENABLE
void action_keyevent(keyevent_t event)
{
    if (backlight_mode == 7) {
        if (event.pressed) {
            softpwm_led_decrease_all(32);
        }
    }
    if (backlight_mode == 8) {
        if (event.pressed) {
            softpwm_led_increase_all(32);
        }
    }
}
#endif

#endif
