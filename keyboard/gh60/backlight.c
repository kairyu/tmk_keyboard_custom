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
#include "breathing_led.h"

#ifdef BACKLIGHT_ENABLE

void backlight_enable(void);
void backlight_disable(void);
inline void backlight_set_raw(uint8_t raw);

#ifdef GH60_REV_CHN
#else
#define SOFTPWM_TIMER_TOP F_CPU/(256*64)
uint8_t softpwm_ocr = 0;
uint8_t softpwm_ocr_buff = 0;
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
}

void backlight_disable(void)
{
#if defined(GH60_REV_CHN)
    // Turn off PWM
    cli();
    DDRB &= ~(1<<PB6);
    TCCR1A &= ~( (1<<WGM10) | (1<<COM1B1) );
    TCCR1B &= ~( (1<<CS11) | (1<<CS10) );
    sei();
    OCR1B = 0;
#else
    DDRF  &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    cli();
    TCCR1B &= ~(1<<WGM12);
    TCCR1B &= ~(1<<CS10);
    TIMSK1 &= ~(1<<OCIE1A);
    sei();
    OCR1A = 0;
#endif
}

void backlight_set(uint8_t level)
{
#ifdef BREATHING_LED_ENABLE
    switch (level) {
        case 1:
        case 2:
        case 3:
            backlight_enable();
            breathing_led_disable();
            backlight_set_raw(pgm_read_byte(&backlight_table[level]));
            break;
        case 4:
        case 5:
        case 6:
            backlight_enable();
            breathing_led_enable();
            breathing_led_set_duration(6 - level);
            break;
        case 0:
        default:
            breathing_led_disable();
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

#ifdef BREATHING_LED_ENABLE
void breathing_led_set_raw(uint8_t raw)
{
    backlight_set_raw(raw);
}
#endif

inline void backlight_set_raw(uint8_t raw)
{
#if defined(GH60_REV_CHN)
    OCR1B = raw;
#else
    softpwm_ocr_buff = raw;
#endif
}

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
