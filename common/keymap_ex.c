/*
Copyright 2013 Kai Ryu <kai1103@gmail.com>

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
#include "eeconfig.h"
#include "keymap_ex.h"
#include "debug.h"

#ifdef KEYMAP_EX_ENABLE

void keymap_init(void) {
    if (!check_keymap_in_eeprom()) {
        write_keymap_to_eeprom();
    }
}

bool check_keymap_in_eeprom(void) {
    return false;
}

void write_keymap_to_eeprom(void) {
    uint16_t checksum = EECONFIG_MAGIC_NUMBER;
    const uint16_t *fn_actions = fn_actions_pointer();
    const uint8_t *keymaps = keymaps_pointer();
    // write fn_actions
    if (fn_actions != NULL) {
        uint16_t size_of_fn_actions = fn_actions_size();
        for (uint16_t i = 0; i < FN_ACTIONS_SIZE_EX; i++) {
            uint16_t fn_action = 0;
            if (i < size_of_fn_actions) {
                fn_action = pgm_read_word(fn_actions + i);
            }
            eeconfig_write_keymap_fn_action(i, fn_action);
            checksum ^= fn_action;
        }
    }
    // write keymaps
    if (keymaps != NULL) {
        uint16_t size_of_keymaps = keymaps_size();
        for (uint16_t i = 0; i < KEYMAPS_SIZE_EX; i++) {
            uint8_t keymap = 0;
            if (i < size_of_keymaps) {
                keymap = pgm_read_byte(keymaps + i);
            }
            eeconfig_write_keymap_key_by_index(i, keymap);
            uint16_t keymap_word = keymap;
            if (i & 1) {
                keymap_word = keymap << 8;
            }
            checksum ^= keymap_word;
        }
    }
    // write checksum
    eeprom_write_word(&((keymap_ex_t*)EECONFIG_KEYMAP_EX)->checksum, checksum);
}

uint8_t eeconfig_read_keymap_key(uint8_t layer, uint8_t row, uint8_t col) {
    //return eeprom_read_byte(&((keymap_ex_t*)(EECONFIG_KEYMAP_EX))->keymaps[layer][row][col]);
    return eeprom_read_byte((void*)(EECONFIG_KEYMAP_KEYMAPS + KEY_OFFSET(layer, row, col)));
}

void eeconfig_write_keymap_key(uint8_t layer, uint8_t row, uint8_t col, uint8_t key) {
    //return eeprom_write_byte(&((keymap_ex_t*)(EECONFIG_KEYMAP_EX))->keymaps[layer][row][col], key);
    return eeprom_write_byte((void*)(EECONFIG_KEYMAP_KEYMAPS + KEY_OFFSET(layer, row, col)), key);
}

uint8_t eeconfig_read_keymap_key_by_index(uint16_t index) {
    //return eeprom_read_byte(((keymap_ex_t*)(EECONFIG_KEYMAP_EX)) + index);
    return eeprom_read_byte((void*)(EECONFIG_KEYMAP_KEYMAPS + index));
}

void eeconfig_write_keymap_key_by_index(uint16_t index, uint8_t key) {
    //return eeprom_write_byte(((keymap_ex_t*)(EECONFIG_KEYMAP_EX)) + index, key);
    return eeprom_write_byte((void*)(EECONFIG_KEYMAP_KEYMAPS + index), key);
}

uint16_t eeconfig_read_keymap_fn_action(uint8_t index) {
    //return eeprom_read_word(&((keymap_ex_t*)(EECONFIG_KEYMAP_EX))->fn_actions[index]);
    return eeprom_read_word((void*)(EECONFIG_KEYMAP_FN_ACTIONS + FN_ACTION_OFFSET(index)));
}

void eeconfig_write_keymap_fn_action(uint8_t index, uint16_t fn_action) {
    //return eeprom_write_word(&((keymap_ex_t*)(EECONFIG_KEYMAP_EX))->fn_actions[index], fn_action);
    return eeprom_write_word((void*)(EECONFIG_KEYMAP_FN_ACTIONS + FN_ACTION_OFFSET(index)), fn_action);
}

#endif
