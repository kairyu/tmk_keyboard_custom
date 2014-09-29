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
#include <util/delay.h>
#include "buzzer.h"
#include "debug.h"

void buzzer_init(void)
{
    DDRD  |=  (1<<PD1);
    PORTD &= ~(1<<PD1);
}

inline
void buzzer_on(void)
{
#ifndef EXPERIMENTAL
    PORTD |=  (1<<PD1);
#else
    PORTD |=  (1<<PD5);
#endif
}

inline
void buzzer_off(void)
{
#ifndef EXPERIMENTAL
    PORTD &= ~(1<<PD1);
#else
    PORTD &= ~(1<<PD5);
#endif
}

void buzzer(uint16_t frequency, uint16_t duration) 
{
    uint16_t delay = 100000L / (2 * frequency);
    uint16_t period = (uint32_t)frequency * duration / 1000L;
    uint16_t i;
    //dprintf("delay: %d\nperiod: %d\n", delay, period);
    do {
        buzzer_on();
        i = delay;
        do {
            _delay_us(10);
        } while (--i);
        buzzer_off();
        i = delay;
        do {
            _delay_us(10);
        } while (--i);
    } while(--period);
}
