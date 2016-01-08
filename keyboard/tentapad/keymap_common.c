/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

//#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keymap.h"
#include "keymap_in_eeprom.h"
#include "keymap_common.h"

static uint8_t keymaps_cache[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] = {{{0}}};
static uint8_t last_layer_number = 1;

void keymaps_cache_init(void)
{
    for (uint8_t layer = 0; layer < KEYMAPS_COUNT; layer++) {
        uint8_t non_empty_key = 0;
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
#ifndef KEYMAP_IN_EEPROM_ENABLE
                keymaps_cache[layer][row][col] = pgm_read_byte(&keymaps[layer][row][col]);
#else
                keymaps_cache[layer][row][col] = eeconfig_read_keymap_key(layer, row, col);
#endif
                if (keymaps_cache[layer][row][col] > KC_TRANSPARENT) {
                    non_empty_key++;
                }
            }
        }
        if (non_empty_key) {
            last_layer_number = layer;
        }
    }
}

uint8_t last_layer(void)
{
    return last_layer_number;
}

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    return keymaps_cache[layer][key.row][key.col];
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
#ifndef KEYMAP_IN_EEPROM_ENABLE
    return (action_t) {
        .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)])
    };
#else
    return (action_t) {
        .code = eeconfig_read_keymap_fn_action(FN_INDEX(keycode))
    };
#endif
}

#ifdef KEYMAP_IN_EEPROM_ENABLE
const uint8_t* keymaps_pointer(void) {
    return (const uint8_t*)keymaps;
}

const uint16_t* fn_actions_pointer(void) {
    return fn_actions;
}
#endif
