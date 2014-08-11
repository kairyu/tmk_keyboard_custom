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
    CONFIG_MODE = 0,
    SWITCH_LAYOUT,
    SWITCH_BACKLIGHT
};

enum {
    CONFIG_LAYER = 8,
};

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    [0]  = KEYMAP( Z,   X,   ESC, NO,  FN0 ),
    [1]  = KEYMAP( BTN1,BTN2,ESC, NO,  FN0 ),
    [2]  = KEYMAP( LEFT,RGHT,ESC, NO,  FN0 ),
    [3]  = KEYMAP( UP,  DOWN,ESC, NO,  FN0 ),
    [4]  = KEYMAP( PGUP,PGDN,ESC, NO,  FN0 ),
    [5]  = KEYMAP( SPC, ESC, ESC, NO,  FN0 ),
    [CONFIG_LAYER] = KEYMAP( FN1, FN2, NO,  NO,  FN0 ),
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_FUNCTION(CONFIG_MODE),
    [1] = ACTION_FUNCTION(SWITCH_LAYOUT),
    [2] = ACTION_FUNCTION(SWITCH_BACKLIGHT)
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    static uint8_t config_mode = 0;
    static uint8_t layer = 0;
    static uint8_t backlight = 0;
    switch (id) {
        case CONFIG_MODE:
            if (record->event.pressed) {
                if (config_mode) {
                    config_mode = 0;
                    layer_off(CONFIG_LAYER);
                }
                else {
                    config_mode = 1;
                    layer = 0;
                    backlight = 0;
                    layer_on(CONFIG_LAYER);
                }
            }
            break;
        case SWITCH_LAYOUT:
            if (record->event.pressed) {
                if (config_mode) {
                    default_layer_set(1UL<<layer);
                    eeconfig_write_default_layer(1UL<<layer);
                    layer = (layer + 1) % 6;
                }
            }
            break;
        case SWITCH_BACKLIGHT:
            if (record->event.pressed) {
                if (config_mode) {
                    backlight_level(backlight);
                    backlight = (backlight + 1) % (BACKLIGHT_LEVELS + 1);
                }
            }
            break;
    }
}
