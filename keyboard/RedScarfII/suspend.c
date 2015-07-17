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
#include "suspend.h"
#include "rgb.h"

#ifdef SUSPEND_ACTION

void suspend_power_down_action(void)
{
    DDRE  &= ~(1<<PE2);
    PORTE &= ~(1<<PE2);
}

void suspend_wakeup_init_action(void)
{
    rgb_init();
}

#endif
