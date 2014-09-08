#include "keymap_common.h"

// Poker2
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space             |Alt |Fn0 |Gui |Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NO,  ENT,  \
        LSFT,NO,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,FN0, RSFT, \
        LCTL,LGUI,LALT,          SPC,                     RALT,FN0, RGUI,RCTL),
    /* Keymap 1: Fn Layer
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |     |   |Up |   |   |   |Cal|   |Ins|   |Psc|Slk|Pau|     |
     * |-----------------------------------------------------------|
     * |      |Lef|Dow|Rig|   |   |   |   |   |   |Hom|PgU|        |
     * |-----------------------------------------------------------|
     * |        |   |App|Fn1|Fn2|Fn3|VoD|VoU|Mut|End|PgD|      |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     */
    KEYMAP(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,  \
        TRNS,TRNS,UP,  TRNS,TRNS,TRNS,CALC,TRNS,INS, TRNS,PSCR,SLCK,PAUS,TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HOME,PGUP,NO,  TRNS, \
        TRNS,NO,  TRNS,APP, FN1, FN2, FN3, VOLD,VOLU,MUTE,END, PGDN,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,TRNS,TRNS),
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
    [1] = ACTION_BACKLIGHT_DECREASE(),
    [2] = ACTION_BACKLIGHT_TOGGLE(),
    [3] = ACTION_BACKLIGHT_INCREASE()
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif
