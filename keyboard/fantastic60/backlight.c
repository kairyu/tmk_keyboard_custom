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

#define BACKLIGHT 0

extern backlight_config_t backlight_config;
static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

void backlight_set(uint8_t level)
{
    softpwm_led_enable();
#ifdef BREATHING_LED_ENABLE
    switch (level) {
        case 1:
        case 2:
        case 3:
#ifdef FADING_LED_ENABLE
            fading_led_disable(BACKLIGHT);
#endif
            breathing_led_disable(BACKLIGHT);
            softpwm_led_set(BACKLIGHT, pgm_read_byte(&backlight_table[level]));
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
        case 8:
            fading_led_enable(BACKLIGHT);
            breathing_led_disable(BACKLIGHT);
            fading_led_set_direction(BACKLIGHT, FADING_LED_FADE_OUT);
            fading_led_set_duration(3);
#endif
        case 0:
        default:
#ifdef FADING_LED_ENABLE
            fading_led_disable(BACKLIGHT);
#endif
            breathing_led_disable(BACKLIGHT);
            softpwm_led_set(BACKLIGHT, 0);
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
 *   RGB R:     PE2
 *   RGB G:     PC6
 *   RGB B:     PC7
 */
void softpwm_led_init()
{
    DDRF  |=  (1<<PF7);
    PORTF |=  (1<<PF7);
    DDRE  |=  (1<<PE2);
    PORTE |=  (1<<PE2);
    DDRC  |=  (1<<PC7 | 1<<PC6);
    PORTC |=  (1<<PC7 | 1<<PC6);
}

void softpwm_led_on(uint8_t index)
{
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
}

void softpwm_led_off(uint8_t index)
{
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
}
#endif
#endif

#ifdef FADING_LED_ENABLE
void action_keyevent(keyevent_t event)
{
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
#endif

#ifdef CUSTOM_LED_ENABLE
void softpwm_led_custom(void)
{
    rgb_fading();
}

#ifdef FADING_LED_ENABLE
void fading_led_custom(uint8_t *value)
{
    rgb_set_brightness(value[0]);
}
#endif

void breathing_led_custom(uint8_t *value)
{
    rgb_set_brightness(value[0]);
}
#endif

#endif
