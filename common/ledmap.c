#include "ledmap.h"
#include "led.h"
#include "softpwm_led.h"
#include "action_layer.h"

static led_state_t led_state = 0;
static led_state_t led_state_last = 0;

static void update_led_state(void);

void led_set(uint8_t usb_led)
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        uint8_t code = ledmap_get_code(i);
        switch (code) {
            case LEDMAP_NUM_LOCK:
                usb_led & (1 << USB_LED_NUM_LOCK) ? LED_BIT_ON(led_state, i) : LED_BIT_OFF(led_state, i);
                break;
            case LEDMAP_CAPS_LOCK:
                usb_led & (1 << USB_LED_CAPS_LOCK) ? LED_BIT_ON(led_state, i) : LED_BIT_OFF(led_state, i);
                break;
            case LEDMAP_SCROLL_LOCK:
                usb_led & (1 << USB_LED_SCROLL_LOCK) ? LED_BIT_ON(led_state, i) : LED_BIT_OFF(led_state, i);
                break;
            case LEDMAP_COMPOSE:
                usb_led & (1 << USB_LED_COMPOSE) ? LED_BIT_ON(led_state, i) : LED_BIT_OFF(led_state, i);
                break;
            case LEDMAP_KANA:
                usb_led & (1 << USB_LED_KANA) ? LED_BIT_ON(led_state, i) : LED_BIT_OFF(led_state, i);
                break;
            default:
                break;
        }
    }
    update_led_state();
}

#ifndef NO_ACTION_LAYER
void default_layer_state_change(uint32_t state)
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        uint8_t code = ledmap_get_code(i);
        if (code >= LEDMAP_DEFAULT_LAYER_0 && code < LEDMAP_DEFAULT_LAYER_31) {
            state & (1UL << (code - LEDMAP_DEFAULT_LAYER_0)) ? LED_BIT_ON(led_state, i) : LED_BIT_OFF(led_state, i);
        }
    }
    update_led_state();
}

void layer_state_change(uint32_t state)
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        uint8_t code = ledmap_get_code(i);
        if (code >= LEDMAP_LAYER_0 && code < LEDMAP_LAYER_31) {
            state & (1UL << (code - LEDMAP_LAYER_0)) ? LED_BIT_ON(led_state, i) : LED_BIT_OFF(led_state, i);
        }
    }
    update_led_state();
}
#endif

#ifdef SOFTPWM_LED_ENABLE
void softpwm_led_on()
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        uint8_t code = ledmap_get_code(i);
        if (code == LEDMAP_BACKLIGHT) {
            ledmap_led_on(i);
        }
    }
}

void softpwm_led_off()
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        uint8_t code = ledmap_get_code(i);
        if (code == LEDMAP_BACKLIGHT) {
            ledmap_led_off(i);
        }
    }
}
#endif

void update_led_state(void)
{
    uint8_t diff = led_state_last ^ led_state;
    if (diff) {
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (diff & LED_BIT(i)) {
                if (led_state & LED_BIT(i)) {
                    ledmap_led_on(i);
                }
                else {
                    ledmap_led_off(i);
                }
            }
        }
        led_state_last = led_state;
    }
}
