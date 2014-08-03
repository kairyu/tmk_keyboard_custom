#ifndef LEDMAP_H
#define LEDMAP_H

#include "stdint.h"
#include "stdbool.h"
#include "led.h"

typedef led_pack_t led_state_t;
typedef led_pack_t led_binding_t;

typedef enum {
    LEDMAP_NO = 0,
    LEDMAP_DEFAULT_LAYER_0,
    LEDMAP_DEFAULT_LAYER_31 = LEDMAP_DEFAULT_LAYER_0 + 31,
    LEDMAP_LAYER_0,
    LEDMAP_LAYER_31 = LEDMAP_LAYER_0 + 31,
    LEDMAP_NUM_LOCK,
    LEDMAP_CAPS_LOCK,
    LEDMAP_SCROLL_LOCK,
    LEDMAP_COMPOSE,
    LEDMAP_KANA,
    LEDMAP_BACKLIGHT = 0x80
} ledmap_code_t;

#define LEDMAP_MASK 0x7F

typedef union {
    uint8_t raw;
    struct {
        uint8_t binding : 7;
        bool backlight : 1;
    };
} ledmap_t;

#define LEDMAP_DEFAULT_LAYER(x) (LEDMAP_DEFAULT_LAYER_0 + x)
#define LEDMAP_LAYER(x) (LEDMAP_LAYER_0 + x)

void ledmap_init(void);

#ifdef LEDMAP_ENABLE
uint8_t ledmap_get_code(uint8_t index);
void ledmap_led_init(void);
void ledmap_led_on(uint8_t index);
void ledmap_led_off(uint8_t index);
#else
#define ledmaps
#define ledmap_get()
#define ledmap_led_init()
#define ledmap_led_on()
#define ledmap_led_off()
#endif

#endif
