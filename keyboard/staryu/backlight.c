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
#include "timer.h"
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
            fading_led_disable_all();
            breathing_led_set_duration(6 - level);
            breathing_led_set_index_all(0);
            breathing_led_enable_all();
            break;
        case 7:
            breathing_led_disable_all();
            breathing_led_set_duration(1);
            fading_led_set_direction_all(FADING_LED_FADE_OUT);
            fading_led_set_duration(3);
            fading_led_enable_all();
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
        case 1:
            PORTC &= ~(1<<PC2);
            break;
        case 2:
            PORTC &= ~(1<<PC7);
            break;
        case 3:
            PORTD &= ~(1<<PD5);
            break;
        case 4:
            PORTD &= ~(1<<PD6);
            break;
        case 5:
            PORTB &= ~(1<<PB0);
            break;
    }
}

void softpwm_led_off(uint8_t index)
{
    switch (index) {
        case 1:
            PORTC |= (1<<PC2);
            break;
        case 2:
            PORTC |= (1<<PC7);
            break;
        case 3:
            PORTD |= (1<<PD5);
            break;
        case 4:
            PORTD |= (1<<PD6);
            break;
        case 5:
            PORTB |= (1<<PB0);
            break;
    }
}
#endif

static uint8_t idle_state = 0;
static uint16_t idle_last = 0;

void action_keyevent(keyevent_t event)
{
    if (backlight_config.enable) {
        if (backlight_config.level == 7) {
            if (event.pressed) {
                if (idle_state > 1) {
                    breathing_led_disable_all();
                }
                idle_state = 0;
                uint8_t key = event.key.col + 1;
                fading_led_set_delay(key, 64);
                softpwm_led_increase(key, 32);
            }
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
    static uint8_t index = 0;
    static uint16_t last = 0;
    if (backlight_config.level == 7) {
        if (idle_state == 0) {
            uint8_t max = value[0];
            for (uint8_t i = 1; i < LED_COUNT; i++) {
                if (value[i] > max) max = value[i];
            }
            rgb_set_brightness(max);
            if (max == 0) {
                idle_last = timer_read();
                idle_state = 1;
            }
        }
        if (idle_state == 1) {
            if (timer_elapsed(idle_last) > 3000) {
                breathing_led_set_index_all(0);
                index = 0;
                idle_state = 2;
            }
        }
        if (idle_state == 2) {
            if (timer_elapsed(last) > 500) {
                last = timer_read();
                breathing_led_enable_once(index);
                index = (index + 1) % 6;
            }
        }
    }
}

void breathing_led_custom(uint8_t *value)
{
    rgb_set_brightness(value[0]);
}
#endif

#endif
