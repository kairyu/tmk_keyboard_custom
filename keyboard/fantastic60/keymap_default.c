/*
Copyright 2015 Kai Ryu <kai1103@gmail.com>

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
#include "rgb.h"
#include "debug.h"


// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space             |Fn0 |Gui |App |Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP_ANSI(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,  \
        LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT, \
        LCTL,LGUI,LALT,          SPC,                     FN0, RGUI,APP, RCTL),
    /* Keymap 1: Fn Layer
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |     |   |Up |Fn4|Fn5|Fn6|Cal|   |Ins|   |Psc|Slk|Pau|     |
     * |-----------------------------------------------------------|
     * |      |Lef|Dow|Rig|Fn7|Fn8|   |   |   |   |Hom|PgU|        |
     * |-----------------------------------------------------------|
     * |        |Fn2|Fn1|Fn3|Fn9|F10|VoD|VoU|Mut|End|PgD|          |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     */
    KEYMAP_ANSI(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,  \
        TRNS,TRNS,UP,  FN4, FN5, FN6, CALC,TRNS,INS, TRNS,PSCR,SLCK,PAUS,TRNS, \
        TRNS,LEFT,DOWN,RGHT,FN7, FN8, TRNS,TRNS,TRNS,TRNS,HOME,PGUP,     TRNS, \
        TRNS,     FN2, FN1, FN3, FN9, FN10,VOLD,VOLU,MUTE,END, PGDN,     TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,TRNS,TRNS),
};

enum function_id {
    AF_RGB_TOGGLE = 0,
    AF_RGB_ON,
    AF_RGB_OFF,
    AF_RGB_DECREASE,
    AF_RGB_INCREASE,
    AF_RGB_STEP,
    AF_RGB_COLOR_DECREASE,
    AF_RGB_COLOR_INCREASE
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
    [1] = ACTION_BACKLIGHT_TOGGLE(),
    [2] = ACTION_BACKLIGHT_DECREASE(),
    [3] = ACTION_BACKLIGHT_INCREASE(),
    [4] = ACTION_FUNCTION(AF_RGB_STEP),
    [5] = ACTION_FUNCTION_OPT(AF_RGB_COLOR_DECREASE, RGB_R),
    [6] = ACTION_FUNCTION_OPT(AF_RGB_COLOR_INCREASE, RGB_R),
    [7] = ACTION_FUNCTION_OPT(AF_RGB_COLOR_DECREASE, RGB_G),
    [8] = ACTION_FUNCTION_OPT(AF_RGB_COLOR_INCREASE, RGB_G),
    [9] = ACTION_FUNCTION_OPT(AF_RGB_COLOR_DECREASE, RGB_B),
    [10] = ACTION_FUNCTION_OPT(AF_RGB_COLOR_INCREASE, RGB_B),
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) {
        switch (id) {
            case AF_RGB_TOGGLE:
                rgb_toggle();
                break;
            case AF_RGB_ON:
                rgb_on();
                break;
            case AF_RGB_OFF:
                rgb_off();
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
            case AF_RGB_COLOR_INCREASE:
                rgb_color_increase(opt);
                break;
            case AF_RGB_COLOR_DECREASE:
                rgb_color_decrease(opt);
                break;
        }
    }
}
