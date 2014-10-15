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

#include <stdint.h>
#include <util/delay.h>
#include "action.h"
#include "action_layer.h"
#include "backlight.h"
#include "softpwm_led.h"
#include "eeconfig.h"
#include "keymap_common.h"
#include "vibration.h"
#include "pitches.h"
#include "buzzer.h"
#include "tentapad.h"
#include "debug.h"

static const uint16_t tones[] PROGMEM = {
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,
    NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6,
    NOTE_C7
};

uint8_t config_mode = 0;
static uint8_t layer = 0;
static uint8_t backlight = 0;
static uint8_t layer_modified = 0;
static uint8_t backlight_modified = 0;
extern uint8_t backlight_mode;
extern const uint8_t backlight_brightness_mid;
extern const uint8_t backlight_brightness_high;

void action_keyevent(keyevent_t event)
{
    uint8_t key = event.key.col;
    if (config_mode) {
        /* config mode */
        switch (key) {
            case KEY_K1:
                if (event.pressed) {
                    switch_layout();
                }
                break;
            case KEY_K2:
                if (event.pressed) {
                    switch_backlight();
                }
                break;
            case KEY_CFG:
                if (event.pressed) {
                    exit_config_mode();
                }
                break;
        }
    }
    else {
        /* normal mode */
        switch (key) {
            case KEY_K1: case KEY_K2:
                if (event.pressed) {
                    /* press */
                    switch (backlight_mode) {
                        case 0: case 6:
                            softpwm_led_on(key);
                            break;
                        case 1: case 2:
                            softpwm_led_increase(LED_KEY_SIDE - 1 + backlight_mode, 32);
                        case 3 ... 5:
                            softpwm_led_set(key, backlight_brightness_high);
                            break;
                    }
                }
                else {
                    /* release */
                    switch (backlight_mode) {
                        case 0: case 6:
                            softpwm_led_off(key);
                            break;
                        case 1 ... 5:
                            softpwm_led_set(key, 0);
                            break;
                    }
                }
                break;
            case KEY_TT:
                if (event.pressed) {
                    vibration(32);
                    switch (backlight_mode) {
                        case 1: case 2:
                            softpwm_led_increase(LED_KEY_SIDE - 1 + backlight_mode, 32);
                            break;
                    }
                }
                break;
            case KEY_TP:
                switch (backlight_mode) {
                    case 1: case 5:
                        if (event.pressed) {
                            softpwm_led_set(LED_BOARD_SIDE, backlight_brightness_high);
                        }
                        else {
                            softpwm_led_set(LED_BOARD_SIDE, backlight_brightness_mid);
                        }
                        break;
                    case 2: case 4:
                        if (event.pressed) {
                            softpwm_led_set(LED_KEY_SIDE, backlight_brightness_high);
                        }
                        else {
                            softpwm_led_set(LED_KEY_SIDE, backlight_brightness_mid);
                        }
                        break;
                }
                break;
            case KEY_CFG:
                if (event.pressed) {
                    enter_config_mode();
                }
                break;
        }
    }
}

void enter_config_mode(void)
{
    config_mode = 1;
    layer_modified = 0;
    backlight_modified = 0;
    backlight = backlight_mode;
    backlight_level(8);
    softpwm_led_set(0, 32 * (layer + 1));
    softpwm_led_set(1, 32 * (backlight + 1));
    buzzer(pgm_read_word(&tones[0]), 50);
    buzzer(pgm_read_word(&tones[2]), 50);
    buzzer(pgm_read_word(&tones[4]), 50);
    buzzer(pgm_read_word(&tones[7]), 50);
}

void exit_config_mode(void)
{
    config_mode = 0;
    backlight_level(backlight);
    if (layer_modified) {
        default_layer_set(1UL<<layer);
        eeconfig_write_default_layer(1UL<<layer);
    }
    buzzer(pgm_read_word(&tones[7]), 50);
    buzzer(pgm_read_word(&tones[4]), 50);
    buzzer(pgm_read_word(&tones[2]), 50);
    buzzer(pgm_read_word(&tones[0]), 50);
}

void switch_layout(void)
{
    if (!layer_modified) {
        layer = 0;
        layer_modified = 1;
    }
    else {
        layer = (layer + 1) % (last_layer() + 1);
    }
    dprintf("layer: %d\n", layer);
    dprintf("last layer: %d\n", last_layer());
    set_layer_indicator(layer);
}

void switch_backlight(void)
{
    if (!backlight_modified) {
        backlight = 0;
        backlight_modified = 1;
    }
    else {
        backlight = (backlight + 1) % (BACKLIGHT_LEVELS);
    }
    dprintf("backlight: %d\n", backlight);
    set_backlight_indicator(backlight);
}

void set_layer_indicator(uint8_t layer)
{
    layer = (layer < 7) ? layer : 7;
    softpwm_led_set(0, 32 * (layer + 1) - 1);
    buzzer(pgm_read_word(&tones[layer]), 50);
    if (layer == 0) {
        _delay_ms(10);
        buzzer(pgm_read_word(&tones[layer]), 50);
    }
}

void set_backlight_indicator(uint8_t backlight)
{
    softpwm_led_set(1, 32 * (backlight + 1) - 1);
    buzzer(pgm_read_word(&tones[7 + backlight]), 50);
    if (backlight == 0) {
        _delay_ms(10);
        buzzer(pgm_read_word(&tones[7 + backlight]), 50);
    }
}
