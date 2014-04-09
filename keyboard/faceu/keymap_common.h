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
#include "keymap_ex.h"


/*
#ifdef KEYMAP_EX_ENABLE
extern const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[FN_ACTIONS_COUNT];
#else
*/
extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];
//#endif


/* GH60 keymap definition macro
 * K95 and K42 are extra keys for ISO
 * KB2 is extra key for HHKB
 */
#define KEYMAP( \
    K27, K28, K38, K48, K58, K57, K67, K68, K78, K88, K98, K97, K77, KB7, KB2, \
    K22, K21, K31, K41, K51, K52, K62, K61, K71, K81, K91, K92, K72, KB3, \
    K32, K23, K33, K43, K53, K54, K64, K63, K73, K83, K93, K94, K95, KB5, \
    KA2, K42, K25, K35, K45, K55, K56, K66, K65, K75, K85, K96, KA5, KB6, \
    KA1, KB1, KA4,                KB4,                KA6, KA7, K86, KA3  \
) { \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##K21, KC_##K22, KC_##K23, KC_NO,    KC_##K25, KC_NO,    KC_##K27, KC_##K28 }, \
    { KC_##K31, KC_##K32, KC_##K33, KC_NO,    KC_##K35, KC_NO,    KC_NO,    KC_##K38 }, \
    { KC_##K41, KC_##K42, KC_##K43, KC_NO,    KC_##K45, KC_NO,    KC_NO,    KC_##K48 }, \
    { KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57, KC_##K58 }, \
    { KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67, KC_##K68 }, \
    { KC_##K71, KC_##K72, KC_##K73, KC_NO,    KC_##K75, KC_NO,    KC_##K77, KC_##K78 }, \
    { KC_##K81, KC_NO,    KC_##K83, KC_NO,    KC_##K85, KC_##K86, KC_NO,    KC_##K88 }, \
    { KC_##K91, KC_##K92, KC_##K93, KC_##K94, KC_##K95, KC_##K96, KC_##K97, KC_##K98 }, \
    { KC_##KA1, KC_##KA2, KC_##KA3, KC_##KA4, KC_##KA5, KC_##KA6, KC_##KA7, KC_NO,   }, \
    { KC_##KB1, KC_##KB2, KC_##KB3, KC_##KB4, KC_##KB5, KC_##KB6, KC_##KB7, KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
}

/* ANSI valiant. No extra keys for ISO */
#define KEYMAP_ANSI( \
    K27, K28, K38, K48, K58, K57, K67, K68, K78, K88, K98, K97, K77, KB7, \
    K22, K21, K31, K41, K51, K52, K62, K61, K71, K81, K91, K92, K72, KB3, \
    K32, K23, K33, K43, K53, K54, K64, K63, K73, K83, K93, K94,      KB5, \
    KA2, K25, K35, K45, K55, K56, K66, K65, K75, K85, K96,           KA5, \
    KA1, KB1, KA4,                KB4,                KA6, KA7, K86, KA3  \
) KEYMAP( \
    K27, K28, K38, K48, K58, K57, K67, K68, K78, K88, K98, K97, K77, KB7, NO, \
    K22, K21, K31, K41, K51, K52, K62, K61, K71, K81, K91, K92, K72, KB3, \
    K32, K23, K33, K43, K53, K54, K64, K63, K73, K83, K93, K94, NO,  KB5, \
    KA2, NO,  K25, K35, K45, K55, K56, K66, K65, K75, K85, K96, KA5, NO,  \
    KA1, KB1, KA4,                KB4,                KA6, KA7, K86, KA3  \
)

/* Winkeyless valiant. No context key */
#define KEYMAP_WINKEYLESS( \
    K27, K28, K38, K48, K58, K57, K67, K68, K78, K88, K98, K97, K77, KB7, \
    K22, K21, K31, K41, K51, K52, K62, K61, K71, K81, K91, K92, K72, KB3, \
    K32, K23, K33, K43, K53, K54, K64, K63, K73, K83, K93, K94,      KB5, \
    KA2, K25, K35, K45, K55, K56, K66, K65, K75, K85, K96,           KA5, \
    KA1, KB1, KA4,                KB4,                     KA7, K86, KA3  \
) KEYMAP_ANSI( \
    K27, K28, K38, K48, K58, K57, K67, K68, K78, K88, K98, K97, K77, KB7, \
    K22, K21, K31, K41, K51, K52, K62, K61, K71, K81, K91, K92, K72, KB3, \
    K32, K23, K33, K43, K53, K54, K64, K63, K73, K83, K93, K94,      KB5, \
    KA2, K25, K35, K45, K55, K56, K66, K65, K75, K85, K96,           KA5, \
    KA1, KB1, KA4,                KB4,                KA6, NO,  K86, KA3  \
)

#define KEYMAP_HHKB( \
    K27, K28, K38, K48, K58, K57, K67, K68, K78, K88, K98, K97, K77, KB7, KB2, \
    K22, K21, K31, K41, K51, K52, K62, K61, K71, K81, K91, K92, K72, KB3, \
    K32, K23, K33, K43, K53, K54, K64, K63, K73, K83, K93, K94,      KB5, \
    KA2, K25, K35, K45, K55, K56, K66, K65, K75, K85, K96,      KA5, KB6, \
    KA1, KB1, KA4,                KB4,                KA6, KA7, K86, KA3  \
) KEYMAP( \
    K27, K28, K38, K48, K58, K57, K67, K68, K78, K88, K98, K97, K77, KB7, KB2, \
    K22, K21, K31, K41, K51, K52, K62, K61, K71, K81, K91, K92, K72, KB3, \
    K32, K23, K33, K43, K53, K54, K64, K63, K73, K83, K93, K94, NO,  KB5, \
    KA2, NO,  K25, K35, K45, K55, K56, K66, K65, K75, K85, K96, KA5, KB6, \
    KA1, KB1, KA4,                KB4,                KA6, KA7, K86, KA3  \
)

#endif
