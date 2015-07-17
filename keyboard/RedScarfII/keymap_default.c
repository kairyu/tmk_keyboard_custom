#include "keymap_common.h"
#include "rgb.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: ModelF/77 - OEM 1.25-1.25-1.25-6.25-1.25-1.25-1.25-1.25
     * ,-----------------------------------------------------------------------------------.
     * | F1| F6|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Num|  /|  *|  -|
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F2| F7|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  7|  8|  9|   |
     * |---+---+-----------------------------------------------------------+---+---+---|  +|
     * | F3| F8|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |  4|  5|  6|   |
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F4| F9|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|  1|  2|  3|   |
     * |---+---+-----------------------------------------------------------+---+---+---|Ent|
     * | F5|F10|Ctrl|Gui |Alt |         Space          |Alt |Fn0 |Gui |Ctrl|  0|  0|  .|   |
     * `-----------------------------------------------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,NLCK,PSLS,PAST,PMNS, \
        F3,  F4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,P7,  P8,  P9,  PPLS, \
        F5,  F6,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV, ENT, P4,  P5,  P6,  PPLS, \
        F7,  F8,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN0, P1,  P2,  P3,  PENT, \
        F9,  F10, LCTL,LGUI,LALT,          SPC,                RALT,FN0, RGUI,RGUI,RCTL,P0,  P0,  PDOT,PENT  ),
    /* Keymap 1: ModelF/77 - Winkeyless 1.5-1-1.5-7-1.5-1-1.5
     * ,-----------------------------------------------------------------------------------.
     * | F1| F6|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Num|  /|  *|  -|
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F2| F7|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  7|  8|  9|   |
     * |---+---+-----------------------------------------------------------+---+---+---|  +|
     * | F3| F8|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |  4|  5|  6|   |
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F4| F9|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|  1|  2|  3|   |
     * |---+---+-----------------------------------------------------------+---+---+---|Ent|
     * | F5|F10|Ctrl |Gui|Alt  |           Space           |Alt  |Fn0|Ctrl |  0|  0|  .|   |
     * `-----------------------------------------------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,NLCK,PSLS,PAST,PMNS, \
        F3,  F4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,P7,  P8,  P9,  PPLS, \
        F5,  F6,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV, ENT, P4,  P5,  P6,  PPLS, \
        F7,  F8,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN0, P1,  P2,  P3,  PENT, \
        F9,  F10, LCTL,LGUI,LALT,          SPC,                RALT,RALT,RGUI,FN0, RCTL,P0,  P0,  PDOT,PENT  ),
    /* Keymap 2: ModelF/77 - OEM + Arrow Keys 1.25-1.25-1.25-6.25-1-1-1-1-1
     * ,-----------------------------------------------------------------------------------.
     * | F1| F6|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Num|  /|  *|  -|
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F2| F7|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  7|  8|  9|   |
     * |---+---+-----------------------------------------------------------+---+---+---|  +|
     * | F3| F8|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |  4|  5|  6|   |
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F4| F9|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|  1|  2|  3|   |
     * |---+---+-----------------------------------------------------------+---+---+---|Ent|
     * | F5|F10|Ctrl|Gui |Alt |         Space          |Alt|Fn0|Ctr|Lef|Dow|Rig|  0|  .|   |
     * `-----------------------------------------------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,NLCK,PSLS,PAST,PMNS, \
        F3,  F4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,P7,  P8,  P9,  PPLS, \
        F5,  F6,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV, ENT, P4,  P5,  P6,  PPLS, \
        F7,  F8,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,UP,  P1,  P2,  P3,  PENT, \
        F9,  F10, LCTL,LGUI,LALT,          SPC,                RALT,FN0, RCTL,LEFT,DOWN,RGHT,P0,  PDOT,PENT  ),
    /* Keymap 3: ModelF/77 - 18xx 1.5-1.5-7-1.5-1.5-1-1
     * ,-----------------------------------------------------------------------------------.
     * | F1| F6|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Num|  /|  *|  -|
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F2| F7|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  7|  8|  9|   |
     * |---+---+-----------------------------------------------------------+---+---+---|  +|
     * | F3| F8|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |  4|  5|  6|   |
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F4| F9|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|  1|  2|  3|   |
     * |---+---+-----------------------------------------------------------+---+---+---|Ent|
     * | F5|F10|Ctrl |Alt  |          Space            |Alt  |Ctrl |Lef|Dow|Rig|  0|  .|   |
     * `-----------------------------------------------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,NLCK,PSLS,PAST,FN0,  \
        F3,  F4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,P7,  P8,  P9,  PMNS, \
        F5,  F6,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV, ENT, P4,  P5,  P6,  PPLS, \
        F7,  F8,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,UP,  P1,  P2,  P3,  PENT, \
        F9,  F10, LCTL,LGUI,LALT,          SPC,                RALT,FN0, RCTL,LEFT,DOWN,RGHT,P0,  PDOT,PENT  ),
    /* Keymap 4: Mini/68 - OEM 1.25-1.25-1.25-6.25-1-1-1
     * ,-----------------------------------------------------------------------.
     * | F1| F6|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Hom|
     * |---+---+-----------------------------------------------------------+---|
     * | F2| F7|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|PgU|
     * |---+---+-----------------------------------------------------------+---|
     * | F3| F8|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |PgD|
     * |---+---+-----------------------------------------------------------+---|
     * | F4| F9|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|End|
     * |---+---+-----------------------------------------------------------+---|
     * | F5|F10|Ctrl|Gui |Alt |       Space            |Alt|Fn0|Ctr|Lef|Dow|Rig|
     * `-----------------------------------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,HOME,PSLS,PAST,FN0,  \
        F3,  F4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,PGUP,P8,  P9,  PMNS, \
        F5,  F6,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV, ENT, PGDN,P5,  P6,  PPLS, \
        F7,  F8,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,UP,  END, P2,  P3,  PENT, \
        F9,  F10, LCTL,LGUI,LALT,          SPC,                RALT,FN0, RCTL,LEFT,DOWN,RGHT,P0,  PDOT,PENT  ),
    /* Keymap 5: Mini/68 - 18xx 1.5-1.5-7-1.5-1.5
     * ,-----------------------------------------------------------------------.
     * | F1| F6|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |  `|
     * |---+---+-----------------------------------------------------------+---|
     * | F2| F7|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|PgU|
     * |---+---+-----------------------------------------------------------+---|
     * | F3| F8|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |PgD|
     * |---+---+-----------------------------------------------------------+---|
     * | F4| F9|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|Fn0|
     * |---+---+-----------------------------------------------------------+---|
     * | F5|F10|Ctrl |Alt  |          Space            |Alt  |Ctrl |Lef|Dow|Rig|
     * `-----------------------------------------------------------------------'
     */
    KEYMAP(
        F1,  F2,  ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,GRV, PSLS,PAST,FN0,  \
        F3,  F4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,PGUP,P8,  P9,  PMNS, \
        F5,  F6,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV, ENT, PGDN,P5,  P6,  PPLS, \
        F7,  F8,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,UP,  FN0, P2,  P3,  PENT, \
        F9,  F10, LCTL,LGUI,LALT,          SPC,                RALT,FN0, RCTL,LEFT,DOWN,RGHT,P0,  PDOT,PENT  ),
    /* Keymap 6: Fn Layer
     * ,-----------------------------------------------------------------------------------.
     * |n17|n24|  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |n10|n11|n12|n13|
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * |n10|n22|     |   |Up |Fn5|Fn6|Fn7|Cal|   |Ins|   |Psc|Slk|Pau|     |n14|n15|n16|   |
     * |---+---+-----------------------------------------------------------|---+---+---|n17|
     * |n14|n16|      |Lef|Dow|Rig|Fn8|Fn9|   |   |   |   |Hom|PgU|        |n18|n19|n20|   |
     * |---+---+-----------------------------------------------------------|---+---+---+---|
     * |n25|n27|        |   |App|Fn1|Fn2|Fn3|VoD|VoU|Mut|End|PgD|      |   |n22|n23|n24|   |
     * |---+---+-----------------------------------------------------------+---+---+---|n25|
     * |n15|n13|    |    |    |                        |    |    |    |    |n26|n27|n28|   |
     * `-----------------------------------------------------------------------------------'
     */
    KEYMAP(
        FN10,FN14,GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL, FN10,FN11,FN12,FN13, \
        FN26,FN15,TRNS,TRNS,UP,  FN5, FN6, FN7, CALC,TRNS,INS, TRNS,PSCR,SLCK,PAUS,TRNS,FN14,FN15,FN16,FN17, \
        FN23,FN16,TRNS,LEFT,DOWN,RGHT,FN8, FN9, TRNS,TRNS,TRNS,TRNS,HOME,PGUP,TRNS,TRNS,FN18,FN19,FN20,FN21, \
        FN28,FN13,TRNS,TRNS,TRNS,APP, FN1, FN2, FN3, VOLD,VOLU,MUTE,END, PGDN,TRNS,TRNS,FN22,FN23,FN24,FN25, \
        FN17,FN25,TRNS,TRNS,TRNS,          FN4,                TRNS,TRNS,TRNS,TRNS,TRNS,FN26,FN27,FN28,FN29  ),
    /* Keymap 2: Arrow key Overlayer
     * ,-----------------------------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |   |   |   |
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |   |   |   |
     * |---+---+-----------------------------------------------------------+---+---+---|   |
     * |   |   |      |   |   |   |   |   |   |   |   |   |   |   |        |   |   |   |   |
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * |   |   |        |   |   |   |   |   |   |   |   |   |   |          |   |Up |   |   |
     * |---+---+-----------------------------------------------------------+---+---+---|   |
     * |   |   |    |    |    |                        |    |    |    |    |Lef|Dow|Rig|   |
     * `-----------------------------------------------------------------------------------'
     */
    /*
    KEYMAP(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,UP,  TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,               TRNS,TRNS,TRNS,TRNS,TRNS,LEFT,DOWN,RGHT,TRNS  ),
        */
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
    [0] = ACTION_LAYER_MOMENTARY(6),
    [1] = ACTION_BACKLIGHT_DECREASE(),
    [2] = ACTION_BACKLIGHT_TOGGLE(),
    [3] = ACTION_BACKLIGHT_INCREASE(),
    [5] = ACTION_FUNCTION(AF_RGB_TOGGLE),
    /*[4] = ACTION_LAYER_TOGGLE(2),*/
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
