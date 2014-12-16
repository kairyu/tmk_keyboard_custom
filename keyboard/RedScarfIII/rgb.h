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
    RGB_STATIC,
    RGB_ANIMATE
};

enum rgb_static_id {
    RGB_STATIC_RED,
    RGB_STATIC_GREEN,
    RGB_STATIC_BLUE,
    RGB_STATIC_RED_1,
    RGB_STATIC_GREEN_1,
    RGB_STATIC_BLUE_1,
    RGB_STATIC_RED_2,
    RGB_STATIC_GREEN_2,
    RGB_STATIC_BLUE_2,
    RGB_STATIC_RED_3,
    RGB_STATIC_GREEN_3,
    RGB_STATIC_BLUE_3,
    RGB_STATIC_RED_4,
    RGB_STATIC_GREEN_4,
    RGB_STATIC_BLUE_4,
    RGB_STATIC_WHITE
};

enum rgb_animate_id {
    RGB_ANIMATE_FLASH,
    RGB_ANIMATE_STROBE,
    RGB_ANIMATE_FADE,
    RGB_ANIMATE_SMOOTH
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
uint8_t rgb_to_yc059(uint8_t mode, uint8_t id);

#endif
