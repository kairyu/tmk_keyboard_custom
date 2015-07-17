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

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "yc059.h"

inline
void yc059_ir_enable(void)
{
    YC059_IR_DDR  |=  (1<<YC059_IR_BIT);
}

inline
void yc059_ir_disable(void)
{
    YC059_IR_DDR  &= ~(1<<YC059_IR_BIT);
}

inline
void yc059_ir_high(void)
{
    YC059_IR_PORT &= ~(1<<YC059_IR_BIT);
}

inline
void yc059_ir_low(void)
{
    YC059_IR_PORT |=  (1<<YC059_IR_BIT);
}

void yc059_init(void)
{
    YC059_IR_DDR  &= ~(1<<YC059_IR_BIT);
    YC059_IR_PORT &= ~(1<<YC059_IR_BIT);
}

void yc059_send(uint8_t data)
{
    if (data == YC059_ERROR) return;
    cli();
    yc059_ir_enable();
    yc059_send_header();
    yc059_send_address();
    yc059_send_byte(data);
    yc059_send_byte(~data);
    yc059_send_stop();
    yc059_ir_disable();
    sei();
}

inline
void yc059_send_header(void)
{
    yc059_ir_high();
    _delay_us(YC059_HDR_MARK);
    yc059_ir_low();
    _delay_us(YC059_HDR_SPACE);
}

inline
void yc059_send_stop(void)
{
    yc059_ir_high();
    _delay_us(YC059_BIT_MARK);
    yc059_ir_low();
}

inline
void yc059_send_address(void)
{
    yc059_send_word(YC059_ADDRESS);
}

void yc059_send_byte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++) {
        yc059_ir_high();
        _delay_us(YC059_BIT_MARK);
        yc059_ir_low();
        if (byte & 1) {
            _delay_us(YC059_ONE_SPACE);
        }
        else {
            _delay_us(YC059_ZERO_SPACE);
        }
        byte >>= 1;
    }
}

void yc059_send_word(uint16_t word)
{
    yc059_send_byte((word & 0xFF00) >> 8);
    yc059_send_byte(word & 0xFF);
}
