#ifndef LEDMAP_H
#define LEDMAP_H

#include "stdint.h"

#if (LED_COUNT <= 8)
typedef uint8_t  led_pack_t;
#elif (LED_COUNT <= 16)
typedef uint16_t led_pack_t;
#elif (LED_COUNT <= 32)
typedef uint32_t led_pack_t;
#else
#error "LED_COUNT: invalid value"
#endif

typedef led_pack_t led_state_t;

#if (LED_COUNT <= 16)
#define LED_BIT(i) (1U<<(i))
#elif (LED_COUNT <= 32)
#define LED_BIT(i) (1UL<<(i))
#else
#error "LED_COUNT: invalid value"
#endif

#define LED_BIT_ON(state, i) ((state) |= LED_BIT(i))
#define LED_BIT_OFF(state, i) ((state) &= ~LED_BIT(i))

typedef enum {
    LEDMAP_DEFAULT_LAYER_0 = 0,
    LEDMAP_DEFAULT_LAYER_31 = 31,
    LEDMAP_LAYER_0 = 32,
    LEDMAP_LAYER_31 = 63,
    LEDMAP_NUM_LOCK = 64,
    LEDMAP_CAPS_LOCK,
    LEDMAP_SCROLL_LOCK,
    LEDMAP_COMPOSE,
    LEDMAP_KANA,
    LEDMAP_BACKLIGHT = 0x80,
    LEDMAP_UNCONFIGURED = 0xFF
} ledmap_code_t;

#define LEDMAP_DEFAULT_LAYER(x) (LEDMAP_DEFAULT_LAYER_0 + x)
#define LEDMAP_LAYER(x) (LEDMAP_LAYER_0 + x)

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
