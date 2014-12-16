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

#include <avr/eeprom.h>
#include "yc059.h"
#include "rgb.h"

static rgb_config_t rgb_config;

void rgb_init(void)
{
    yc059_init();
    rgb_read_config();
    if (rgb_config.raw == RGB_UNCONFIGURED) {
        rgb_config.enable = 0;
        rgb_config.mode = RGB_STATIC;
        rgb_config.id = RGB_STATIC_WHITE;
        rgb_write_config();
    }
    yc059_send(rgb_config.enable ? YC059_ON : YC059_OFF);
    rgb_resume();
}

void rgb_resume(void)
{
    yc059_send(rgb_to_yc059(rgb_config.mode, rgb_config.id));
}

void rgb_read_config(void)
{
    rgb_config.raw = eeprom_read_byte(EECONFIG_RGB);
}

void rgb_write_config(void)
{
    eeprom_write_byte(EECONFIG_RGB, rgb_config.raw);
}

void rgb_on(void)
{
    rgb_config.enable = 1;
    yc059_send(YC059_ON);
    rgb_resume();
    rgb_write_config();
}

void rgb_off(void)
{
    rgb_config.enable = 0;
    yc059_send(YC059_OFF);
    rgb_write_config();
}

void rgb_toggle(void)
{
    rgb_config.enable ^= 1;
    yc059_send(rgb_config.enable ? YC059_ON : YC059_OFF);
    rgb_resume();
    rgb_write_config();
}

void rgb_increase(void)
{
    yc059_send(YC059_INCREASE);
}

void rgb_decrease(void)
{
    yc059_send(YC059_DECREASE);
}

void rgb_set(uint8_t mode, uint8_t id)
{
    if (rgb_config.enable) {
        rgb_config.mode = mode;
        rgb_config.id = id;
        rgb_resume();
        rgb_write_config();
    }
}

uint8_t rgb_to_yc059(uint8_t mode, uint8_t id)
{
    switch (mode) {
        case RGB_STATIC:
            if (id == RGB_STATIC_WHITE) {
                return YC059_STATIC_WHITE;
            }
            else {
                return YC059_STATIC_RED + (id / 3) * 4 + id % 3;
            }
            break;
        case RGB_ANIMATE:
            return YC059_FLASH + id * 4;
            break;
        default:
            return YC059_OFF;
            break;
    }
}
