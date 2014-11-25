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
static led_binding_t reverse_binding = 0;

static void update_led_state(led_state_t state, uint8_t force);

void ledmap_init(void)
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        ledmap_t ledmap = ledmap_get_code(i);
        if (ledmap.reverse) {
            LED_BIT_SET(reverse_binding, i);
        }
        if (ledmap.backlight) {
            LED_BIT_SET(backlight_binding, i);
        }
        switch (ledmap.binding) {
            case LEDMAP_BINDING_DEFAULT_LAYER:
                LED_BIT_SET(default_layer_binding, i);
                break;
            case LEDMAP_BINDING_LAYER:
                LED_BIT_SET(layer_binding, i);
                break;
            case LEDMAP_BINDING_USB_LED:
                LED_BIT_SET(usb_led_binding, i);
                break;
        }
    }
    ledmap_led_init();
    update_led_state(0, 1);
}

void led_set(uint8_t usb_led)
{
    if (usb_led_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (usb_led_binding & LED_BIT(i)) {
                uint8_t param = ledmap_get_code(i).param;
                (usb_led & (1 << param)) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
            }
        }
        update_led_state(led_state, 0);
    }
}

#ifndef NO_ACTION_LAYER
void default_layer_state_change(uint32_t state)
{
    if (default_layer_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (default_layer_binding & LED_BIT(i)) {
                uint8_t param = ledmap_get_code(i).param;
                (state & (1UL << param)) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
            }
        }
        update_led_state(led_state, 0);
    }
}

void layer_state_change(uint32_t state)
{
    if (layer_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (layer_binding & LED_BIT(i)) {
                uint8_t param = ledmap_get_code(i).param;
                (state & (1UL << param)) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
            }
        }
        update_led_state(led_state, 0);
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
        update_led_state(led_state_last, 1);
    }
}
#endif

void update_led_state(led_state_t state, uint8_t force)
{
    led_state_t diff = led_state_last ^ state;
    if (force || diff) {
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (softpwm_led_get_state() && (backlight_binding & LED_BIT(i))) {
                continue;
            }
            if (force || diff & LED_BIT(i)) {
                if ((state ^ reverse_binding) & LED_BIT(i)) {
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
