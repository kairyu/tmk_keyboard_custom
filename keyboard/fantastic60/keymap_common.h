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


/* TX60 keymap definition macro
 * SW44 and SW56 are extra keys for ISO
 */
#define KEYMAP( \
    SW01, SW02, SW03, SW04, SW05, SW06, SW07, SW08, SW09, SW10, SW11, SW12, SW13, SW14, SW15, \
    SW16, SW17, SW18, SW19, SW20, SW21, SW22, SW23, SW24, SW25, SW26, SW27, SW28,       SW29, \
    SW30, SW31, SW32, SW33, SW34, SW35, SW36, SW37, SW38, SW39, SW40, SW41,             SW42, \
    SW43, SW44, SW45, SW46, SW47, SW48, SW49, SW50, SW51, SW52, SW53, SW54,       SW55, SW56, \
    SW57, SW58, SW59,                   SW60,                         SW61, SW62, SW63, SW64  \
) { \
    { KC_##SW01, KC_##SW02, KC_##SW03, KC_##SW04, KC_##SW05, KC_##SW06, KC_##SW07, KC_##SW08 }, \
    { KC_##SW09, KC_##SW10, KC_##SW11, KC_##SW12, KC_##SW13, KC_##SW14, KC_##SW15, KC_##SW16 }, \
    { KC_##SW17, KC_##SW18, KC_##SW19, KC_##SW20, KC_##SW21, KC_##SW22, KC_##SW23, KC_##SW24 }, \
    { KC_##SW25, KC_##SW26, KC_##SW27, KC_##SW28, KC_##SW29, KC_##SW30, KC_##SW31, KC_##SW32 }, \
    { KC_##SW33, KC_##SW34, KC_##SW35, KC_##SW36, KC_##SW37, KC_##SW38, KC_##SW39, KC_##SW40 }, \
    { KC_##SW41, KC_##SW42, KC_##SW43, KC_##SW44, KC_##SW45, KC_##SW46, KC_##SW47, KC_##SW48 }, \
    { KC_##SW49, KC_##SW50, KC_##SW51, KC_##SW52, KC_##SW53, KC_##SW54, KC_##SW55, KC_##SW56 }, \
    { KC_##SW57, KC_##SW58, KC_##SW59, KC_##SW60, KC_##SW61, KC_##SW62, KC_##SW63, KC_##SW64 }  \
}

/* ANSI valiant. No extra keys for ISO */
#define KEYMAP_ANSI( \
    SW01, SW02, SW03, SW04, SW05, SW06, SW07, SW08, SW09, SW10, SW11, SW12, SW13, SW15, \
    SW16, SW17, SW18, SW19, SW20, SW21, SW22, SW23, SW24, SW25, SW26, SW27, SW28, SW29, \
    SW30, SW31, SW32, SW33, SW34, SW35, SW36, SW37, SW38, SW39, SW40, SW41,       SW42, \
    SW43,       SW45, SW46, SW47, SW48, SW49, SW50, SW51, SW52, SW53, SW54,       SW55, \
    SW57, SW58, SW59,                   SW60,                   SW61, SW62, SW63, SW64  \
) KEYMAP( \
    SW01, SW02, SW03, SW04, SW05, SW06, SW07, SW08, SW09, SW10, SW11, SW12, SW13, NO,   SW15, \
    SW16, SW17, SW18, SW19, SW20, SW21, SW22, SW23, SW24, SW25, SW26, SW27, SW28,       SW29, \
    SW30, SW31, SW32, SW33, SW34, SW35, SW36, SW37, SW38, SW39, SW40, SW41,             SW42, \
    SW43, NO,   SW45, SW46, SW47, SW48, SW49, SW50, SW51, SW52, SW53, SW54,       SW55, NO,   \
    SW57, SW58, SW59,                   SW60,                         SW61, SW62, SW63, SW64  \
)

#endif
