/*
Copyright 2013 Kai Ryu <kai1103@gmail.com>

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
#include "backlight.h"

/* Backlight pin configuration
 * PF7  PF6  PF5
 */
void backlight_set(uint8_t level)
{
    switch (level) {
        case 0:
            DDRF  &= ~(1<<PF7 | 1<<PF6 | 1<<PF5);
            break;
        case 1:
            DDRF  &= ~(1<<PF6 | 1<<PF5);
            DDRF  |=  (1<<PF7);
            PORTF &= ~(1<<PF7);
            break;
        case 2:
            DDRF  &= ~(1<<PF5);
            DDRF  |=  (1<<PF7 | 1<<PF6);
            PORTF &= ~(1<<PF7 | 1<<PF6);
            break;
        case 3:
            DDRF  |=  (1<<PF7 | 1<<PF6 | 1<<PF5);
            PORTF &= ~(1<<PF7 | 1<<PF6 | 1<<PF5);
            break;
    }
}
