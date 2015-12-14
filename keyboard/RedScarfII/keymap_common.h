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
#include "action_util.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "keymap_in_eeprom.h"


extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];


/* RedScarfII keymap definition macro
 * K3B and K2M are extra keys for ISO
 */
#define KEYMAP( \
    K5B, K5C, K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H, K0I, K0J, K0K, K0L, K0M, K0N, K0P, K0Q, K0R, K0S, \
    K5D, K5E, K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M, K1N, K1P, K1Q, K1R, K1S, \
    K5F, K5G, K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M, K2N, K2P, K2Q, K2R, K2S, \
    K5H, K5I, K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N, K3P, K3Q, K3R, K3S, \
    K5J, K5K, K4A, K4B, K4C,           K4J,                K4K, K4L, K4H, K4M, K4N, K4P, K4Q, K4R, K4S  \
) { \
    { KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F, KC_##K0G, KC_##K0H, KC_##K0I, KC_##K0J, KC_##K0K, KC_##K0L, KC_##K0M, KC_##K0N, KC_##K0P, KC_##K0Q, KC_##K0R, KC_##K0S }, \
    { KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F, KC_##K1G, KC_##K1H, KC_##K1I, KC_##K1J, KC_##K1K, KC_##K1L, KC_##K1M, KC_##K1N, KC_##K1P, KC_##K1Q, KC_##K1R, KC_##K1S }, \
    { KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F, KC_##K2G, KC_##K2H, KC_##K2I, KC_##K2J, KC_##K2K, KC_##K2L, KC_##K2M, KC_##K2N, KC_##K2P, KC_##K2Q, KC_##K2R, KC_##K2S }, \
    { KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F, KC_##K3G, KC_##K3H, KC_##K3I, KC_##K3J, KC_##K3K, KC_##K3L, KC_##K3M, KC_##K3N, KC_##K3P, KC_##K3Q, KC_##K3R, KC_##K3S }, \
    { KC_##K4A, KC_##K4B, KC_##K4C, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K4H, KC_NO,    KC_##K4J, KC_##K4K, KC_##K4L, KC_##K4M, KC_##K4N, KC_##K4P, KC_##K4Q, KC_##K4R, KC_##K4S },  \
    { KC_NO,    KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F, KC_##K5G, KC_##K5H, KC_##K5I, KC_##K5J, KC_##K5K, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
}

/* No extra F1-F10 keys */
#define KEYMAP_NORMAL( \
    K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H, K0I, K0J, K0K, K0L, K0M, K0N, K0P, K0Q, K0R, K0S, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M, K1N, K1P, K1Q, K1R, K1S, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M, K2N, K2P, K2Q, K2R, K2S, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N, K3P, K3Q, K3R, K3S, \
    K4A, K4B, K4C,           K4J,                K4K, K4L, K4H, K4M, K4N, K4P, K4Q, K4R, K4S  \
) KEYMAP( \
    NO,  NO,  K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H, K0I, K0J, K0K, K0L, K0M, K0N, K0P, K0Q, K0R, K0S, \
    NO,  NO,  K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M, K1N, K1P, K1Q, K1R, K1S, \
    NO,  NO,  K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M, K2N, K2P, K2Q, K2R, K2S, \
    NO,  NO,  K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N, K3P, K3Q, K3R, K3S, \
    NO,  NO,  K4A, K4B, K4C,           K4J,                K4K, K4L, K4H, K4M, K4N, K4P, K4Q, K4R, K4S  \
)

/* ANSI valiant. No extra keys for ISO */
#define KEYMAP_ANSI( \
    K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H, K0I, K0J, K0K, K0L, K0M, K0N, K0P, K0Q, K0R, K0S, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M, K1N, K1P, K1Q, K1R,      \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,      K2N, K2P, K2Q, K2R, K2S, \
    K3A,      K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N, K3P, K3Q, K3R,      \
    K4A, K4B, K4C,           K4I,                K4K, K4L, K4H, K4M, K4N, K4P, K4Q, K4R, K4S  \
) KEYMAP_NORMAL( \
    K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H, K0I, K0J, K0K, K0L, K0M, K0N, K0P, K0Q, K0R, K0S, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M, K1N, K1P, K1Q, K1R, NO,  \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, NO,  K2N, K2P, K2Q, K2R, K2S, \
    K3A, NO,  K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N, K3P, K3Q, K3R, NO,  \
    K4A, K4B, K4C,           K4I,                K4K, K4L, K4H, K4M, K4N, K4P, K4Q, K4R, K4S  \
)

#endif
