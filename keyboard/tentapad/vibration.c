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
#include "timer.h"
#include "vibration.h"

static uint8_t vibration_state = 0;
static uint16_t vibration_start;
static uint16_t vibration_duration;

void vibration_task(void)
{
    if (vibration_state) {
        if (timer_elapsed(vibration_start) > vibration_duration) {
            vibration_state = 0;
            vibration_disable();
        }
    }
}

void vibration_init(void)
{
#ifndef EXPERIMENTAL
    DDRD  |=  (1<<PD6);
    PORTD &= ~(1<<PD6);
#else
    DDRD  |=  (1<<PD5);
    PORTD &= ~(1<<PD5);
#endif
}

void vibration_enable(void)
{
#ifndef EXPERIMENTAL
    PORTD |=  (1<<PD6);
#else
    PORTD |=  (1<<PD5);
#endif
}

void vibration_disable(void)
{
#ifndef EXPERIMENTAL
    PORTD &= ~(1<<PD6);
#else
    PORTD &= ~(1<<PD5);
#endif
}

void vibration(uint16_t duration)
{
    vibration_state = 1;
    vibration_start = timer_read();
    vibration_duration = duration;
    vibration_enable();
}
