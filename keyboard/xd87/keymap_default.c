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
#ifdef RGB_LED_ENABLE
#include "rgb_led.h"
#endif

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
    * ,---------------------------------------------------------------------------.
     * |Esc|N10|F1 | F2| F3| F4| |F5| F6| F7| F8|  | F9|F10|F11|F12|  |Prs|Scl|Pau|
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|  |---+---+---|   
     * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   Bs  |  |Ins|Hom|Pgu| 
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|  |---+---+---|
     * |Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \|  |  |Del|End|Pgd| 
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|  |---+---+---|
     * | Cap |  A|  S|  D|  F|  G||  H|  J|  K|  L|  ;| ' |  Enter |  
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|  |---+---+---|
     * |  Shi  |  Z|  X|  C|  V|  B||  N|  M|  ,|  .|  /|    Shi   |  |Fn8| Up|Fn9|
     * |---+---+---+---+-------+---+---+---+-------+---+---+---+---|  |---+---+---|
     * | Ctr| Gui| Alt|        Space               |Fn0|Alt|App|Ctr|  |Lef|Dow|Rig|
     * `--------------------------------------------------------------------------'
     */


    KEYMAP(
        ESC, FN10,F1, F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10,  F11,  F12, PSCR, SLCK, PAUS, \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,NO, INS, HOME, PGUP,\
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, DEL,END,PGDN,\
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT, NO, ENT,   \
        LSFT,NO, Z,   X,   C,   V,   B,   N,   M,   COMM, DOT, SLSH,      RSFT, NO, FN8, UP, FN9,\
        LCTL,LGUI,LALT,         NO,  SPC,                     FN0, RALT,APP, RCTL,LEFT,DOWN,RGHT),
    /* Keymap 1: Fn Layer
     * ,---------------------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  |   |   |   |
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|  |---+---+---|   
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |  |   |   |   | 
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|  |---+---+---|
     * |    |   | ↑ |   |   |   |   |   |   |   |   |   |   |      |  |   |   |   | 
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|  |---+---+---|
     * |     |  ←|  ↓|  →|   |   ||   |   |   |   |   |   |        |  
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|  |---+---+---|
     * |      |   |   |FN2|FN1|FN3|VLD|VLU|MUT|   |   |            |  |   |Fn5|   |
     * |---+---+---+---+-------+---+---+---+-------+---+---+---+---|  |---+---+---|
     * |    |    |    |                            |   |N10|   |   |  |Fn6|Fn4|Fn7|
     * `--------------------------------------------------------------------------'
     */
    KEYMAP(
    	TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,  UP,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS, FN2, FN1, FN3,VOLD,VOLU,MUTE,TRNS,TRNS,TRNS,TRNS,TRNS, FN5,TRNS, \
        TRNS,TRNS,TRNS,     TRNS,          TRNS,     TRNS,FN10,TRNS,TRNS,FN6,  FN4, FN7),
    };

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

enum macro_id {
    AM_KEYPAD_00 = 0,
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
    [4] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_DECREASE), 
    [5] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_INCREASE), 
    [6] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_DECREASE_BRIGHTNESS),
    [7] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_INCREASE_BRIGHTNESS),
    [8] = ACTION_BACKLIGHT_STEP(),
    [9] = ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_STEP),
    [10]= ACTION_FUNCTION_OPT(AF_RGB_LED, AF_RGB_LED_TOGGLE),
    
  };

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case AM_KEYPAD_00:
            return (record->event.pressed ?
                    MACRO( T(P0), T(P0), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
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
