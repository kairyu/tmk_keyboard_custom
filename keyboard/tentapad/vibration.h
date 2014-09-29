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

#ifndef VIBRATION_H
#define VIBRATION_H

#include <stdint.h>

void vibration_init(void);
void vibration_task(void);
void vibration_enable(void);
void vibration_disable(void);
void vibration(uint16_t duration);

#endif
