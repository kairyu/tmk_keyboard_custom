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

#ifndef CONFIG_H
#define CONFIG_H


/* USB Device descriptor parameter */
#define VENDOR_ID       0xCDCD
#define PRODUCT_ID      0x8787
#define DEVICE_VER      0x0001
#define MANUFACTURER    xiudi
#define PRODUCT         XD87
#define DESCRIPTION     t.m.k. keyboard firmware for XD87

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* keymap in eeprom */
#define FN_ACTIONS_COUNT 32
#define KEYMAPS_COUNT 8

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* number of backlight levels */
#ifdef BREATHING_LED_ENABLE
#define BACKLIGHT_LEVELS 8
#else
#define BACKLIGHT_LEVELS 3
#endif
#define BACKLIGHT_CUSTOM
#ifdef RGB_LED_ENABLE
#define CUSTOM_LED_ENABLE
#endif

#define BACKLIGHT_CONFIG_DEFAULT_ENABLE true
#define BACKLIGHT_CONFIG_DEFAULT_LEVEL 2
#define RGB_LED_CONFIG_DEFAULT_ENABLE true
#define RGB_LED_CONFIG_DEFAULT_LEVEL 9

/* LED mapping */
#ifdef LEDMAP_ENABLE
#define LED_COUNT  3
#define LEDMAP_V2
#define LED1_PORT   E
#define LED1_BIT    2
#define LED2_PORT   D
#define LED2_BIT    0
#define LED3_PORT   B
#define LED3_BIT    7
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

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
