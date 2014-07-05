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
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "keymap_in_eeprom.h"


extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];


/* LR94 keymap definition macro
 * K1J, K3M and  K2B are extra keys for ISO
 */
#define KEYMAP( \
    K6A, K6B, K6C, K6D, K6E, K6F, K6G, K6H, K6I, K6J, K6K, K6L, K6M, K6N, K6P, K6Q, K0J, K5P, \
    K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K1J, K5Q, K0K, K4P, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4N, K4Q, K0L, K3P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3N, K3Q, K0M, K2P, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,      K2N, K2M, K2Q, K0N, K1P, \
    K1A, K1B, K1C,           K1F,                          K1K, K1L, K1M, K1N, K1Q, K0P, K0Q  \
) { \
    { KC_NO,    KC_##K1A, KC_##K2A, KC_##K3A, KC_##K4A, KC_##K5A, KC_##K6A }, \
    { KC_NO,    KC_##K1B, KC_##K2B, KC_##K3B, KC_##K4B, KC_##K5B, KC_##K6B }, \
    { KC_NO,    KC_##K1C, KC_##K2C, KC_##K3C, KC_##K4C, KC_##K5C, KC_##K6C }, \
    { KC_NO,    KC_NO,    KC_##K2D, KC_##K3D, KC_##K4D, KC_##K5D, KC_##K6D }, \
    { KC_NO,    KC_NO,    KC_##K2E, KC_##K3E, KC_##K4E, KC_##K5E, KC_##K6E }, \
    { KC_NO,    KC_##K1F, KC_##K2F, KC_##K3F, KC_##K4F, KC_##K5F, KC_##K6F }, \
    { KC_NO,    KC_NO,    KC_##K2G, KC_##K3G, KC_##K4G, KC_##K5G, KC_##K6G }, \
    { KC_NO,    KC_NO,    KC_##K2H, KC_##K3H, KC_##K4H, KC_##K5H, KC_##K6H }, \
    { KC_NO,    KC_NO,    KC_##K2I, KC_##K3I, KC_##K4I, KC_##K5I, KC_##K6I }, \
    { KC_##K0J, KC_##K1J, KC_##K2J, KC_##K3J, KC_##K4J, KC_##K5J, KC_##K6J }, \
    { KC_##K0K, KC_##K1K, KC_##K2K, KC_##K3K, KC_##K4K, KC_##K5K, KC_##K6K }, \
    { KC_##K0L, KC_##K1L, KC_##K2L, KC_##K3L, KC_##K4L, KC_##K5L, KC_##K6L }, \
    { KC_##K0M, KC_##K1M, KC_##K2M, KC_##K3M, KC_##K4M, KC_##K5M, KC_##K6M }, \
    { KC_##K0N, KC_##K1N, KC_##K2N, KC_##K3N, KC_##K4N, KC_##K5N, KC_##K6N }, \
    { KC_##K0P, KC_##K1P, KC_##K2P, KC_##K3P, KC_##K4P, KC_##K5P, KC_##K6P }, \
    { KC_##K0Q, KC_##K1Q, KC_##K2Q, KC_##K3Q, KC_##K4Q, KC_##K5Q, KC_##K6Q }  \
}

/* ANSI valiant. No extra keys for ISO */
#define KEYMAP_ANSI( \
    K6A,      K6C, K6D, K6E, K6F, K6G, K6H, K6I, K6J, K6K, K6L, K6M, K6N, K6P, K6Q, K0J, K5P, \
    K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M,      K5N, K5Q, K0K, K4P, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4N, K4Q, K0L, K3P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L,           K3N,                \
    K2A, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,                K2N,      K0N,      \
    K1A, K1B, K1C,           K1F,                          K1K, K1L, K1M, K1N, K1Q, K0P, K0Q  \
) KEYMAP( \
    K6A, NO,  K6C, K6D, K6E, K6F, K6G, K6H, K6I, K6J, K6K, K6L, K6M, K6N, K6P, K6Q, K0J, K5P, \
    K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, NO,  K5Q, K0K, K4P, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4N, K4Q, K0L, K3P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, NO,       K3N, NO,  NO,  NO,  \
    K2A, NO,  K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,      NO,  K2N, NO,  K0N, NO,  \
    K1A, K1B, K1C,           K1F,                          K1K, K1L, K1M, K1N, K1Q, K0P, K0Q  \
)

#endif
