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

#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>

extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];

#define CONFIG_LAYER (KEYMAPS_COUNT - 1)
#define RESERVED_FN (FN_ACTIONS_COUNT - 4)

void keymaps_cache_init(void);
uint8_t last_layer(void);

/* TentaPad keymap definition macro
 */
#define KEYMAP( \
    K1, K2, TT \
) { \
    { KC_##K1, KC_##K2, KC_##TT } \
}

#endif
