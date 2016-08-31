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
#include "action_util.h"
#include "keymap_common.h"
#include "rgb.h"


// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------.
     * |Fn3|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P| BS|
     * |-----------------------------------------------|
     * |Tab |  A|  S|  D|  F|  G|  H|  J|  K|  L|Enter |
     * |-----------------------------------------------|
     * |Shift |  Z|  X|  C|  V|  B|  N|  M|  .|RShi|Fn0|
     * |-----------------------------------------------|
     * |Ctrl |Gui|Alt  |        Space         |Fn1|Ctrl|
     * `-----------------------------------------------'
     */
    KEYMAP(
        FN3, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   BSPC, \
        TAB, A,   S,   D,   F,   G,   H,   J,   K,   L,        ENT,  \
        LSFT,     Z,   X,   C,   V,   B,   N,   M,   DOT, RSFT,FN0,  \
        LCTL,LGUI,LALT,               SPC,                FN1, RCTL  ),
    /* Keymap 1: Arrow Keys Overlay
     * ,-----------------------------------------------.
     * |   |   |Up |   |   |   |   |   |   |   |   |   |
     * |-----------------------------------------------|
     * |    |Lef|Dow|Rig|   |   |   |   |   |   |      |
     * |-----------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |    |   |
     * |-----------------------------------------------|
     * |     |   |     |                      |   |    |
     * `-----------------------------------------------'
     */
    KEYMAP(
        TRNS,TRNS,UP,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,               TRNS,               TRNS,TRNS  ),
    /* Keymap 2: Fn Layer 1
     * ,-----------------------------------------------.
     * |  1|  2|  3|  4|  5|  6|  7|  8|  8|  9|  -|  =|
     * |-----------------------------------------------|
     * |Caps|   |   |   |   |   |   |   |   |  ;|     '|
     * |-----------------------------------------------|
     * |      |Fn7|Fn8|Fn5|Fn4|Fn6|   |   |  ,|   /|   |
     * |-----------------------------------------------|
     * |     |   |     |          Fn2         |   |    |
     * `-----------------------------------------------'
     */
    KEYMAP(
        1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL,  \
        CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,SCLN,     QUOT, \
        TRNS,     FN7, FN8, FN5, FN4, FN6, TRNS,TRNS,COMM,SLSH,TRNS, \
        TRNS,TRNS,TRNS,               FN2,                TRNS,TRNS  ),
    /* Keymap 3: Fn Layer 2
     * ,-----------------------------------------------.
     * |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|
     * |-----------------------------------------------|
     * |Caps|   |   |   |   |   |   |   |  [|  ]|\     |
     * |-----------------------------------------------|
     * |      |Fn7|Fn8|Fn5|Fn4|Fn6|   |   |  ,|   /|   |
     * |-----------------------------------------------|
     * |     |   |     |          Fn2         |   |    |
     * `-----------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,  \
        CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,LBRC,RBRC,     BSLS, \
        TRNS,     FN7, FN8, FN5, FN4, FN6, TRNS,TRNS,COMM,SLSH,TRNS, \
        TRNS,TRNS,TRNS,               FN2,                TRNS,TRNS  ),
};

#ifndef NO_ACTION_FUNCTION
enum function_id {
    AF_RGB_TOGGLE = 0,
    AF_RGB_DECREASE,
    AF_RGB_INCREASE,
    AF_RGB_STEP,
    AF_TRICKY_ESC
};
#endif

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_LAYER_MOMENTARY(2),
    [1] = ACTION_LAYER_MOMENTARY(3),
    [2] = ACTION_LAYER_TOGGLE(1),
    [3] = ACTION_FUNCTION(AF_TRICKY_ESC),
    [4] = ACTION_BACKLIGHT_TOGGLE(),
    [5] = ACTION_BACKLIGHT_DECREASE(),
    [6] = ACTION_BACKLIGHT_INCREASE(),
    [7] = ACTION_FUNCTION(AF_RGB_TOGGLE),
    [8] = ACTION_FUNCTION(AF_RGB_STEP)
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

#ifndef NO_ACTION_FUNCTION
#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
#ifdef RGB_LED_ENABLE
    if (record->event.pressed) {
        switch (id) {
            case AF_RGB_TOGGLE:
                rgb_toggle();
                break;
            case AF_RGB_DECREASE:
                rgb_decrease();
                break;
            case AF_RGB_INCREASE:
                rgb_increase();
                break;
            case AF_RGB_STEP:
                rgb_step();
                break;
        }
    }
#endif
    static uint8_t tricky_esc_registered;
    switch (id) {
        case AF_TRICKY_ESC:
            if (record->event.pressed) {
                if (get_mods() & MODS_SHIFT_MASK) {
                    tricky_esc_registered = KC_GRV;
                }
                else {
                    tricky_esc_registered = KC_ESC;
                }
                register_code(tricky_esc_registered);
                send_keyboard_report();
            }
            else {
                unregister_code(tricky_esc_registered);
                send_keyboard_report();
            }
            break;
    }
}
#endif
