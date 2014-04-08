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

#ifndef KEYMAP_EX_H
#define KEYMAP_EX_H

#ifdef KEYMAP_EX_ENABLE

#include <stdint.h>
#include <stdbool.h>

#define EECONFIG_KEYMAP_EX 0x10
#ifndef FN_ACTIONS_COUNT
#define FN_ACTIONS_COUNT 32
#endif
#ifndef KEYMAPS_COUNT
#define KEYMAPS_COUNT 8
#endif

typedef struct {
    uint16_t checksum;
    uint16_t fn_actions[FN_ACTIONS_COUNT];
    uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS];
} keymap_ex_t;

#define EECONFIG_KEYMAP_DEBUG (EECONFIG_KEYMAP_EX - sizeof(uint16_t))
#define EECONFIG_KEYMAP_CHECKSUM (EECONFIG_KEYMAP_EX)
#define EECONFIG_KEYMAP_FN_ACTIONS (EECONFIG_KEYMAP_EX + sizeof(uint16_t))
#define EECONFIG_KEYMAP_KEYMAPS (EECONFIG_KEYMAP_FN_ACTIONS + sizeof(uint16_t) * FN_ACTIONS_COUNT)

#define KEYS_COUNT (KEYMAPS_COUNT * MATRIX_ROWS * MATRIX_COLS)
#define KEYMAP_SIZE (sizeof(uint16_t) * FN_ACTIONS_COUNT + sizeof(uint8_t) * KEYS_COUNT)
#define FN_ACTION_OFFSET(index) (sizeof(uint16_t) * index)
#define KEY_OFFSET(layer, row, col) (sizeof(uint8_t) * (layer * MATRIX_ROWS * MATRIX_COLS + row * MATRIX_COLS + col))

void keymap_ex_init(void);
void keymap_ex_disable(void);
bool check_keymap_in_eeprom(void);
void write_keymap_to_eeprom(void);
uint8_t eeconfig_read_keymap_key(uint8_t layer, uint8_t row, uint8_t col);
void eeconfig_write_keymap_key(uint8_t layer, uint8_t row, uint8_t col, uint8_t key);
uint8_t eeconfig_read_keymap_key_by_index(uint16_t index);
void eeconfig_write_keymap_key_by_index(uint16_t index, uint8_t key);
uint16_t eeconfig_read_keymap_fn_action(uint8_t index);
void eeconfig_write_keymap_fn_action(uint8_t index, uint16_t fn_action);

const uint8_t* keymaps_pointer(void);
const uint16_t* fn_actions_pointer(void);
uint16_t keys_count(void);
uint16_t fn_actions_count(void);

#endif

#endif
