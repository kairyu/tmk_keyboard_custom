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

#define KEYMAP( \
    K0A, K0B, K0C, K0D, K0E, K0F, K0G,             K0H, K0J, K0K, K0L, K0M, K0N, K0P, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G,             K1H, K1J, K1K, K1L, K1M, K1N, K1P, \
    K2A, K2B, K2C, K2D, K2E, K2F,                       K2J, K2K, K2L, K2M, K2N, K2P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G,             K3H, K3J, K3K, K3L, K3M, K3N, K3P, \
    K4A, K4B, K4C, K4D, K4E,                                 K4K, K4L, K4M, K4N, K4P, \
                                  K5F, K5G,   K5H, K5J,                               \
                                       K5E,   K5K,                                    \
                             K5D, K5C, K5B,   K5N, K5M, K5L                           \
) { \
    { KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F, KC_##K0G, KC_##K0H, KC_##K0J, KC_##K0K, KC_##K0L, KC_##K0M, KC_##K0N, KC_##K0P }, \
    { KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F, KC_##K1G, KC_##K1H, KC_##K1J, KC_##K1K, KC_##K1L, KC_##K1M, KC_##K1N, KC_##K1P }, \
    { KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F, KC_NO,    KC_NO,    KC_##K2J, KC_##K2K, KC_##K2L, KC_##K2M, KC_##K2N, KC_##K2P }, \
    { KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F, KC_##K3G, KC_##K3H, KC_##K3J, KC_##K3K, KC_##K3L, KC_##K3M, KC_##K3N, KC_##K3P }, \
    { KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K4K, KC_##K4L, KC_##K4M, KC_##K4N, KC_##K4P }, \
    { KC_NO,    KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F, KC_##K5G, KC_##K5H, KC_##K5J, KC_##K5K, KC_##K5L, KC_##K5M, KC_##K5N, KC_NO    }  \
}

#endif
