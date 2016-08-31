/*
Copyright 2016 Kai Ryu <kai1103@gmail.com>

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
#include "light_ws2812.h"
#include "debug.h"

#ifdef RGB_LED_ENABLE

volatile static uint8_t rgb_fading_enable = 0;
static rgb_config_t rgb_config;
static struct cRGB rgb_color[RGB_LED_COUNT];
static uint16_t rgb_hue = 0;
static uint8_t rgb_saturation = 255;
static uint8_t rgb_brightness = 16;
static uint8_t rgb_rainbow = 0;

extern backlight_config_t backlight_config;
extern uint8_t backlight_brightness;

static void rgb_write_config(void);
static void rgb_read_config(void);
static void rgb_set_level(uint8_t level);
static void rgb_refresh(void);
#if 0
static void hue_to_rgb(uint16_t hue, struct cRGB *rgb);
#endif
static void hsb_to_rgb(uint16_t hue, uint8_t saturation, uint8_t brightness, struct cRGB *rgb);

void rgb_init(void)
{
    rgb_read_config();
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

void rgb_set_level(uint8_t level)
{
    xprintf("RGB Level: %d\n", level);
    if (level == RGB_OFF) {
        rgb_brightness = 0;
    }
    else if (backlight_config.enable) {
        if (backlight_config.level >= 1 && backlight_config.level <= 3) {
            rgb_brightness = backlight_brightness;
        }
    }
    else {
        rgb_brightness = 16;
    }
    if (level <= RGB_WHITE) {
        rgb_fading_enable = 0;
        rgb_rainbow = 0;
        if (level != RGB_OFF) {
            if (level == RGB_WHITE) {
                rgb_saturation = 0;
            }
            else {
                rgb_hue = (level - 1) * 128;
                rgb_saturation = 255;
            }
            if (backlight_config.enable) {
                if (backlight_config.level >= 1 && backlight_config.level <= 3) {
                    rgb_brightness = backlight_brightness;
                }
            }
            else {
                rgb_brightness = 16;
            }
        }
        rgb_refresh();
    }
    else {
        rgb_saturation = 255;
        rgb_fading_enable = 1;
        rgb_rainbow = (level >= RGB_RAINBOW) ? 1 : 0;
    }
}

void rgb_set_brightness(uint8_t brightness)
{
    if (rgb_config.enable) {
        rgb_brightness = brightness;
        rgb_refresh();
    }
}

void rgb_refresh(void)
{
    struct cRGB rgb;
    uint16_t hue;
    uint8_t i;
    if (rgb_rainbow) {
        for (i = 0; i < RGB_LED_COUNT; i++) {
#ifdef VER_PROTOTYPE
            uint8_t j;
            if (i == 0) j = 1;
            else if (i == 1) j = 0;
            else j = i;
#endif
            hue = rgb_hue + (768 / RGB_LED_COUNT) * i;
            hsb_to_rgb(hue, rgb_saturation, rgb_brightness, &rgb);
#ifdef VER_PROTOTYPE
            rgb_color[j] = rgb;
#else
            rgb_color[i] = rgb;
#endif
        }
    }
    else {
        hsb_to_rgb(rgb_hue, rgb_saturation, rgb_brightness, &rgb);
        for (i = 0; i < RGB_LED_COUNT; i++) {
            rgb_color[i] = rgb;
        }
    }
    /* xprintf("R%d G%d B%d\n", rgb_color[0].r, rgb_color[0].g, rgb_color[0].b); */
    ws2812_setleds(rgb_color, RGB_LED_COUNT);
}

#if 0
void hue_to_rgb(uint16_t hue, struct cRGB *rgb)
{
    uint8_t hi = hue / 60;
    uint16_t f = (hue % 60) * 425 / 100;
    uint8_t q = 255 - f;
    switch (hi) {
        case 0: rgb->r = 255; rgb->g = f;   rgb->b = 0;   break;
        case 1: rgb->r = q;   rgb->g = 255; rgb->b = 0;   break;
        case 2: rgb->r = 0;   rgb->g = 255; rgb->b = f;   break;
        case 3: rgb->r = 0;   rgb->g = q;   rgb->b = 255; break;
        case 4: rgb->r = f;   rgb->g = 0;   rgb->b = 255; break;
        case 5: rgb->r = 255; rgb->g = 0;   rgb->b = q;   break;
    }
}
#endif

/*
 * original code: https://blog.adafruit.com/2012/03/14/constant-brightness-hsb-to-rgb-algorithm/
 */
void hsb_to_rgb(uint16_t hue, uint8_t saturation, uint8_t brightness, struct cRGB *rgb)
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
    if (rgb_fading_enable) {
        if (++step > rgb_fading_enable) {
            step = 0;
            rgb_hue = hue;
            rgb_refresh();
            if (++hue >= 768) {
                hue = 0;
            }
        }
    }
}

#endif
