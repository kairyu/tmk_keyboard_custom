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

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

extern backlight_config_t backlight_config;
uint8_t backlight_brightness;

void backlight_set(uint8_t level)
{
    softpwm_led_enable();
    switch (level) {
        case 1:
        case 2:
        case 3:
            fading_led_disable_all();
            breathing_led_disable_all();
            backlight_brightness = pgm_read_byte(&backlight_table[level]);
            softpwm_led_set_all(backlight_brightness);
            rgb_set_brightness(backlight_brightness);
            break;
        case 4:
        case 5:
        case 6:
            breathing_led_enable_all();
            fading_led_disable_all();
            breathing_led_set_duration(6 - level);
            break;
        case 7:
        case 8:
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction_all(FADING_LED_FADE_IN);
            fading_led_set_duration(level == 7 ? 3 : 0);
            break;
        case 9:
        case 10:
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction_all(FADING_LED_FADE_OUT);
            fading_led_set_duration(level == 9 ? 3 : 0);
            break;
        case 0:
        default:
            fading_led_disable_all();
            breathing_led_disable_all();
            backlight_brightness = 0;
            softpwm_led_set_all(backlight_brightness);
            break;
    }
}


#ifndef LEDMAP_ENABLE
void softpwm_led_init(void)
{
    DDRC |= (1<<PC2 | 1<<PC7);
    DDRD |= (1<<PD5 | 1<<PD6);
    DDRB |= (1<<PB0);
}

void softpwm_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            PORTC &= ~(1<<PC2);
            break;
        case 1:
            PORTC &= ~(1<<PC7);
            break;
        case 2:
            PORTD &= ~(1<<PD5);
            break;
        case 3:
            PORTD &= ~(1<<PD6);
            break;
        case 4:
            PORTB &= ~(1<<PB0);
            break;
    }
}

void softpwm_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            PORTC |= (1<<PC2);
            break;
        case 1:
            PORTC |= (1<<PC7);
            break;
        case 2:
            PORTD |= (1<<PD5);
            break;
        case 3:
            PORTD |= (1<<PD6);
            break;
        case 4:
            PORTB |= (1<<PB0);
            break;
    }
}
#endif

void action_keyevent(keyevent_t event)
{
    if (backlight_config.enable) {
        switch (backlight_config.level) {
            case 7:
                if (event.pressed) {
                    fading_led_set_delay(event.key.col, 64);
                    softpwm_led_decrease(event.key.col, 32);
                }
                break;
            case 8:
                if (event.pressed) {
                    fading_led_set_direction(event.key.col, FADING_LED_FADE_OUT);
                }
                else {
                    fading_led_set_direction(event.key.col, FADING_LED_FADE_IN);
                }
                break;
            case 9:
                if (event.pressed) {
                    fading_led_set_delay(event.key.col, 64);
                    softpwm_led_increase(event.key.col, 32);
                }
                break;
            case 10:
                if (event.pressed) {
                    fading_led_set_direction(event.key.col, FADING_LED_FADE_IN);
                }
                else {
                    fading_led_set_direction(event.key.col, FADING_LED_FADE_OUT);
                }
                break;
        }
    }
}

#ifdef CUSTOM_LED_ENABLE
void softpwm_led_custom(void)
{
    rgb_fading();
}

void fading_led_custom(uint8_t *value)
{
    uint8_t tmp = value[0];
    switch (backlight_config.level) {
        case 7:
        case 8:
            for (uint8_t i = 0; i < LED_COUNT; i++) {
                if (value[i] < tmp) tmp = value[i];
            }
            break;
        case 9:
        case 10:
            for (uint8_t i = 0; i < LED_COUNT; i++) {
                if (value[i] > tmp) tmp = value[i];
            }
            break;
    }
    rgb_set_brightness(tmp);
}

void breathing_led_custom(uint8_t *value)
{
    rgb_set_brightness(*value);
}
#endif

#endif
