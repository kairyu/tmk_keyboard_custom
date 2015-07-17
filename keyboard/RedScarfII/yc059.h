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

#ifndef YC059_H
#define YC059_H

#include <stdint.h>

#define YC059_FREQ          38000
#define YC059_ADDRESS       0x00EF

#define YC059_HDR_MARK      9000
#define YC059_HDR_SPACE     4500
#define YC059_BIT_MARK      560
#define YC059_ONE_SPACE     1600
#define YC059_ZERO_SPACE    560
#define YC059_RPT_SPACE     2250

#define YC059_IR_DDR        DDRC
#define YC059_IR_PORT       PORTC
#define YC059_IR_BIT        PC6

enum yc059_id {
    YC059_INCREASE = 0,
    YC059_DECREASE,
    YC059_OFF,
    YC059_ON,
    YC059_FIXED_RED,
    YC059_FIXED_GREEN,
    YC059_FIXED_BLUE,
    YC059_FIXED_WHITE,
    YC059_FIXED_RED_1,
    YC059_FIXED_GREEN_1,
    YC059_FIXED_BLUE_1,
    YC059_FLASH,
    YC059_FIXED_RED_2,
    YC059_FIXED_GREEN_2,
    YC059_FIXED_BLUE_2,
    YC059_STROBE,
    YC059_FIXED_RED_3,
    YC059_FIXED_GREEN_3,
    YC059_FIXED_BLUE_3,
    YC059_FADE,
    YC059_FIXED_RED_4,
    YC059_FIXED_GREEN_4,
    YC059_FIXED_BLUE_4,
    YC059_SMOOTH,
    YC059_ERROR = 0xFF
};

void yc059_init(void);
void yc059_send(uint8_t data);
void yc059_send_header(void);
void yc059_send_address(void);
void yc059_send_byte(uint8_t byte);
void yc059_send_word(uint16_t word);
void yc059_send_stop(void);

#endif
