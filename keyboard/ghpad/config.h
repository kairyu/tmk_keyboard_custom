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


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1010
#define DEVICE_VER      0x0002
#define MANUFACTURER    geekhack
#define PRODUCT         GHPad
#define DESCRIPTION     t.m.k. keyboard firmware for GHPad

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 4

/* keymap in eeprom */
#define FN_ACTIONS_COUNT 32
#define KEYMAPS_COUNT 32

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* number of backlight levels */
#define BACKLIGHT_LEVELS 8
#define BACKLIGHT_CUSTOM

/* number of leds */
#define LED_COUNT 5

/* LED mapping */
#ifdef LEDMAP_ENABLE
#define LEDMAP_V2
#define LED1_PORT   B
#define LED1_BIT    2
#define LED2_PORT   F
#define LED2_BIT    7
#define LED3_PORT   F
#define LED3_BIT    6
#define LED4_PORT   F
#define LED4_BIT    5
#define LED5_PORT   B
#define LED5_BIT    5
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#ifndef __ASSEMBLER__
#include "matrix.h"
#define IS_COMMAND() ( \
    matrix_is_on(0, 0) && matrix_is_on(0, MATRIX_COLS - 1) \
)
#endif

/* boot magic key */
#define BOOTMAGIC_KEY_SALT KC_FN0

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
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
