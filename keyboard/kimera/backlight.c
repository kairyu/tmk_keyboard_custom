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
#ifdef SOFTPWM_LED_ENABLE
#include "softpwm_led.h"
#else
#include "breathing_led.h"
#endif
#include "hook.h"
#include "kimera.h"
#include "rgb_led.h"

#ifdef BACKLIGHT_ENABLE

void backlight_enable(void);
void backlight_disable(void);
inline void backlight_set_raw(uint8_t raw);

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

extern backlight_config_t backlight_config;
static uint8_t backlight_brightness;

/* Backlight pin configuration
 * LED4: PB6 (D10) OC1B
 */
#ifndef SOFTPWM_LED_ENABLE
void backlight_enable(void)
{
    // Turn on PWM
    LED4_DDR |= (1<<LED4_BIT);
    cli();
    TCCR1A |= ((1<<WGM10) | (1<<COM1B1));
    TCCR1B |= ((1<<CS11) | (1<<CS10));
    sei();
}
#endif

#ifndef SOFTPWM_LED_ENABLE
void backlight_disable(void)
{
    // Turn off PWM
    LED4_DDR &= ~(1<<LED4_BIT);
    cli();
    TCCR1A &= ~((1<<WGM10) | (1<<COM1B1));
    TCCR1B &= ~((1<<CS11) | (1<<CS10));
    sei();
    LED4_OCR = 0;
}
#endif

void backlight_set(uint8_t level)
{
#ifdef SOFTPWM_LED_ENABLE
    softpwm_enable();
#endif
#ifdef BREATHING_LED_ENABLE
    switch (level) {
        case 1:
        case 2:
        case 3:
#ifdef SOFTPWM_LED_ENABLE
            softpwm_led_enable_all();
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_disable_all();
#else
            backlight_enable();
            breathing_led_disable();
#endif
            backlight_brightness = pgm_read_byte(&backlight_table[level]);
            backlight_set_raw(backlight_brightness);
            break;
        case 4:
        case 5:
        case 6:
#ifdef SOFTPWM_LED_ENABLE
            softpwm_led_enable_all();
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_enable_all();
#else
            backlight_enable();
            breathing_led_enable();
#endif
            breathing_led_set_duration(6 - level);
            break;
#ifdef SOFTPWM_LED_ENABLE
#ifdef FADING_LED_ENABLE
        case 7:
            softpwm_led_enable_all();
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction_all(FADING_LED_FADE_IN);
            fading_led_set_duration(3);
            break;
        case 8:
            softpwm_led_enable_all();
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction_all(FADING_LED_FADE_OUT);
            fading_led_set_duration(3);
            break;
#endif
#endif
        case 0:
        default:
#ifdef SOFTPWM_LED_ENABLE
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_disable_all();
            backlight_brightness = 0;
            backlight_set_raw(backlight_brightness);
            softpwm_led_disable_all();
#else
            breathing_led_disable();
            backlight_disable();
#endif
            break;
    }
#else
    if (level > 0) {
        backlight_enable();
        backlight_set_raw(pgm_read_byte(&backlight_table[level]));
    }
    else {
        backlight_disable();
    }
#endif
}

#ifndef SOFTPWM_LED_ENABLE
#ifdef BREATHING_LED_ENABLE
void breathing_led_set_raw(uint8_t raw)
{
    backlight_set_raw(raw);
}
#endif
#endif

inline void backlight_set_raw(uint8_t raw)
{
#ifdef SOFTPWM_LED_ENABLE
    softpwm_led_set_all(raw);
#else
    LED4_OCR = raw;
#endif
}

#ifndef LEDMAP_ENABLE
#ifdef SOFTPWM_LED_ENABLE
void softpwm_led_init(void)
{
    LED4_DDR  |=  (1<<LED4_BIT);
}

void softpwm_led_on(uint8_t index)
{
    LED4_PORT |=  (1<<LED4_BIT);
}

void softpwm_led_off(uint8_t index)
{
    LED4_PORT &= ~(1<<LED4_BIT);
}
#endif
#endif

#ifdef SOFTPWM_LED_ENABLE
#ifdef FADING_LED_ENABLE
void hook_matrix_change(keyevent_t event)
{
    if (backlight_config.enable) {
        if (backlight_config.level == 7) {
            if (event.pressed) {
                fading_led_set_delay_all(64);
                softpwm_led_decrease_all(32);
            }
        }
        if (backlight_config.level == 8) {
            if (event.pressed) {
                fading_led_set_delay_all(64);
                softpwm_led_increase_all(32);
            }
        }
    }
}
#endif

#ifdef RGB_LED_ENABLE
#ifdef CUSTOM_LED_ENABLE
void softpwm_led_custom(void)
{
}

void fading_led_custom(uint8_t *value)
{
    rgb_led_set_brightness(value[0], false);
}

void breathing_led_custom(uint8_t *value)
{
    rgb_led_set_brightness(value[0], false);
}
#endif
#endif
#endif

#endif
