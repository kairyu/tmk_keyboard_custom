#include "keymap_common.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------------------------------.
     * | F1| F6|Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Num|  /|  *|  -|
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F2| F7|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  7|  8|  9|   |
     * |---+---+-----------------------------------------------------------+---+---+---|  +|
     * | F3| F8|Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |  4|  5|  6|   |
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * | F4| F9|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|  1|  2|  3|   |
     * |---+---+-----------------------------------------------------------+---+---+---|Ent|
     * | F5|F10|Ctrl|Gui |Alt |         Space          |Alt |Gui |Fn0 |Ctrl|  0|  0|  .|   |
     * `-----------------------------------------------------------------------------------'
     */
    KEYMAP(
        F1,  F6,  ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,NLCK,PSLS,PAST,PMNS, \
        F2,  F7,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,P7,  P8,  P9,  PPLS, \
        F3,  F8,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV, ENT, P4,  P5,  P6,  PPLS, \
        F4,  F9,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN0, P1,  P2,  P3,  PENT, \
        F5,  F10, LCTL,LGUI,LALT,               SPC,                RALT,FN0, RGUI,RCTL,P0,  P0,  PDOT,PENT  ),
    /* Keymap 1: Fn Layer
     * ,-----------------------------------------------------------------------------------.
     * |   |   |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |   |   |   |   |
     * |---+---+-----------------------------------------------------------+---+---+---+---|
     * |   |   |     |   |Up |   |   |   |Cal|   |Ins|   |Psc|Slk|Pau|     |   |   |   |   |
     * |---+---+-----------------------------------------------------------|---+---+---|   |
     * |   |   |      |Lef|Dow|Rig|   |   |   |   |   |   |Hom|PgU|        |   |   |   |   |
     * |---+---+-----------------------------------------------------------|---+---+---+---|
     * |   |   |        |   |App|Fn1|Fn2|Fn3|VoD|VoU|Mut|End|PgD|      |   |   |   |   |   |
     * |---+---+-----------------------------------------------------------+---+---+---|   |
     * |   |   |    |    |    |           Fn4          |    |    |    |    |   |   |   |   |
     * `-----------------------------------------------------------------------------------'
     */
    KEYMAP(
        TRNS,TRNS,GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL, TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,UP,  TRNS,TRNS,TRNS,CALC,TRNS,INS, TRNS,PSCR,SLCK,PAUS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HOME,PGUP,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,APP, FN1, FN2, FN3, VOLD,VOLU,MUTE,END, PGDN,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,               FN4,                TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS  ),
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
    KEYMAP(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,UP,  TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,               TRNS,               TRNS,TRNS,TRNS,TRNS,LEFT,DOWN,RGHT,TRNS  ),
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
