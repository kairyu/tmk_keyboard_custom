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

/* GHPad keymap definition macro
 */
#define KEYMAP( \
    K0A, K0B, K0C, K0D, \
    K1A, K1B, K1C, K1D, \
    K2A, K2B, K2C, K2D, \
    K3A, K3B, K3C, K3D, \
    K4A, K4B, K4C, K4D, \
    K5A, K5B, K5C, K5D  \
) { \
    { KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D }, \
    { KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D }, \
    { KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D }, \
    { KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D }, \
    { KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D }, \
    { KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D }  \
}

#endif
