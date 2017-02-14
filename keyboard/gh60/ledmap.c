#include <avr/pgmspace.h>
#include "ledmap.h"
#include "debug.h"


#ifdef LEDMAP_ENABLE

static const uint16_t ledmaps[LED_COUNT] PROGMEM = {
#ifdef LEDMAP_V2
#if defined(GH60_REV_CHN)
    [0] = LEDMAP_ACTIVE_LOW | LEDMAP_CAPS_LOCK | LEDMAP_BACKLIGHT,  // CapsLock - PB2
    [1] = LEDMAP_ACTIVE_HIGH | LEDMAP_BACKLIGHT,                    // PWM      - PB6
#else
    [0] = LEDMAP_ACTIVE_LOW | LEDMAP_CAPS_LOCK | LEDMAP_BACKLIGHT,  // CapsLock - PB2
    [1] = LEDMAP_ACTIVE_LOW | LEDMAP_BACKLIGHT,                     // Esc      - GPIO1 - PF6
    [2] = LEDMAP_ACTIVE_LOW | LEDMAP_LAYER(1) | LEDMAP_BACKLIGHT,   // WASD     - GPIO0 - PF7
    [3] = LEDMAP_ACTIVE_LOW | LEDMAP_LAYER(2) | LEDMAP_BACKLIGHT,   // Sh/Al/Ct - GPIO3 - PF4
    [4] = LEDMAP_ACTIVE_LOW | LEDMAP_LAYER(1) | LEDMAP_BACKLIGHT,   // Fn       - GPIO2 - PF5
#endif
#else
#if defined(GH60_REV_CHN)
    [0] = LEDMAP_CAPS_LOCK | LEDMAP_BACKLIGHT,  // CapsLock - PB2
    [1] = LEDMAP_BACKLIGHT,                     // PWM      - PB6
#else
    [0] = LEDMAP_CAPS_LOCK | LEDMAP_BACKLIGHT,  // CapsLock - PB2
    [1] = LEDMAP_BACKLIGHT,                     // Esc      - GPIO1 - PF6
    [2] = LEDMAP_LAYER(1) | LEDMAP_BACKLIGHT,   // WASD     - GPIO0 - PF7
    [3] = LEDMAP_LAYER(2) | LEDMAP_BACKLIGHT,   // Sh/Al/Ct - GPIO3 - PF4
    [4] = LEDMAP_LAYER(1) | LEDMAP_BACKLIGHT,   // Fn       - GPIO2 - PF5
#endif
#endif
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

#ifndef LEDMAP_V2
void ledmap_led_init(void)
{
    DDRB |= (1<<PB2);
    PORTB |= (1<<PB2);
#if defined(GH60_REV_CHN)
    DDRB  |= (1<<PB6);
    PORTB &= ~(1<<PB6);
#else
    DDRF  |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    PORTF |= (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
#endif
}

void ledmap_led_on(uint8_t index)
{
#if defined(GH60_REV_CHN)
    switch (index) {
        case 0:
            PORTB &= ~(1<<PB2);
            break;
        case 1:
            PORTB |= (1<<PB6);
            break;
    }
#else
    switch (index) {
        case 0:
            PORTB &= ~(1<<PB2);
            break;
        case 1:
            PORTF &= ~(1<<PF6);
            break;
        case 2:
            PORTF &= ~(1<<PF7);
            break;
        case 3:
            PORTF &= ~(1<<PF4);
            break;
        case 4:
            PORTF &= ~(1<<PF5);
            break;
    }
#endif
}

void ledmap_led_off(uint8_t index)
{
#if defined(GH60_REV_CHN)
    switch (index) {
        case 0:
            PORTB |= (1<<PB2);
            break;
        case 1:
            PORTB &= ~(1<<PB6);
            break;
    }
#else
    switch (index) {
        case 0:
            PORTB |= (1<<PB2);
            break;
        case 1:
            PORTF |= (1<<PF6);
            break;
        case 2:
            PORTF |= (1<<PF7);
            break;
        case 3:
            PORTF |= (1<<PF4);
            break;
        case 4:
            PORTF |= (1<<PF5);
            break;
    }
#endif
}
#endif

#endif
