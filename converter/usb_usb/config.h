/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H


#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x005B
#define DEVICE_VER      0x0814
#define MANUFACTURER    t.m.k.
#define PRODUCT         USB to USB keyboard converter


#define DESCRIPTION     Product from t.m.k. keyboard firmware project


/* matrix size */
#define MATRIX_ROWS 16
#define MATRIX_COLS 16

/* keymap in eeprom */
#define FN_ACTIONS_COUNT 32
#define KEYMAPS_COUNT 3

/* number of leds */
#define LED_COUNT 3
#define EECONFIG_LEDMAP_IN_EEPROM 8

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) 

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
