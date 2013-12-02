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

#if defined(KEYMAP_PLAIN)
    #include "keymap_plain.h"
#else
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,---------------.
     * |Num|/  |*  |-  |
     * |---+---+---+---|
     * |7  |8  |9  |+  |
     * |---+---+---|   |
     * |4  |5  |6  |   |
     * |---+---+---+---|
     * |1  |2  |3  |Ent|
     * |---+---+---|   |
     * |0  |Up |.  |   |
     * |---+---+---+---|
     * |Lef|Dow|Rig|Fn0|
     * `---------------'
     */
    [0] = KEYMAP(
        NLCK,PSLS,PAST,PMNS, \
        P7,  P8,  P9,  PPLS, \
        P4,  P5,  P6,  NO,   \
        P1,  P2,  P3,  PENT, \
        P0,  UP,  PDOT,NO,   \
        LEFT,DOWN,RGHT,FN0),
    /* Keymap 1: */
    [1] = KEYMAP(
        TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS),
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
static const uint16_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_LAYER_MOMENTARY(1)
};
#endif

#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

#ifdef KEYMAP_EX_ENABLE
const uint8_t* keymaps_pointer(void) {
    return (const uint8_t*)keymaps;
}

const uint16_t* fn_actions_pointer(void) {
    return fn_actions;
}

uint16_t keys_count(void) {
    return KEYMAPS_SIZE * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return FN_ACTIONS_SIZE;
}
#endif

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    if (layer < KEYMAPS_SIZE) {
#ifndef KEYMAP_EX_ENABLE
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
#else
        return eeconfig_read_keymap_key(layer, key.row, key.col);
#endif
    } else {
        // XXX: this may cuaes bootlaoder_jump inconsistent fail.
        //debug("key_to_keycode: base "); debug_dec(layer); debug(" is invalid.\n");
        // fall back to layer 0
#ifndef KEYMAP_EX_ENABLE
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
#else
        return eeconfig_read_keymap_key(0, key.row, key.col);
#endif
    }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
#ifndef KEYMAP_EX_ENABLE
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
#else
        action.code = eeconfig_read_keymap_fn_action(FN_INDEX(keycode));
#endif
    } else {
        action.code = ACTION_NO;
    }
    return action;
}
