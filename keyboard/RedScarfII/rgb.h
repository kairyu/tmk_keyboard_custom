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

#ifndef RGB_H
#define RGB_H

#include <stdint.h>
#include <stdbool.h>

enum rgb_mode_id {
    RGB_FIXED = 0,
    RGB_VARIABLE
};

enum rgb_fixed_id {
    RGB_FIXED_WHITE = 0,
    RGB_FIXED_RED,
    RGB_FIXED_GREEN,
    RGB_FIXED_BLUE,
    RGB_FIXED_RED_1,
    RGB_FIXED_GREEN_1,
    RGB_FIXED_BLUE_1,
    RGB_FIXED_RED_2,
    RGB_FIXED_GREEN_2,
    RGB_FIXED_BLUE_2,
    RGB_FIXED_RED_3,
    RGB_FIXED_GREEN_3,
    RGB_FIXED_BLUE_3,
    RGB_FIXED_RED_4,
    RGB_FIXED_GREEN_4,
    RGB_FIXED_BLUE_4,
    RGB_FIXED_COUNT
};

enum rgb_variable_id {
    RGB_VARIABLE_FLASH = 0,
    RGB_VARIABLE_STROBE,
    RGB_VARIABLE_FADE,
    RGB_VARIABLE_SMOOTH,
    RGB_VARIABLE_COUNT
};

typedef union {
    uint8_t raw;
    struct {
        uint8_t id      :4;
        uint8_t mode    :3;
        bool    enable  :1;
    };
} rgb_config_t;

#define EECONFIG_RGB (uint8_t *)7
#define RGB_UNCONFIGURED 0xFF

void rgb_init(void);
void rgb_resume(void);
void rgb_read_config(void);
void rgb_write_config(void);
void rgb_on(void);
void rgb_off(void);
void rgb_toggle(void);
void rgb_increase(void);
void rgb_decrease(void);
void rgb_set(uint8_t mode, uint8_t id);
void rgb_step(uint8_t mode);
uint8_t rgb_to_yc059(uint8_t mode, uint8_t id);

#endif
