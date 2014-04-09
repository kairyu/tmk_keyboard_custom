/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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
#include <stdint.h>
#include "timer.h"


// counter resolution 1ms
// NOTE: union { uint32_t timer32; struct { uint16_t dummy; uint16_t timer16; }}
volatile uint32_t timer_count = 0;

void timer_init(void)
{
    // Timer0 CTC mode
    TCCR0A |= (1<<WGM01 | 0<<WGM00);

#if TIMER_PRESCALER == 1
    TCCR0B |= (0<<CS02 | 0<<CS01 | 1<<CS00);
#elif TIMER_PRESCALER == 8
    TCCR0B |= (0<<CS02 | 1<<CS01 | 0<<CS00);
#elif TIMER_PRESCALER == 64
    TCCR0B |= (0<<CS02 | 1<<CS01 | 1<<CS00);
#elif TIMER_PRESCALER == 256
    TCCR0B |= (1<<CS02 | 0<<CS01 | 0<<CS00);
#elif TIMER_PRESCALER == 1024
    TCCR0B |= (1<<CS02 | 0<<CS01 | 1<<CS00);
#else
#   error "Timer prescaler value is NOT vaild."
#endif

    OCR0A = TIMER_RAW_TOP;
    TIMSK0 = (1<<OCIE0A);
}

inline
void timer_clear(void)
{
    uint8_t sreg = SREG;
    cli();
    timer_count = 0;
    SREG = sreg;
}

inline
uint16_t timer_read(void)
{
    uint32_t t;

    uint8_t sreg = SREG;
    cli();
    t = timer_count;
    SREG = sreg;

    return (t & 0xFFFF);
}

inline
uint32_t timer_read32(void)
{
    uint32_t t;

    uint8_t sreg = SREG;
    cli();
    t = timer_count;
    SREG = sreg;

    return t;
}

inline
uint16_t timer_elapsed(uint16_t last)
{
    uint32_t t;

    uint8_t sreg = SREG;
    cli();
    t = timer_count;
    SREG = sreg;

    return TIMER_DIFF_16((t & 0xFFFF), last);
}

inline
uint32_t timer_elapsed32(uint32_t last)
{
    uint32_t t;

    uint8_t sreg = SREG;
    cli();
    t = timer_count;
    SREG = sreg;

    return TIMER_DIFF_32(t, last);
}

// excecuted once per 1ms.(excess for just timer count?)
ISR(TIMER0_COMPA_vect)
{
    timer_count++;
}
