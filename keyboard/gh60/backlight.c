/*
Copyright 2013,2014 Kai Ryu <kai1103@gmail.com>

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
#ifdef RGB_LED_ENABLE
#include "rgb_led.h"
#endif

#ifdef BACKLIGHT_ENABLE

extern backlight_config_t backlight_config;

void backlight_enable(void);
void backlight_disable(void);
inline void backlight_set_raw(uint8_t raw);

#ifndef SOFTPWM_LED_ENABLE
#ifdef GH60_REV_CHN
#else
#define SOFTPWM_TIMER_TOP F_CPU/(256*64)
uint8_t softpwm_ocr = 0;
uint8_t softpwm_ocr_buff = 0;
#endif
#endif

static const uint8_t backlight_table[] PROGMEM = {
    0, 16, 128, 255
};

/* Backlight pin configuration
 * PWM:  PB6                  (Rev.CHN)
 * GPIO: PF7  PF6  PF5  PF4   (Rev.B)
 */
void backlight_enable(void)
{
#ifdef SOFTPWM_LED_ENABLE
    softpwm_led_enable_all();
#else
#if defined(GH60_REV_CHN)
    // Turn on PWM
    DDRB |= (1<<PB6);
    cli();
    TCCR1A |= ((1<<WGM10) | (1<<COM1B1));
    TCCR1B |= ((1<<CS11) | (1<<CS10));
    sei();
#else
    DDRF  |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    cli();
    TCCR1B |= (1<<WGM12);
    TCCR1B |= (1<<CS10);
    OCR1AH = (SOFTPWM_TIMER_TOP>>8)&0xff;
    OCR1AL = SOFTPWM_TIMER_TOP&0xff;
    TIMSK1 |= (1<<OCIE1A);
    sei();
#endif
#endif
}

void backlight_disable(void)
{
#ifdef SOFTPWM_LED_ENABLE
    softpwm_led_disable_all();
#else
#if defined(GH60_REV_CHN)
    // Turn off PWM
    cli();
    DDRB &= ~(1<<PB6);
    TCCR1A &= ~( (1<<WGM10) | (1<<COM1B1) );
    TCCR1B &= ~( (1<<CS11) | (1<<CS10) );
    sei();
    OCR1B = 0;
#else
    DDRF &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    cli();
    TCCR1B &= ~(1<<WGM12);
    TCCR1B &= ~(1<<CS10);
    TIMSK1 &= ~(1<<OCIE1A);
    sei();
    OCR1A = 0;
#endif
#endif
}

void backlight_set(uint8_t level)
{
    softpwm_enable();
#ifdef BREATHING_LED_ENABLE
    switch (level) {
        case 1:
        case 2:
        case 3:
            backlight_enable();
#ifdef SOFTPWM_LED_ENABLE
            fading_led_disable_all();
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
            fading_led_disable_all();
            breathing_led_set_duration(6 - level);
#else
            breathing_led_enable();
            breathing_led_set_duration(6 - level);
#endif
            break;
        case 7:
            backlight_enable();
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction_all(FADING_LED_FADE_IN);
            fading_led_set_duration(3);
            break;
        case 8:
            backlight_enable();
            fading_led_enable_all();
            breathing_led_disable_all();
            fading_led_set_direction_all(FADING_LED_FADE_OUT);
            fading_led_set_duration(3);
            break;
        case 0:
        default:
#ifdef SOFTPWM_LED_ENABLE
            fading_led_disable_all();
            breathing_led_disable_all();
            backlight_set_raw(0);
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
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        softpwm_led_set(i, raw);
    }
#else
#if defined(GH60_REV_CHN)
    OCR1B = raw;
#else
    softpwm_ocr_buff = raw;
#endif
#endif
}

#ifdef SOFTPWM_LED_ENABLE
#ifndef LEDMAP_ENABLE

void softpwm_led_init(void)
{
#if defined(GH60_REV_CHN)
    DDRB |= (1<<PB6);
#else
    DDRF  |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
#endif
}

void softpwm_led_on(uint8_t index)
{
#if defined(GH60_REV_CHN)
    PORTB |= (1<<PB6);
#else
    PORTF &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
#endif
}

void softpwm_led_off(uint8_t index)
{
#if defined(GH60_REV_CHN)
    PORTB &= ~(1<<PB6);
#else
    PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
#endif
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
                fading_led_set_delay_all(32);
                softpwm_led_decrease_all(16);
            }
        }
        if (backlight_config.level == 8) {
            if (event.pressed) {
                fading_led_set_delay_all(32);
                softpwm_led_increase_all(16);
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


#ifndef SOFTPWM_LED_ENABLE
#if defined(GH60_REV_CHN)
#else
ISR(TIMER1_COMPA_vect)
{
    static uint8_t pwm = 0;
    pwm++;
    // LED on
    if (pwm == 0) {
        //PORTB |= (1<<PB6);
        PORTF &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
        softpwm_ocr = softpwm_ocr_buff;
    }
    // LED off
    if (pwm == softpwm_ocr) {
        //PORTB &= ~(1<<PB6);
        PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    }
}
#endif
#endif

#endif
