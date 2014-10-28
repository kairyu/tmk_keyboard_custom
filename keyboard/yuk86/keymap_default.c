#include "keymap_common.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,-------------------------------------------------------------------.
     * |Esc|   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Psc|Slk|Pau|
     * |-------------------------------------------------------------------|
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Ins|Hom|
     * |-------------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Del|End|
     * |-----------------------------------------------------------|   |---|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |   |PgU|
     * |-------------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |Up |PgD|
     * |-------------------------------------------------------------------|
     * |Ctrl|Gui |Alt |          Space          |Alt |Fn0 |Ctrl|Lef|Dow|Rig|
     * `-------------------------------------------------------------------'
     */
    KEYMAP(
        ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,PAUS, \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL,      BSPC,INS, HOME, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,DEL, END,  \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,          ENT, FN0, PGUP, \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,               RSFT,UP,  PGDN, \
        LCTL,LGUI,LALT,          SPC,                          RALT,FN0, RCTL,LEFT,DOWN,RGHT),
    /* Keymap 1: Fn Layer
     * ,-------------------------------------------------------------------.
     * |Fn1|   |MyC|Cal|Mai|WHo|Sto|Pre|Pla|Nex|Sel|VoD|VoU|Mut|   |   |   |
     * |-------------------------------------------------------------------|
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |   |
     * |-------------------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |   |
     * |-----------------------------------------------------------|   |---|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |   |   |
     * |-------------------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |          |   |   |
     * |-------------------------------------------------------------------|
     * |    |    |    |                         |    |    |    |   |   |   |
     * `-------------------------------------------------------------------'
     */
    KEYMAP(
        FN1,      MYCM,CALC,MAIL,WHOM,MSTP,MPRV,MPLY,MNXT,MSEL,VOLD,VOLU,MUTE,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,               TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                         TRNS,TRNS,TRNS,TRNS,TRNS,TRNS),
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
    [1] = ACTION_BACKLIGHT_STEP(),
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_ROWS * MATRIX_COLS;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif
