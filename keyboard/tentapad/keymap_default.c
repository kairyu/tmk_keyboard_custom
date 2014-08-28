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

#include <avr/pgmspace.h>
#include "keycode.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "backlight.h"
#include "keymap_common.h"

enum function_id {
    TOUCH_PROXIMITY = 0,
    CONFIG_MODE,
    SWITCH_LAYOUT,
    SWITCH_BACKLIGHT
};

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    [0] = KEYMAP( Z,   X,   ESC ),
    [1] = KEYMAP( BTN1,BTN2,ESC ),
    [2] = KEYMAP( LEFT,RGHT,ESC ),
    [3] = KEYMAP( UP,  DOWN,ESC ),
    [4] = KEYMAP( PGUP,PGDN,ESC ),
    [5] = KEYMAP( SPC, ESC, ESC ),
    [CONFIG_LAYER] = KEYMAP( FN30, FN31, NO )
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    [28] = ACTION_FUNCTION(TOUCH_PROXIMITY),
    [29] = ACTION_FUNCTION(CONFIG_MODE),
    [30] = ACTION_FUNCTION(SWITCH_LAYOUT),
    [31] = ACTION_FUNCTION(SWITCH_BACKLIGHT)
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

uint8_t config_mode = 0;
static uint8_t layer = 0;
static uint8_t backlight = 0;
static uint8_t layer_modified = 0;
static uint8_t backlight_modified = 0;
extern backlight_config_t backlight_config;

void enter_config_mode(void);
void exit_config_mode(void);
void switch_layout(void);
void switch_backlight(void);

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case CONFIG_MODE:
            if (record->event.pressed) {
                if (config_mode) {
                    exit_config_mode();
                }
                else {
                    enter_config_mode();
                }
            }
            break;
        case SWITCH_LAYOUT:
            if (record->event.pressed) {
                if (config_mode) {
                    switch_layout();
                }
            }
            break;
        case SWITCH_BACKLIGHT:
            if (record->event.pressed) {
                if (config_mode) {
                    switch_backlight();
                }
            }
            break;
    }
}

void enter_config_mode(void)
{
    config_mode = 1;
    layer_modified = 0;
    backlight_modified = 0;
    backlight = backlight_config.level;
    backlight_level(8);
    layer_on(CONFIG_LAYER);
}

void exit_config_mode(void)
{
    config_mode = 0;
    backlight_level(backlight);
    layer_off(CONFIG_LAYER);
    if (layer_modified) {
        default_layer_set(1UL<<layer);
        eeconfig_write_default_layer(1UL<<layer);
    }
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
    softpwm_led_set(0, 32 * (layer + 1));
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
    softpwm_led_set(1, 32 * (backlight + 1));
}
