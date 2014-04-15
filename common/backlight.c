/*
Copyright 2013 Mathias Andersson <wraul@dbox.se>

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

#include "backlight.h"
#include "breathing_led.h"
#include "eeconfig.h"
#include "debug.h"

backlight_config_t backlight_config;

void backlight_init(void)
{
    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    backlight_config.raw = eeconfig_read_backlight();
    backlight_set(backlight_config.enable ? backlight_config.level : 0);
}

void backlight_increase(void)
{
#if defined(BACKLIGHT_CUSTOM) || defined(BREATHING_LED_ENABLE)
    if (backlight_config.enable) {
        if (backlight_config.level < BACKLIGHT_LEVELS) {
            backlight_config.level++;
            eeconfig_write_backlight(backlight_config.raw);
        }
        dprintf("backlight custom increase: %u\n", backlight_config.level);
        backlight_set(backlight_config.level);
    }
#ifdef BREATHING_LED_ENABLE
    breathing_led_increase();
#endif
#else
    if(backlight_config.level < BACKLIGHT_LEVELS)
    {
        backlight_config.level++;
        backlight_config.enable = 1;
        eeconfig_write_backlight(backlight_config.raw);
    }
    dprintf("backlight increase: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
#endif
}

void backlight_decrease(void)
{
#if defined(BACKLIGHT_CUSTOM) || defined(BREATHING_LED_ENABLE)
    if (backlight_config.enable) {
        if(backlight_config.level > 1)
        {
            backlight_config.level--;
            eeconfig_write_backlight(backlight_config.raw);
        }
        dprintf("backlight custom decrease: %u\n", backlight_config.level);
        backlight_set(backlight_config.level);
    }
#ifdef BREATHING_LED_ENABLE
    breathing_led_decrease();
#endif
#else
    if(backlight_config.level > 0)
    {
        backlight_config.level--;
        backlight_config.enable = !!backlight_config.level;
        eeconfig_write_backlight(backlight_config.raw);
    }
    dprintf("backlight decrease: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
#endif
}

void backlight_toggle(void)
{
#ifdef BREATHING_LED_ENABLE
    if (breathing_led_is_enabled()) {
        breathing_led_disable();
        backlight_disable();
        return;
    }
#endif
    backlight_config.enable ^= 1;
    if (backlight_config.enable) {
#if defined(BACKLIGHT_CUSTOM) || defined(BREATHING_LED_ENABLE)
        backlight_enable();
#endif
        if (backlight_config.level == 0) {
            backlight_config.level = 1;
        }
    }
    else {
#ifndef BREATHING_LED_ENABLE
#ifdef BACKLIGHT_CUSTOM
        backlight_disable();
#endif
#endif
    }
    eeconfig_write_backlight(backlight_config.raw);
    dprintf("backlight toggle: %u\n", backlight_config.enable);
    backlight_set(backlight_config.enable ? backlight_config.level : 0);
#ifdef BREATHING_LED_ENABLE
    if (!backlight_config.enable) {
        breathing_led_enable();
    }
#endif
}

void backlight_step(void)
{
    backlight_config.level++;
    if(backlight_config.level > BACKLIGHT_LEVELS)
    {
        backlight_config.level = 0;
    }
    backlight_config.enable = !!backlight_config.level;
    eeconfig_write_backlight(backlight_config.raw);
    dprintf("backlight step: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}
