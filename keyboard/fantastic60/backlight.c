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
#include "rgb.h"

#ifdef BACKLIGHT_ENABLE

#define BACKLIGHT 0

extern backlight_config_t backlight_config;
uint8_t backlight_brightness;
static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

void backlight_set(uint8_t level)
{
#ifdef BREATHING_LED_ENABLE
    switch (level) {
        case 1:
        case 2:
        case 3:
#ifdef FADING_LED_ENABLE
            fading_led_disable(BACKLIGHT);
#endif
            breathing_led_disable(BACKLIGHT);
            backlight_brightness = pgm_read_byte(&backlight_table[level]);
            softpwm_led_set(BACKLIGHT, backlight_brightness);
            rgb_set_brightness(backlight_brightness);
            break;
        case 4:
        case 5:
        case 6:
#ifdef FADING_LED_ENABLE
            fading_led_disable(BACKLIGHT);
#endif
            breathing_led_enable(BACKLIGHT);
            breathing_led_set_duration(6 - level);
            break;
#ifdef FADING_LED_ENABLE
        case 7:
            fading_led_enable(BACKLIGHT);
            breathing_led_disable(BACKLIGHT);
            fading_led_set_direction(BACKLIGHT, FADING_LED_FADE_IN);
            fading_led_set_duration(3);
            break;
        case 8:
            fading_led_enable(BACKLIGHT);
            breathing_led_disable(BACKLIGHT);
            fading_led_set_direction(BACKLIGHT, FADING_LED_FADE_OUT);
            fading_led_set_duration(3);
            break;
#endif
        case 0:
        default:
#ifdef FADING_LED_ENABLE
            fading_led_disable(BACKLIGHT);
#endif
            breathing_led_disable(BACKLIGHT);
            backlight_brightness = 0;
            softpwm_led_set(BACKLIGHT, backlight_brightness);
            break;
    }
#else
    if (level > 0) {
        softpwm_led_set(BACKLIGHT, pgm_read_byte(&backlight_table[level]));
    }
    else {
        softpwm_led_set(BACKLIGHT, 0);
    }
#endif
}

#ifndef LEDMAP_ENABLE
#ifdef SOFTPWM_LED_ENABLE
/* Backlight pin configuration
 *   Backlight: PF7
 *   RGB R:     PF6
 *   RGB G:     PF5
 *   RGB B:     PF4
 */
void softpwm_led_init()
{
    DDRF  |=  (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    PORTF |=  (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
}

void softpwm_led_on(uint8_t index)
{
    if (index) {
        PORTF &= ~((1<<PF7) >> index);
    }
    else {
        PORTF |=  (1<<PF7);
    }
    /*
    switch (index) {
        case 0:
            PORTF &= ~(1<<PF7);
            break;
        case 1:
            PORTE &= ~(1<<PE2);
            break;
        case 2:
            PORTC &= ~(1<<PC6);
            break;
        case 3:
            PORTC &= ~(1<<PC7);
            break;
    }
    */
}

void softpwm_led_off(uint8_t index)
{
    if (index) {
        PORTF |=  ((1<<PF7) >> index);
    }
    else {
        PORTF &= ~(1<<PF7);
    }
    /*
    switch (index) {
        case 0:
            PORTF |=  (1<<PF7);
            break;
        case 1:
            PORTE |=  (1<<PE2);
            break;
        case 2:
            PORTC |=  (1<<PC6);
            break;
        case 3:
            PORTC |=  (1<<PC7);
            break;
    }
    */
}
#endif
#endif

#ifdef FADING_LED_ENABLE
void action_keyevent(keyevent_t event)
{
    if (backlight_config.enable) {
        if (backlight_config.level == 7) {
            if (event.pressed) {
                fading_led_set_delay(BACKLIGHT, 64);
                softpwm_led_decrease(BACKLIGHT, 32);
            }
        }
        if (backlight_config.level == 8) {
            if (event.pressed) {
                fading_led_set_delay(BACKLIGHT, 64);
                softpwm_led_increase(BACKLIGHT, 32);
            }
        }
    }
}
#endif

#ifdef CUSTOM_LED_ENABLE
void softpwm_led_custom(void)
{
    rgb_fading();
}

#ifdef FADING_LED_ENABLE
void fading_led_custom(uint8_t *value)
{
    rgb_set_brightness(value[BACKLIGHT]);
}
#endif

void breathing_led_custom(uint8_t *value)
{
    rgb_set_brightness(value[BACKLIGHT]);
}
#endif

#endif
