#include "keymap_common.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,---------------------------------------------------------------------------------------.
     * |Esc|   | F1| F2| F3| F4| | F5| F6| F7| F8| | F9|F10|F11|F12|Psc|Slk|Pus|               |
     * |---------------------------------------------------------------------------------------|
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Ins|Hom|PgU|Num|  /|  *|  -|
     * |---------------------------------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Del|End|PgD|  7|  8|  9|   |
     * |-----------------------------------------------------------------------------------|  +|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |           |  4|  5|  6|   |
     * |-----------------------------------------------------------|   ,---.   |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |   |Up |   |  1|  2|  3|   |
     * |-----------------------------------------------------------------------------------|Ent|
     * |Ctrl|Gui |Alt |         Space          |Alt |Gui |Fn0 |Ctrl|Lef|Dow|Rig|      0|  .|   |
     * `---------------------------------------------------------------------------------------'
     */
    KEYMAP_ANSI_104(
        ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,   PSCR,SLCK,PAUS,                       \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,  INS, HOME,PGUP,  NLCK,PSLS,PAST,PMNS, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,  DEL, END, PGDN,  P7,  P8,  P9,  PPLS, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                    P4,  P5,  P6,        \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,       UP,         P1,  P2,  P3,  PENT, \
        LCTL,LGUI,LALT,               SPC,                RALT,RGUI,FN0, RCTL,  LEFT,DOWN,RGHT,  P0,       PDOT       ),
    /* Keymap 1: Fn Layer
     * ,---------------------------------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |               |
     * |---------------------------------------------------------------------------------------|
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |   |   |   |   |   |   |
     * |---------------------------------------------------------------------------------------|
     * |     |Fn1|Fn2|Fn3|   |   |   |   |   |   |   |   |   |     |   |   |   |   |   |   |   |
     * |-----------------------------------------------------------------------------------|   |
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |           |   |   |   |   |
     * |-----------------------------------------------------------|   ,---.   |----------------
     * |        |   |   |   |   |   |   |   |   |   |   |          |   |   |   |   |   |   |   |
     * |-----------------------------------------------------------------------------------|   |
     * |    |    |    |                        |    |    |    |    |   |   |   |   |   |   |   |
     * `---------------------------------------------------------------------------------------'
     */
    KEYMAP_ANSI_104(
        TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,                       \
        TRNS,FN1, FN2, FN3, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,  NLCK,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,                   TRNS,TRNS,TRNS,      \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,       TRNS,       TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,               TRNS,               TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,  TRNS,     TRNS       ),
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    /* Poker2 Layout */
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_BACKLIGHT_TOGGLE(),
    [2] = ACTION_BACKLIGHT_DECREASE(),
    [3] = ACTION_BACKLIGHT_INCREASE(),
};

#ifdef KEYMAP_EX_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif
