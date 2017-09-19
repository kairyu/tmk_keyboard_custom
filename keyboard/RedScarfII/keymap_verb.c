#include "keymap_common.h"
#include "rgb.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0:
     * ,-------------------------------------------------------------------------.
     * | F1| F2|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | Home|
     * |---+---+-----------------------------------------------------------+-----|
     * | F3| F4|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  End|
     * |---+---+-----------------------------------------------------------+-----|
     * | F5| F6|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  | PgUp|
     * |---+---+-----------------------------------------------------------+-----|
     * | F7| F8|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift|  Up| PgDn|
     * |---+---+-----------------------------------------------------------+-----|
     * | F9|F10|Ctrl|Gui |Alt |         Space          |Alt |Fn0 |Left|Down|Right|
     * `-------------------------------------------------------------------------'
     */
    KEYMAP_VERB(
        F1,  F2,  FN30,1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,HOME, \
        F3,  F4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,END,  \
        F5,  F6,  FN1 ,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT, PGUP, \
        F7,  F8,  LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,UP,  PGDN, \
        F9,  F10, LCTL,LGUI,LALT,          SPC,                RALT,FN0, RGUI,LEFT,DOWN,RIGHT ),

    /*
     * Keymap 1: incomplete
     */
    KEYMAP_VERB(
        TRNS,TRNS,GRV ,F1  ,F2  ,F3  ,F4  ,F5  ,F6  ,F7  ,F8  ,F9  ,F10 ,F11 ,F12 ,DEL ,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,\
        TRNS,TRNS, TRNS,TRNS,TRNS,        TRNS,              TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS ),
};

/*
 * Action function definition
 */
enum function_id {
    AF_RGB_ON = 0,
    AF_RGB_OFF,
    AF_RGB_TOGGLE,
    AF_RGB_INCREASE,
    AF_RGB_DECREASE,
    AF_RGB_FIXED,
    AF_RGB_VARIABLE,
    AF_RGB_STEP,
    AF_TRICKY_ESC
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
    [2] = ACTION_BACKLIGHT_TOGGLE(),
    [3] = ACTION_BACKLIGHT_INCREASE(),
    [4] = ACTION_LAYER_TOGGLE(2),
    [5] = ACTION_FUNCTION(AF_RGB_ON),
    [6] = ACTION_FUNCTION_OPT(AF_RGB_STEP, RGB_FIXED),
    [7] = ACTION_FUNCTION_OPT(AF_RGB_STEP, RGB_VARIABLE),
    [8] = ACTION_FUNCTION(AF_RGB_DECREASE),
    [9] = ACTION_FUNCTION(AF_RGB_INCREASE),
    [10] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_RED),
    [11] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_GREEN),
    [12] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_BLUE),
    [13] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_WHITE),
    [14] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_RED_1),
    [15] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_GREEN_1),
    [16] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_BLUE_1),
    [17] = ACTION_FUNCTION_OPT(AF_RGB_VARIABLE, RGB_VARIABLE_FLASH),
    [18] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_RED_2),
    [19] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_GREEN_2),
    [20] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_BLUE_2),
    [21] = ACTION_FUNCTION_OPT(AF_RGB_VARIABLE, RGB_VARIABLE_STROBE),
    [22] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_RED_3),
    [23] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_GREEN_3),
    [24] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_BLUE_3),
    [25] = ACTION_FUNCTION_OPT(AF_RGB_VARIABLE, RGB_VARIABLE_FADE),
    [26] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_RED_4),
    [27] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_GREEN_4),
    [28] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_BLUE_4),
    [29] = ACTION_FUNCTION_OPT(AF_RGB_VARIABLE, RGB_VARIABLE_SMOOTH),
    [30] = ACTION_FUNCTION(AF_TRICKY_ESC)
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) {
        switch (id) {
            case AF_RGB_ON:
                rgb_on();
                break;
            case AF_RGB_OFF:
                rgb_off();
                break;
            case AF_RGB_TOGGLE:
                rgb_toggle();
                break;
            case AF_RGB_INCREASE:
                rgb_increase();
                break;
            case AF_RGB_DECREASE:
                rgb_decrease();
                break;
            case AF_RGB_FIXED:
                rgb_set(RGB_FIXED, opt);
                break;
            case AF_RGB_VARIABLE:
                rgb_set(RGB_VARIABLE, opt);
                break;
            case AF_RGB_STEP:
                rgb_step(opt);
                break;
        }
    }
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

/*
 * Action macro definition
 */
enum macro_id {
    KEYPAD_00 = 0,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case KEYPAD_00:
            return (record->event.pressed ?
                    MACRO( T(P0), T(P0), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
