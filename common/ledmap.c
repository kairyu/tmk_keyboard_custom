#include "ledmap.h"
#include "ledmap_in_eeprom.h"
#include "led.h"
#include "softpwm_led.h"
#include "action_layer.h"
#include "debug.h"

static led_state_t led_state_last = 0;
static led_binding_t usb_led_binding = 0;
static led_binding_t default_layer_binding = 0;
static led_binding_t layer_binding = 0;
static led_binding_t backlight_binding = 0;

static void update_led_state(led_state_t state);

void ledmap_init(void)
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        uint8_t code = ledmap_get_code(i);
        if (code & LEDMAP_BACKLIGHT) {
            LED_BIT_SET(backlight_binding, i);
        }
        code &= LEDMAP_MASK;
        if (code >= LEDMAP_DEFAULT_LAYER_0 && code <= LEDMAP_DEFAULT_LAYER_31) {
            LED_BIT_SET(default_layer_binding, i);
        }
        else if (code >= LEDMAP_LAYER_0 && code <= LEDMAP_LAYER_31) {
            LED_BIT_SET(layer_binding, i);
        }
        else if (code >= LEDMAP_NUM_LOCK && code <= LEDMAP_KANA) {
            LED_BIT_SET(usb_led_binding, i);
        }
    }
    ledmap_led_init();
}

void led_set(uint8_t usb_led)
{
    if (usb_led_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (usb_led_binding & LED_BIT(i)) {
                uint8_t code = ledmap_get_code(i) & LEDMAP_MASK;
                for (uint8_t j = USB_LED_NUM_LOCK; j <= USB_LED_KANA; j++) {
                    if (code - LEDMAP_NUM_LOCK == j) {
                        (usb_led & (1 << j)) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
                    }
                }
            }
        }
        update_led_state(led_state);
    }
}

#ifndef NO_ACTION_LAYER
void default_layer_state_change(uint32_t state)
{
    if (default_layer_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (default_layer_binding & LED_BIT(i)) {
                uint8_t code = ledmap_get_code(i) & LEDMAP_MASK;
                (state & (1UL << (code - LEDMAP_DEFAULT_LAYER_0))) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
            }
        }
        update_led_state(led_state);
    }
}

void layer_state_change(uint32_t state)
{
    if (layer_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (layer_binding & LED_BIT(i)) {
                uint8_t code = ledmap_get_code(i) & LEDMAP_MASK;
                (state & (1UL << (code - LEDMAP_LAYER_0))) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
            }
        }
        update_led_state(led_state);
    }
}
#endif

#ifdef SOFTPWM_LED_ENABLE
void softpwm_led_init(void)
{
}

void softpwm_led_on(uint8_t index)
{
    if (backlight_binding & LED_BIT(index)) {
        ledmap_led_on(index);
    }
}

void softpwm_led_off(uint8_t index)
{
    if (backlight_binding & LED_BIT(index)) {
        ledmap_led_off(index);
    }
}

void softpwm_led_state_change(uint8_t state)
{
    if (state) {
    }
    else {
        led_state_t led_state = led_state_last;
        led_state_last &= ~(backlight_binding);
        update_led_state(led_state);
    }
}
#endif

void update_led_state(led_state_t state)
{
    uint8_t diff = led_state_last ^ state;
    if (diff) {
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (softpwm_led_get_state() && (backlight_binding & LED_BIT(i))) {
                continue;
            }
            if (diff & LED_BIT(i)) {
                if (state & LED_BIT(i)) {
                    ledmap_led_on(i);
                }
                else {
                    ledmap_led_off(i);
                }
            }
        }
        led_state_last = state;
    }
}
