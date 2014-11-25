#ifndef LEDMAP_H
#define LEDMAP_H

#include "stdint.h"
#include "stdbool.h"
#include "led.h"

typedef led_pack_t led_state_t;
typedef led_pack_t led_binding_t;

enum ledmap_binding {
    LEDMAP_BINDING_NO = 0,
    LEDMAP_BINDING_DEFAULT_LAYER,
    LEDMAP_BINDING_LAYER,
    LEDMAP_BINDING_USB_LED
};

enum ledmap_usb_led {
    LEDMAP_USB_LED_NUM_LOCK = 0,
    LEDMAP_USB_LED_CAPS_LOCK,
    LEDMAP_USB_LED_SCROLL_LOCK,
    LEDMAP_USB_LED_COMPOSE,
    LEDMAP_USB_LED_KANA,
};

typedef union {
    uint16_t code;
    struct {
        uint8_t param:      8;
        uint8_t binding:    4;
        bool reverse:       1;
        bool backlight:     1;
        uint8_t reserved:   2;
    };
} ledmap_t;

#define LEDMAP_DEFAULT_LAYER(layer) (LEDMAP_BINDING_DEFAULT_LAYER<<8 | layer)
#define LEDMAP_LAYER(layer)         (LEDMAP_BINDING_LAYER<<8 | layer )
#define LEDMAP_NUM_LOCK             (LEDMAP_BINDING_USB_LED<<8 | LEDMAP_USB_LED_NUM_LOCK)
#define LEDMAP_CAPS_LOCK            (LEDMAP_BINDING_USB_LED<<8 | LEDMAP_USB_LED_CAPS_LOCK)
#define LEDMAP_SCROLL_LOCK          (LEDMAP_BINDING_USB_LED<<8 | LEDMAP_USB_LED_SCROLL_LOCK)
#define LEDMAP_REVERSE              (1<<12)
#define LEDMAP_BACKLIGHT            (1<<13)

void ledmap_init(void);

#ifdef LEDMAP_ENABLE
ledmap_t ledmap_get_code(uint8_t index);
void ledmap_led_init(void);
void ledmap_led_on(uint8_t index);
void ledmap_led_off(uint8_t index);
#else
#define ledmap_get_code()
#define ledmap_led_init()
#define ledmap_led_on()
#define ledmap_led_off()
#endif

#endif
