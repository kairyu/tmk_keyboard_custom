/*
Copyright 2016 Kai Ryu <kai1103@gmail.com>

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
#include "keycode.h"
#include "action.h"
#include "keymap_common.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     *    ,-----------------------------.      ,-----------------------------.
     *    |    `|  1|  2|  3|  4|  5|  -|      |  =|  6|  7|  8|  9|  0|    '|
     *    |-----+---+---+---+---+-------|      |---+---+---+---+---+---+-----|
     *    |Tab  |  Q|  W|  E|  R|  T|   |      |   |  Y|  U|  I|  O|  P|    \|
     *    |-----+---+---+---+---|---| Fn|      | Fn|---+---+---+---+---+-----|
     *    |Caps |  A|  S|  D|  F|  G|---|      |---|  H|  J|  K|  L|  ;|Retur|
     *    |-----+---+---+---+---|---|   |      |   |---+---+---+---+---+-----|
     *    |Shift|  Z|  X|  C|  V|  B| Fn|      | Fn|  N|  M|  ,|  .|  /|Shift|
     *    `-----+---+---+---+---+-------'      `-------+---+---+---+---+-----'
     *      |Ctr|Gui|Alt|Lef|Rig| ,-------.  ,-------. | Up|Dow|  [|  ]|Ctr|
     *      `-------------------' |Esc|Ins|  |Del|Alt| `-------------------'
     *                        ,---+---+---|  |---+---+---.
     *                        |   |   |Hom|  |PgU|   |   |
     *                        |Spc|BS |---|  |---|Tab|Ent|
     *                        |   |   |End|  |PgD|   |   |
     *                        `-----------'  `-----------'
     */
    KEYMAP(
        GRV, 1,   2,   3,   4,   5,   MINS,  EQL, 6,   7,   8,   9,   0,   QUOT, \
        TAB, Q,   W,   E,   R,   T,   FN0,   FN1, Y,   U,   I,   O,   P,   BSLS, \
        CAPS,A,   S,   D,   F,   G,               H,   J,   K,   L,   SCLN,ENT,  \
        LSFT,Z,   X,   C,   V,   B,   FN2,   FN3, N,   M,   COMM,DOT, SLSH,RSFT, \
        LCTL,LGUI,LALT,LEFT,RGHT,                      UP,  DOWN,LBRC,RBRC,RCTL, \
                                 ESC, INS,   DEL, RALT,                          \
                                      HOME,  PGUP,                               \
                            SPC, BSPC,END,   PGDN,TAB, ENT                       ),
    /* Keymap 1: Fn Layer
     *    ,-----------------------------.      ,-----------------------------.
     *    |     |F1 |F2 |F3 |F4 |F5 |   |      |   |F6 |F7 |F8 |F9 |F10|     |
     *    |-----+---+---+---+---+-------|      |---+---+---+---+---+---+-----|
     *    |     |   |   |   |   |   |   |      |   |   |   |   |   |   |     |
     *    |-----+---+---+---+---|---|   |      |   |---+---+---+---+---+-----|
     *    |     |   |   |   |   |   |---|      |---|   |   |   |   |   |     |
     *    |-----+---+---+---+---|---|   |      |   |---+---+---+---+---+-----|
     *    |     |   |   |   |   |   |   |      |   |   |   |   |   |   |     |
     *    `-----+---+---+---+---+-------'      `-------+---+---+---+---+-----'
     *      |   |   |   |   |   | ,-------.  ,-------. |   |   |   |   |   |
     *      `-------------------' |   |   |  |   |   | `-------------------'
     *                        ,---+---+---|  |---+---+---.
     *                        |   |   |   |  |   |   |   |
     *                        |   |   |---|  |---|   |   |
     *                        |   |   |   |  |   |   |   |
     *                        `-----------'  `-----------'
     */
    KEYMAP(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,            TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,                      TRNS,TRNS,TRNS,TRNS,TRNS, \
                                 TRNS,TRNS,  TRNS,TRNS,                          \
                                      TRNS,  TRNS,                               \
                            TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS                      )
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_MOMENTARY(1),
    [2] = ACTION_LAYER_MOMENTARY(1),
    [3] = ACTION_LAYER_MOMENTARY(1)
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif
