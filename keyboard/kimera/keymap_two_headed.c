#include "keymap_common.h"
#include "rgb_led.h"

// Two-headed
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_SIZE] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_SIZE] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,----------------------------------------.    ,------------------------------------------------.
     * |   |   |   |   ||Esc|   | F1| F2| F3| F4|    | | F5| F6| F7| F8| | F9|F10|F11|F12||Psc|Slk|Pus|
     * |---------------||-----------------------|    |-----------------------------------||-----------|
     * |Num|  /|  *|  -||  `|  1|  2|  3|  4|  5|    |  6|  7|  8|  9|  0|  -|  =|Backsp ||Ins|Hom|PgU|
     * |---------------||-------------------------.  `-----------------------------------||-----------|
     * |  7|  8|  9|   ||Tab  |  Q|  W|  E|  R|  T|    |  Y|  U|  I|  O|  P|  [|  ]|    \||Del|End|PgD|
     * |-----------|  +||--------------------------.   `---------------------------------||-----------|
     * |  4|  5|  6|   ||Caps  |  A|  S|  D|  F|  G|    |  H|  J|  K|  L|  ;|  '|Return  ||           |
     * |---------------||----------------------------.   `-------------------------------||   ,---.   |
     * |  1|  2|  3|   ||Shift   |  Z|  X|  C|  V|  B|    |  N|  M|  ,|  .|  /|Shift     ||   |Up |   |
     * |-----------|Ent||----------------------------|    |------------------------------||-----------|
     * |      0|  .|   ||Ctrl|Gui |Alt |    Space    |    |   Space  |Alt |Gui |App |Ctrl||Lef|Dow|Rig|
     * `---------------------------------------------'    `-------------------------------------------'
     */
    KEYMAP_16x16(
        NO,  NO,  NO,  NO,  ESC, NO,  F1,  F2,  F3,  F4,  NO,  NO,  NO,  NO,  NO,  NO, \
        NLCK,PSLS,PAST,PMNS,GRV, 1,   2,   3,   4,   5,   NO,  NO,  NO,  NO,  NO,  NO, \
        P7,  P8,  P9,  PPLS,TAB, Q,   W,   E,   R,   T,   NO,  NO,  NO,  NO,  NO,  NO, \
        P4,  P5,  P6,  NO,  CAPS,A,   S,   D,   F,   G,   NO,  NO,  NO,  NO,  NO,  NO, \
        P1,  P2,  P3,  PENT,LSFT,Z,   X,   C,   V,   B,   NO,  NO,  NO,  NO,  NO,  NO, \
        P0,  NO,  PDOT,NO,  LCTL,LGUI,LALT,NO,  SPC, NO,  NO,  NO,  NO,  NO,  NO,  NO, \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO, \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO, \

        F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,PAUS,NO,  NO,  NO,  NO,  NO, \
        6,   7,   8,   9,   0,   MINS,EQL, BSPC,INS, HOME,PGUP,NO,  NO,  NO,  NO,  NO, \
        Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,DEL, END, PGDN,NO,  NO,  NO,  NO,  NO, \
        H,   J,   K,   L,   SCLN,QUOT,NO,  ENT, NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO, \
        N,   M,   COMM,DOT, SLSH,NO,  NO,  RSFT,NO,  UP,  NO,  NO,  NO,  NO,  NO,  NO, \
        NO,  SPC, NO,  RALT,RGUI,APP, RCTL,NO,  LEFT,DOWN,RGHT,NO,  NO,  NO,  NO,  NO, \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO, \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO  ),
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_SIZE;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

#ifndef NO_ACTION_FUNCTION
enum function_id {
    AF_RGB_LED = 0
};

enum rgb_led_id {
    AF_RGB_LED_TOGGLE = 0,
    AF_RGB_LED_DECREASE,
    AF_RGB_LED_INCREASE,
    AF_RGB_LED_STEP,
    AF_RGB_LED_DECREASE_BRIGHTNESS,
    AF_RGB_LED_INCREASE_BRIGHTNESS
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
#ifdef RGB_LED_ENABLE
#define RGB_LED_BRIGHTNESS_STEP ((RGB_LED_BRIGHTNESS_MAX - RGB_LED_BRIGHTNESS_MIN) / 8)
    if (record->event.pressed) {
        switch (id) {
            case AF_RGB_LED:
                switch (opt) {
                    case AF_RGB_LED_TOGGLE:
                        rgb_led_toggle();
                        break;
                    case AF_RGB_LED_DECREASE:
                        rgb_led_decrease();
                        break;
                    case AF_RGB_LED_INCREASE:
                        rgb_led_increase();
                        break;
                    case AF_RGB_LED_STEP:
                        rgb_led_step();
                        break;
                    case AF_RGB_LED_DECREASE_BRIGHTNESS:
                        rgb_led_decrease_brightness(RGB_LED_BRIGHTNESS_STEP, true);
                        break;
                    case AF_RGB_LED_INCREASE_BRIGHTNESS:
                        rgb_led_increase_brightness(RGB_LED_BRIGHTNESS_STEP, true);
                        break;
                }
                break;
        }
    }
#endif
}
#endif
