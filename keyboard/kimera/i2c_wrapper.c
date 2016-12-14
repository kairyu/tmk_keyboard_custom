/*
Copyright 2016 Kai Ryu <kai1103@gmail.com>

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

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "timer.h"
#include "i2cmaster.h"
#include "i2c_wrapper.h"
#include "debug.h"

void i2c_wrapper_init(void)
{
    dprintf("I2C Init\n");

    /* init timer */
    timer_init();

    /* init i2c */
    i2c_init();
}

void i2c_wrapper_task(void)
{
}
