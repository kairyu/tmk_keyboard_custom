#include "keymap_common.h"

/* Default layout */
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |  `|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Del|
     * |---------------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |PgU|
     * |---------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Ctrl |Gui |Alt  |        Space         |Alt  |Ctrl |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     *                  |         Fn0          |
     *                  `----------------------'
     */
    KEYMAP(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,GRV,  \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,DEL,  \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT, PGUP, \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,UP,  PGDN, \
        LCTL,LGUI,LALT,          SPC,                     RALT,RCTL,LEFT,DOWN,RGHT, \
                                 FN0                                                ),
    /* Keymap 1: Fn Layer
     * ,---------------------------------------------------------------.
     * |Mut| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|       |   |
     * |---------------------------------------------------------------|
     * |     |   |Up |   |   |   |   |   |   |   |Psc|Slk|Pau|  Ins|   |
     * |---------------------------------------------------------------|
     * |      |Lef|Dow|Rig|   |   |   |   |   |   |   |   |Fn1     |Hom|
     * |---------------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |      |VoU|End|
     * |---------------------------------------------------------------|
     * |     |    |     |                      |     |     |Fn2|VoD|Fn3|
     * `---------------------------------------------------------------'
     *                  |                      |
     *                  `----------------------'
     */
    KEYMAP(
        MUTE,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS, \
        TRNS,TRNS,UP,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,INS, TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     FN1, HOME, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,VOLU,END,  \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,FN2, VOLD,FN3,  \
                                 TRNS                                               ),
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    /* Default layout */
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_BACKLIGHT_TOGGLE(),
    [2] = ACTION_BACKLIGHT_DECREASE(),
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

enum function_id {
    TRICKY_ESC = 0,
};

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    static uint8_t tricky_esc_registered;
    switch (id) {
        case TRICKY_ESC:
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
