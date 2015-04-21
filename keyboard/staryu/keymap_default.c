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

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0
     * ,-----------.
     * |   |Up |Fn0|
     * |---+---+---|
     * |Lef|Dow|Rig|
     * `-----------'
     */
    KEYMAP( UP,  FN0, LEFT,DOWN,RGHT ),
    /* Keymap 1
     * ,-----------.
     * |   |PgU|Fn1|
     * |---+---+---|
     * |Hom|PgD|End|
     * `-----------'
     */
    KEYMAP( PGUP,FN1, HOME,PGDN,END  ),
    /* Keymap 2
     * ,-----------.
     * |   |Sel|Fn2|
     * |---+---+---|
     * |Pre|Pla|Nex|
     * `-----------'
     */
    KEYMAP( MSEL,FN2, MPRV,MPLY,MNXT ),
    /* Keymap 3
     * ,-----------.
     * |   |MsU|Fn3|
     * |---+---+---|
     * |MsL|MsD|MsR|
     * `-----------'
     */
    KEYMAP( MS_U,FN3, MS_L,MS_D,MS_R ),
    /* Keymap 4
     * ,-----------.
     * |   |Fn8|Fn4|
     * |---+---+---|
     * |Fn6|Fn5|Fn7|
     * `-----------'
     */
    KEYMAP( FN7, FN3, FN5, FN4, FN6  ),
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
    [0] = ACTION_DEFAULT_LAYER_SET(1),
    [1] = ACTION_DEFAULT_LAYER_SET(2),
    [2] = ACTION_DEFAULT_LAYER_SET(3),
    [3] = ACTION_DEFAULT_LAYER_SET(4),
    [4] = ACTION_DEFAULT_LAYER_SET(0),
    [5] = ACTION_BACKLIGHT_TOGGLE(),
    [6] = ACTION_BACKLIGHT_DECREASE(),
    [7] = ACTION_BACKLIGHT_INCREASE(),
    [8] = ACTION_BACKLIGHT_STEP()
#endif
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif
