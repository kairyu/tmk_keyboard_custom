#include "keymap_common.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------------------.
     * |Esc|   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Num|Psc|Slk|Pau|
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+-------+---+---+---|
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Ins|Hom|PgU|
     * |-----------------------------------------------------------+---+---+---|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Del|End|PgD|
     * |-----------------------------------------------------------+-----------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |           |
     * |-----------------------------------------------------------|   ,---.   |
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |   |Up |   |
     * |-----------------------------------------------------------+---+---+---|
     * |Ctrl|Gui |Alt |      Space             |Alt |Gui |Fn0 |Ctrl|Lef|Dow|Rig|
     * `-----------------------------------------------------------------------'
     */
    KEYMAP_ANSI(
        ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, FN1,  PSCR,SLCK,PAUS, \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL,      BSPC, INS, HOME,PGUP, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS, DEL, END, PGDN, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,          ENT,                  \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,               RSFT,      UP,        \
        LCTL,LGUI,LALT,          SPC,                          RALT,RGUI,FN0, RCTL, LEFT,DOWN,RGHT),
    /* Keymap 1: Keypad Layer
     * ,-----------------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+-------+---+---+---|
     * |   |   |   |   |   |   |   |  7|  8|  9|   |  -|   |       |   |   |   |
     * |-----------------------------------------------------------+---+---+---|
     * |     |   |   |   |   |   |   |  4|  5|  6|   |Ent|   |     |   |   |   |
     * |-----------------------------------------------------------+-----------|
     * |      |   |   |   |   |   |   |  1|  2|  3|  +|  *|        |           |
     * |-----------------------------------------------------------|   ,---.   |
     * |        |   |   |   |   |   |   |  0|  ,|  .|  /|          |   |   |   |
     * |-----------------------------------------------------------+---+---+---|
     * |    |    |    |                        |    |    |    |    |   |   |   |
     * `-----------------------------------------------------------------------'
     */
    KEYMAP_ANSI(
        TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN2, FN3, FN4,  \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,P7,  P8,  P9,  TRNS,PMNS,TRNS,     TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,P4,  P5,  P6,  TRNS,PENT,TRNS,     TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,P1,  P2,  P3,  PPLS,PAST,          TRNS,                \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,P0,  PCMM,PDOT,PSLS,               TRNS,     TRNS,      \
        TRNS,TRNS,TRNS,          TRNS,                         TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS),
    /* Keymap 2: Fn Layer
     * ,-----------------------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |Fn2|Fn3|Fn4|
     * |---+---+---+---+---+---+---+---+---+---+---+---+---+-------+---+---+---|
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |   |   |
     * |-----------------------------------------------------------+---+---+---|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |   |   |
     * |-----------------------------------------------------------+-----------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |           |
     * |-----------------------------------------------------------|   ,---.   |
     * |        |   |   |   |   |   |   |   |   |   |   |          |   |   |   |
     * |-----------------------------------------------------------+---+---+---|
     * |    |    |    |                        |    |    |    |    |   |   |   |
     * `-----------------------------------------------------------------------'
     */
    KEYMAP_ANSI(
        TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN2, FN3, FN4,  \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,                \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,               TRNS,     TRNS,      \
        TRNS,TRNS,TRNS,          TRNS,                         TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS)
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    /* Default Layout */
    [0] = ACTION_LAYER_MOMENTARY(2),
    [1] = ACTION_LAYER_TOGGLE(1),
    [2] = ACTION_BACKLIGHT_DECREASE(),
    [3] = ACTION_BACKLIGHT_TOGGLE(),
    [4] = ACTION_BACKLIGHT_INCREASE()
};

#ifdef KEYMAP_EX_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif
