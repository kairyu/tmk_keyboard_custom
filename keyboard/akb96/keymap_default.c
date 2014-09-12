#include "keymap_common.h"

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
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Fn4|  /|  *|  -|
     * |-----------------------------------------------------------+---+---+---+---|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  7|  8|  9|   |
     * |-----------------------------------------------------------+---+---+---|  +|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |  4|  5|  6|   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |  1|  2|  3|   |
     * |-----------------------------------------------------------+---+---+---|Ent|
     * |Ctrl|Gui |Alt |         Space          |Alt |Gui |Fn0 |Ctrl|  ,|  0|  .|   |
     * `---------------------------------------------------------------------------'
     */
    KEYMAP(
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,PAUS,INS, DEL, PGUP,PGDN, \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL,      BSPC,FN4, PSLS,PAST,PMNS, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,P7,  P8,  P9,  PPLS, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,          ENT, P4,  P5,  P6,        \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,FN0, P1,  P2,  P3,  PENT, \
        LCTL,LGUI,LALT,          SPC,                RALT,RGUI,FN0,           RCTL,PCMM,P0,  PDOT       ),
    /* Keymap 1: Fn Layer
     * ,---------------------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |Num|   |   |   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---|   |
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |   |   |   |   |
     * |-----------------------------------------------------------+---+---+---+---|
     * |        |Fn1|Fn2|Fn3|   |   |   |App|   |   |   |          |   |Up |   |   |
     * |-----------------------------------------------------------+---+---+---|   |
     * |    |    |    |                        |    |    |    |    |Lef|Dow|Rig|   |
     * `---------------------------------------------------------------------------'
     */
    KEYMAP(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,NLCK,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,TRNS,      \
        TRNS,FN1, FN2, FN3, TRNS,TRNS,TRNS,APP, TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,UP,  TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,               TRNS,TRNS,TRNS,          TRNS,LEFT,DOWN,RGHT       ),
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
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,TRNS,      \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,UP,  TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,               TRNS,TRNS,TRNS,          TRNS,LEFT,DOWN,RGHT       ),
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
    [4] = ACTION_LAYER_TOGGLE(2)
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif
