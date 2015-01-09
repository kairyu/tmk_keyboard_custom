#include "keymap_common.h"
#include "rgb.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,---------------------------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Psc|Pau|Ins|Del|PgU|PgD|
     * |-----------------------------------------------------------+---+---+---+---|
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Num|  /|  *|  -|
     * |-----------------------------------------------------------+---+---+---+---|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  7|  8|  9|   |
     * |-----------------------------------------------------------+---+---+---|  +|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |  4|  5|  6|   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|  1|  2|  3|   |
     * |-----------------------------------------------------------+---+---+---|Ent|
     * |Ctrl|Gui |Alt |         Space          |Alt |Fn0 |Gui |Ctrl|  0|  0|  .|   |
     * `---------------------------------------------------------------------------'
     */
    KEYMAP(
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,PAUS,INS, DEL, PGUP,PGDN, \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL,      BSPC,NLCK,PSLS,PAST,PMNS, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,P7,  P8,  P9,  PPLS, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV,      ENT, P4,  P5,  P6,  PPLS, \
        LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,FN0, P1,  P2,  P3,  PENT, \
        LCTL,LGUI,LALT,               SPC,                RALT,FN0, RGUI,     RCTL,P0,  P0,  PDOT,PENT  ),
    /* Keymap 1: Fn Layer
     * ,---------------------------------------------------------------------------.
     * |Fn5|Fn6|Fn7|Fn8|Fn9|   |   |   |   |   |   |   |   |   |   |   |   |Hom|End|
     * |-----------------------------------------------------------+---+---+---+---|
     * |F10|F11|F12|F13|F14|F15|F16|F17|F18|   |   |   |   |       |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |   |   |   |
     * |-----------------------------------------------------------|---+---+---|   |
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |   |   |   |   |
     * |-----------------------------------------------------------|---+---+---+---|
     * |        |   |   |Fn2|Fn1|Fn3|VoD|VoU|Mut|   |   |      |   |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---|   |
     * |    |    |    |           Fn4          |    |    |    |    |   |   |   |   |
     * `---------------------------------------------------------------------------'
     */
    KEYMAP(
        FN5 ,FN6 ,FN7 ,FN8 ,FN9 ,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HOME,END,  \
        FN10,FN11,FN12,FN13,FN14,FN15,FN16,FN17,FN18,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,FN2 ,FN1, FN3, VOLD,VOLU,MUTE,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,               FN4,                TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS  ),
    /* Keymap 2: Arrow key Overlayer
     * ,---------------------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---|   |
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |        |   |   |   |   |   |   |   |   |   |   |          |   |Up |   |   |
     * |-----------------------------------------------------------+---+---+---|   |
     * |    |    |    |                        |    |    |    |    |Lef|Dow|Rig|   |
     * `---------------------------------------------------------------------------'
     */
    KEYMAP(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,UP,  TRNS,TRNS, \
        TRNS,TRNS,TRNS,               TRNS,               TRNS,TRNS,TRNS,     TRNS,LEFT,DOWN,RGHT,TRNS  ),
};

enum function_id {
    AF_RGB_ON = 0,
    AF_RGB_OFF,
    AF_RGB_TOGGLE,
    AF_RGB_INCREASE,
    AF_RGB_DECREASE,
    AF_RGB_FIXED,
    AF_RGB_VARIABLE,
    AF_RGB_STEP
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
    [4] = ACTION_LAYER_TOGGLE(2),
    [5] = ACTION_FUNCTION(AF_RGB_TOGGLE),
    [6] = ACTION_FUNCTION_OPT(AF_RGB_STEP, RGB_FIXED),
    [7] = ACTION_FUNCTION_OPT(AF_RGB_STEP, RGB_VARIABLE),
    [8] = ACTION_FUNCTION(AF_RGB_DECREASE),
    [9] = ACTION_FUNCTION(AF_RGB_INCREASE),
    [10] = ACTION_FUNCTION_OPT(AF_RGB_VARIABLE, RGB_VARIABLE_FADE),
    [11] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_RED),
    [12] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_RED_1),
    [13] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_RED_4),
    [14] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_GREEN_1),
    [15] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_GREEN_3),
    [16] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_BLUE_1),
    [17] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_BLUE_4),
    [18] = ACTION_FUNCTION_OPT(AF_RGB_FIXED, RGB_FIXED_WHITE),
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
}

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
