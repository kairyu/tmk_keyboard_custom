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
#include "softpwm_led.h"
#include "backlight.h"
#include "rgb.h"

volatile static uint8_t rgb_fading_enable = 0;
static rgb_config_t rgb_config;
static rgb_color_t rgb_color;
static uint16_t rgb_hue = 0;
const uint8_t rgb_saturation = 255;
static uint8_t rgb_brightness = 16;

extern backlight_config_t backlight_config;
extern uint8_t backlight_brightness;

static void rgb_write_config(void);
static void rgb_read_config(void);
static void rgb_write_color(void);
static void rgb_read_color(void);
static void rgb_set_level(uint8_t level);
static void rgb_refresh(rgb_color_t *rgb);
static void hsb_to_rgb(uint16_t hue, uint8_t saturation, uint8_t brightness, rgb_color_t *rgb);

void rgb_init(void)
{
    /* shift_register_init(); */
    /* shift_register_write_word(0xFFFF); */
    rgb_read_config();
    rgb_read_color();
    if (rgb_config.raw == RGB_UNCONFIGURED) {
        rgb_config.enable = 0;
        rgb_config.level = RGB_OFF;
        rgb_write_config();
    }
    if (rgb_config.enable) {
        rgb_set_level(rgb_config.level);
    }
}

void rgb_read_config(void)
{
    rgb_config.raw = eeprom_read_byte(EECONFIG_RGB_CONFIG);
}

void rgb_write_config(void)
{
    eeprom_write_byte(EECONFIG_RGB_CONFIG, rgb_config.raw);
}

void rgb_read_color(void)
{
    for (uint8_t i = 0; i < 3; i++) {
        rgb_color.raw[i] = eeprom_read_byte(EECONFIG_RGB_COLOR + i);
    }
}

void rgb_write_color(void)
{
    for (uint8_t i = 0; i < 3; i++) {
        eeprom_write_byte(EECONFIG_RGB_COLOR + i, rgb_color.raw[i]);
    }
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
    rgb_set_level(rgb_config.level);
    rgb_write_config();
}

void rgb_off(void)
{
    rgb_config.enable = 0;
    rgb_set_level(RGB_OFF);
    rgb_write_config();
}

void rgb_decrease(void)
{
    if(rgb_config.level > 0) {
        rgb_config.level--;
        rgb_config.enable = (rgb_config.level != 0);
        rgb_write_config();
    }
    rgb_set_level(rgb_config.level);
}

void rgb_increase(void)
{
    if(rgb_config.level < RGB_LEVELS) {
        rgb_config.level++;
        rgb_config.enable = 1;
        rgb_write_config();
    }
    rgb_set_level(rgb_config.level);
}

void rgb_step(void)
{
    rgb_config.level++;
    if(rgb_config.level > RGB_LEVELS)
    {
        rgb_config.level = 0;
    }
    rgb_config.enable = (rgb_config.level != 0);
    rgb_set_level(rgb_config.level);
}

void rgb_color_increase(uint8_t color)
{
    uint8_t *c = &rgb_color.raw[color];
    if (*c >= 240) {
        *c = 255;
    }
    else {
        *c += 16;
    }
    rgb_refresh(&rgb_color);
    rgb_write_color();
}

void rgb_color_decrease(uint8_t color)
{
    uint8_t *c = &rgb_color.raw[color];
    if (*c > 240) {
        *c = 240;
    }
    else if (*c < 16) {
        *c = 0;
    }
    else {
        *c -= 16;
    }
    rgb_refresh(&rgb_color);
    rgb_write_color();
}

void rgb_set_level(uint8_t level)
{
    rgb_color_t rgb_color_off = { .raw = {0} };
    switch (level) {
        case RGB_OFF:
            rgb_fading_enable = 0;
            rgb_brightness = 0;
            rgb_refresh(&rgb_color_off);
            /* shift_register_write_word(0xFFFF); */
            break;
        case RGB_FIXED:
            rgb_refresh(&rgb_color);
            /* shift_register_write_word(0x0000); */
            break;
        case RGB_FADE_SLOW:
        case RGB_FADE_MID:
        case RGB_FADE_FAST:
            if (backlight_config.enable) {
                if (backlight_config.level >= 1 && backlight_config.level <= 3) {
                    rgb_brightness = backlight_brightness;
                }
            }
            else {
                rgb_brightness = 16;
            }
            rgb_fading_enable = 3 - (level - RGB_FADE_SLOW);
            /* shift_register_write_word(0x0000); */
            break;
    }
}

void rgb_set_brightness(uint8_t brightness)
{
    rgb_brightness = brightness;
}

void rgb_refresh(rgb_color_t *rgb)
{
    for (uint8_t i = 0; i < 3; i++) {
        softpwm_led_set(i + 1, rgb->raw[i]);
    }
}

/*
 * original code: https://blog.adafruit.com/2012/03/14/constant-brightness-hsb-to-rgb-algorithm/
 */
void hsb_to_rgb(uint16_t hue, uint8_t saturation, uint8_t brightness, rgb_color_t *rgb)
{
    uint8_t temp[5];
    uint8_t n = (hue >> 8) % 3;
    uint8_t x = ((((hue & 255) * saturation) >> 8) * brightness) >> 8;
    uint8_t s = ((256 - saturation) * brightness) >> 8;
    temp[0] = temp[3] = s;
    temp[1] = temp[4] = x + s;
    temp[2] = brightness - x;
    rgb->r = temp[n + 2];
    rgb->g = temp[n + 1];
    rgb->b = temp[n];
}

void rgb_fading(void)
{
    static uint8_t step = 0;
    static uint16_t hue = 0;
    static rgb_color_t color;
    if (rgb_fading_enable) {
        if (++step > rgb_fading_enable) {
            step = 0;
            rgb_hue = hue;
            hsb_to_rgb(rgb_hue, rgb_saturation, rgb_brightness, &color);
            rgb_refresh(&color);
            if (++hue >= 768) {
                hue = 0;
            }
        }
    }
}
