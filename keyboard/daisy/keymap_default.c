/*
Copyright 2017 Kai Ryu <kai1103@gmail.com>

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
#include "rgb_led.h"


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
     * |Shift |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|RShi|
     * |-----------------------------------------------|
     * |Ctrl|Gui|Alt |   Fn1   |   Fn2   |RAlt|Fn0|RCtr|
     * `-----------------------------------------------'
     */
    KEYMAP(
        FN3, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   BSPC, \
        TAB, A,   S,   D,   F,   G,   H,   J,   K,   L,        ENT,  \
        LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, RSFT, \
        LCTL,LGUI,LALT,          FN1, FN2,           RALT,FN0, RCTL  ),
    /* Keymap 1: Arrow Keys Overlay
     * ,-----------------------------------------------.
     * |   |   |Up |   |   |   |   |   |   |   |   |   |
     * |-----------------------------------------------|
     * |    |Lef|Dow|Rig|   |   |   |   |   |   |      |
     * |-----------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |    |
     * |-----------------------------------------------|
     * |    |   |    |         |         |    |   |    |
     * `-----------------------------------------------'
     */
    KEYMAP(
        TRNS,TRNS,UP,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,TRNS,          TRNS,TRNS,TRNS  ),
    /* Keymap 2: Fn Layer 1
     * ,-----------------------------------------------.
     * |  1|  2|  3|  4|  5|  6|  7|  8|  8|  9|  -|  =|
     * |-----------------------------------------------|
     * |Caps|Fn9|F10|   |   |   |   |   |   |  ;|     '|
     * |-----------------------------------------------|
     * |      |Fn7|Fn8|Fn5|Fn4|Fn6|   |   |   |  /|    |
     * |-----------------------------------------------|
     * |    |   |    |         |  Space  |    |   |    |
     * `-----------------------------------------------'
     */
    KEYMAP(
        1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL,  \
        CAPS,FN9, FN10,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,SCLN,     QUOT, \
        TRNS,     FN7, FN8, FN5, FN4, FN6, TRNS,TRNS,TRNS,SLSH,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,SPC,           TRNS,TRNS,TRNS  ),
    /* Keymap 3: Fn Layer 2
     * ,-----------------------------------------------.
     * |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|
     * |-----------------------------------------------|
     * |Caps|Fn9|F10|   |   |   |   |   |  [|  ]|\     |
     * |-----------------------------------------------|
     * |      |Fn7|Fn8|Fn5|Fn4|Fn6|   |   |   |  /|    |
     * |-----------------------------------------------|
     * |    |   |    |  Space  |         |    |   |    |
     * `-----------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,  \
        CAPS,FN9, FN10,TRNS,TRNS,TRNS,TRNS,TRNS,LBRC,RBRC,     BSLS, \
        TRNS,     FN7, FN8, FN5, FN4, FN6, TRNS,TRNS,TRNS,SLSH,TRNS, \
        TRNS,TRNS,TRNS,          SPC, TRNS,          TRNS,TRNS,TRNS  ),
};

#ifndef NO_ACTION_FUNCTION
enum function_id {
    AF_TRICKY_ESC = 0,
    AF_RGB_LED
};

enum rgb_led_id {
    AF_RGB_LED_TOGGLE = 0,
    AF_RGB_LED_DECREASE,
    AF_RGB_LED_INCREASE,
    AF_RGB_LED_STEP,
    AF_RGB_LED_DECREASE_BRIGHTNESS,
    AF_RGB_LED_INCREASE_BRIGHTNESS
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
    [0] = ACTION_LAYER_TAP_TOGGLE(1),
    [1] = ACTION_LAYER_TAP_KEY(2, KC_SPC),
    [2] = ACTION_LAYER_TAP_KEY(3, KC_SPC),
    [3] = ACTION_FUNCTION_OPT(AF_TRICKY_ESC, 0),
    [4] = ACTION_BACKLIGHT_TOGGLE(),
    [5] = ACTION_BACKLIGHT_DECREASE(),
    [6] = ACTION_BACKLIGHT_INCREASE(),
    [7] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_DECREASE),
    [8] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_INCREASE),
    [9] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_DECREASE_BRIGHTNESS),
    [10] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_INCREASE_BRIGHTNESS)
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
    static uint8_t tricky_esc_registered;
    switch (id) {
        case AF_TRICKY_ESC:
            if (record->event.pressed) {
                uint8_t mods = get_mods();
                if (opt & (1<<0)) {
                    mods -= MOD_BIT(KC_RSHIFT);
                }
                if (opt & (1<<1)) {
                    mods -= MOD_BIT(KC_LSHIFT);
                }
                if (mods & MODS_SHIFT_MASK) {
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
#ifdef RGB_LED_ENABLE
#define RGB_LED_BRIGHTNESS_STEP ((RGB_LED_BRIGHTNESS_MAX - RGB_LED_BRIGHTNESS_MIN) / 8)
    if (record->event.pressed) {
        switch (id) {
            case AF_RGB_LED:
                switch (opt) {
                    case AF_RGB_LED_TOGGLE:
                        rgb_led_toggle();
                        break;
                    case AF_RGB_LED_DECREASE:
                        rgb_led_decrease();
                        break;
                    case AF_RGB_LED_INCREASE:
                        rgb_led_increase();
                        break;
                    case AF_RGB_LED_STEP:
                        rgb_led_step();
                        break;
                    case AF_RGB_LED_DECREASE_BRIGHTNESS:
                        rgb_led_decrease_brightness(RGB_LED_BRIGHTNESS_STEP, true);
                        break;
                    case AF_RGB_LED_INCREASE_BRIGHTNESS:
                        rgb_led_increase_brightness(RGB_LED_BRIGHTNESS_STEP, true);
                        break;
                }
                break;
        }
    }
#endif
}
#endif
