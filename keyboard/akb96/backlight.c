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
#include "action.h"

#ifdef BACKLIGHT_ENABLE

static uint8_t backlight_mode;

void backlight_enable(void);
void backlight_disable(void);
inline void backlight_set_raw(uint8_t raw);

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

/* Backlight pin configuration
 * PWM:  PB6 (D10)  REV_V2
 *       PB7        REV_V3
 *       PB7        REV_V3_LITE
 */
void backlight_enable(void)
{
#ifdef SOFTPWM_LED_ENABLE
    softpwm_led_enable();
#else
    // Turn on PWM
#if defined(REV_V2)
    DDRB |= (1<<PB6);
#elif defined(REV_V3) || defined(REV_V3_LITE)
    DDRB |= (1<<PB7);
#endif
    cli();
    TCCR1A |= ((1<<WGM10) | (1<<COM1B1));
    TCCR1B |= ((1<<CS11) | (1<<CS10));
    sei();
#endif
}

void backlight_disable(void)
{
#ifdef SOFTPWM_LED_ENABLE
    softpwm_led_disable();
#else
    // Turn off PWM
    cli();
#if defined(REV_V2)
    DDRB &= ~(1<<PB6);
#elif defined(REV_V3) || defined(REV_V3_LITE)
    DDRB &= ~(1<<PB7);
#endif
    TCCR1A &= ~( (1<<WGM10) | (1<<COM1B1) );
    TCCR1B &= ~( (1<<CS11) | (1<<CS10) );
    sei();
    OCR1B = 0;
#endif
}

void backlight_set(uint8_t level)
{
    backlight_mode = level;
#ifdef BREATHING_LED_ENABLE
    switch (level) {
        case 1:
        case 2:
        case 3:
            backlight_enable();
#ifdef SOFTPWM_LED_ENABLE
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_disable_all();
#else
            breathing_led_disable();
#endif
            backlight_set_raw(pgm_read_byte(&backlight_table[level]));
            break;
        case 4:
        case 5:
        case 6:
            backlight_enable();
#ifdef SOFTPWM_LED_ENABLE
            breathing_led_enable_all();
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_set_duration(6 - level);
#else
            breathing_led_enable();
            breathing_led_set_duration(6 - level);
#endif
            break;
#ifdef FADING_LED_ENABLE
        case 7:
            backlight_enable();
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction(FADING_LED_FADE_IN);
            fading_led_set_duration(3);
            break;
        case 8:
            backlight_enable();
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction(FADING_LED_FADE_OUT);
            fading_led_set_duration(3);
            break;
#endif
        case 0:
        default:
#ifdef SOFTPWM_LED_ENABLE
#ifdef FADING_LED_ENABLE
            fading_led_disable_all();
#endif
            breathing_led_disable_all();
#else
            breathing_led_disable();
#endif
            backlight_disable();
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
    OCR1B = raw;
#endif
}

#ifdef SOFTPWM_LED_ENABLE
#ifndef LEDMAP_ENABLE
void softpwm_led_init(void)
{
#if defined(REV_V2)
    DDRB |= (1<<PB6);
    PORTB &= ~(1<<PB6);
#elif defined(REV_V3) || defined(REV_V3_LITE)
    DDRB |= (1<<PB7);
    PORTB &= ~(1<<PB7);
#endif
}

void softpwm_led_on(uint8_t index)
{
#if defined(REV_V2)
    PORTB |= (1<<PB6);
#elif defined(REV_V3) || defined(REV_V3_LITE)
    PORTB |= (1<<PB7);
#endif
}

void softpwm_led_off(uint8_t index)
{
#if defined(REV_V2)
    PORTB &= ~(1<<PB6);
#elif defined(REV_V3) || defined(REV_V3_LITE)
    PORTB &= ~(1<<PB7);
#endif
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
