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

#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "rgb.h"
#include "light_ws2812.h"

static const uint8_t rgb_table[RGB_LEVELS][3] PROGMEM = {
    { 0,   0,   0   },
    { 255, 0,   0   },
    { 255, 127, 0   },
    { 255, 255, 0   },
    { 0,   255, 0   },
    { 0,   255, 255 },
    { 0,   0,   255 },
    { 143, 0,   255 },
    { 255, 255, 255 }
};

static rgb_config_t rgb_config;

void rgb_write_config(void);
void rgb_read_config(void);
void rgb_set(uint8_t level);

void rgb_init(void)
{
    rgb_read_config();
    if (rgb_config.raw == RGB_UNCONFIGURED) {
        rgb_config.enable = 0;
        rgb_config.level = RGB_OFF;
        rgb_write_config();
    }
    if (rgb_config.enable) {
        rgb_set(rgb_config.level);
    }
}

void rgb_read_config(void)
{
    rgb_config.raw = eeprom_read_byte(EECONFIG_RGB);
}

void rgb_write_config(void)
{
    eeprom_write_byte(EECONFIG_RGB, rgb_config.raw);
}

void rgb_toggle(void)
{
    if (rgb_config.enable) {
        rgb_off();
    }
    else {
        rgb_on();
    }
}

void rgb_on(void)
{
    rgb_config.enable = 1;
    rgb_set(rgb_config.level);
    rgb_write_config();
}

void rgb_off(void)
{
    rgb_config.enable = 0;
    rgb_set(RGB_OFF);
    rgb_write_config();
}

void rgb_decrease(void)
{
    if(rgb_config.level > 0) {
        rgb_config.level--;
        rgb_config.enable = (rgb_config.level != 0);
        rgb_write_config();
    }
    rgb_set(rgb_config.level);
}

void rgb_increase(void)
{
    if(rgb_config.level < RGB_LEVELS - 1) {
        rgb_config.level++;
        rgb_config.enable = 1;
        rgb_write_config();
    }
    rgb_set(rgb_config.level);
}

void rgb_step(void)
{
    rgb_config.level++;
    if(rgb_config.level >= RGB_LEVELS)
    {
        rgb_config.level = 0;
    }
    rgb_config.enable = (rgb_config.level != 0);
    rgb_set(rgb_config.level);
}

void rgb_set(uint8_t level)
{
    struct cRGB rgb[1];
    rgb[0].r = pgm_read_byte(&rgb_table[level][0]);
    rgb[0].g = pgm_read_byte(&rgb_table[level][1]);
    rgb[0].b = pgm_read_byte(&rgb_table[level][2]);
    ws2812_setleds(rgb, 1);
}
