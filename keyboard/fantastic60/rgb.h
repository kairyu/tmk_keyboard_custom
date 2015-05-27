/*
Copyright 2015 Kai Ryu <kai1103@gmail.com>

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

typedef union {
    uint8_t raw;
    struct {
        uint8_t level  :7;
        bool    enable :1;
    };
} rgb_config_t;

typedef union {
    uint8_t raw[3];
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
} rgb_color_t;

enum {
    RGB_OFF = 0,
    RGB_FIXED,
    RGB_FADE_SLOW,
    RGB_FADE_MID,
    RGB_FADE_FAST,
    RGB_LEVELS = RGB_FADE_FAST
};

enum {
    RGB_R = 0,
    RGB_G,
    RGB_B,
};

#define EECONFIG_RGB_CONFIG (uint8_t *)8
#define EECONFIG_RGB_COLOR  (uint8_t *)9
#define RGB_UNCONFIGURED 0xFF

void rgb_init(void);
void rgb_toggle(void);
void rgb_on(void);
void rgb_off(void);
void rgb_decrease(void);
void rgb_increase(void);
void rgb_step(void);
void rgb_color_decrease(uint8_t color);
void rgb_color_increase(uint8_t color);
void rgb_set_brightness(uint8_t brightness);
void rgb_fading(void);

#endif
