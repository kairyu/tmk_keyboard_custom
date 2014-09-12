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

/* AKB96 keymap definition macro
 */
#define KEYMAP( \
    KA0, KB0, KC0, KD0, KE0, KF0, KG0, KH0, KI0, KJ0, KK0, KL0, KM0, KN0, KP0, KQ0, KR0, KS0, KS1, \
    KA1, KB1, KC1, KD1, KE1, KF1, KG1, KH1, KI1, KJ1, KK1, KL1, KM1,      KN1, KP1, KQ1, KR1, KS2, \
    KA2, KB2, KC2, KD2, KE2, KF2, KG2, KH2, KI2, KJ2, KK2, KL2, KM2,      KN2, KP2, KQ2, KR2, KS3, \
    KA3, KB3, KC3, KD3, KE3, KF3, KG3, KH3, KI3, KJ3, KK3, KL3,           KN3, KP3, KQ3, KR3,      \
    KA4, KB4, KC4, KD4, KE4, KF4, KG4, KH4, KI4, KJ4, KK4,           KL4, KN4, KP4, KQ4, KR4, KS5, \
    KA5, KB5, KC5,           KF5,                KJ5, KK5, KL5,           KN5, KP5, KQ5, KR5       \
) { \
    { KC_##KA0, KC_##KA1, KC_##KA2, KC_##KA3, KC_##KA4, KC_##KA5 }, \
    { KC_##KB0, KC_##KB1, KC_##KB2, KC_##KB3, KC_##KB4, KC_##KB5 }, \
    { KC_##KC0, KC_##KC1, KC_##KC2, KC_##KC3, KC_##KC4, KC_##KC5 }, \
    { KC_##KD0, KC_##KD1, KC_##KD2, KC_##KD3, KC_##KD4, KC_NO    }, \
    { KC_##KE0, KC_##KE1, KC_##KE2, KC_##KE3, KC_##KE4, KC_NO    }, \
    { KC_##KF0, KC_##KF1, KC_##KF2, KC_##KF3, KC_##KF4, KC_##KF5 }, \
    { KC_##KG0, KC_##KG1, KC_##KG2, KC_##KG3, KC_##KG4, KC_NO    }, \
    { KC_##KH0, KC_##KH1, KC_##KH2, KC_##KH3, KC_##KH4, KC_NO    }, \
    { KC_##KI0, KC_##KI1, KC_##KI2, KC_##KI3, KC_##KI4, KC_NO    }, \
    { KC_##KJ0, KC_##KJ1, KC_##KJ2, KC_##KJ3, KC_##KJ4, KC_##KJ5 }, \
    { KC_##KK0, KC_##KK1, KC_##KK2, KC_##KK3, KC_##KK4, KC_##KK5 }, \
    { KC_##KL0, KC_##KL1, KC_##KL2, KC_##KL3, KC_##KL4, KC_##KL5 }, \
    { KC_##KM0, KC_##KM1, KC_##KM2, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##KN0, KC_##KN1, KC_##KN2, KC_##KN3, KC_##KN4, KC_##KN5 }, \
    { KC_##KP0, KC_##KP1, KC_##KP2, KC_##KP3, KC_##KP4, KC_##KP5 }, \
    { KC_##KQ0, KC_##KQ1, KC_##KQ2, KC_##KQ3, KC_##KQ4, KC_##KQ5 }, \
    { KC_##KR0, KC_##KR1, KC_##KR2, KC_##KR3, KC_##KR4, KC_##KR5 }, \
    { KC_##KS0, KC_##KS1, KC_##KS2, KC_##KS3, KC_NO,    KC_##KS5 }  \
}

#endif
