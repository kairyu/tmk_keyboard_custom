#include <avr/pgmspace.h>
#include "ledmap.h"
#include "debug.h"


#ifdef LEDMAP_ENABLE

static const uint16_t ledmaps[LED_COUNT] PROGMEM = {
#ifdef LEDMAP_V2
    [0] = LEDMAP_ACTIVE_LOW | LEDMAP_NUM_LOCK | LEDMAP_BACKLIGHT,   // LEDS1  - PB2
    [1] = LEDMAP_ACTIVE_LOW | LEDMAP_BACKLIGHT,                     // LEDS6  - PF7
    [2] = LEDMAP_ACTIVE_LOW | LEDMAP_BACKLIGHT,                     // LEDS11 - PF6
    [3] = LEDMAP_ACTIVE_LOW | LEDMAP_BACKLIGHT,                     // LEDS16 - PF5
    [4] = LEDMAP_ACTIVE_HIGH | LEDMAP_BACKLIGHT,                    // PWM    - PB5
#else
    [0] = LEDMAP_NUM_LOCK | LEDMAP_BACKLIGHT,   // LEDS1  - PB2
    [1] = LEDMAP_BACKLIGHT,                     // LEDS6  - PF7
    [2] = LEDMAP_BACKLIGHT,                     // LEDS11 - PF6
    [3] = LEDMAP_BACKLIGHT,                     // LEDS16 - PF5
    [4] = LEDMAP_BACKLIGHT,                     // PWM    - PB5
#endif
};

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

#ifndef LEDMAP_V2
void ledmap_led_init(void)
{
    DDRB  |=  (1<<PB2);
    PORTB |=  (1<<PB2);
    DDRF  |=  (1<<PF7 | 1<<PF6 | 1<<PF5);
    PORTF |=  (1<<PF7 | 1<<PF6 | 1<<PF5);
    DDRB  |=  (1<<PB5);
    PORTB &= ~(1<<PB5);
}

void ledmap_led_on(uint8_t index)
{
    switch (index) {
        case 0:
            PORTB &= ~(1<<PB2);
            break;
        case 1:
            PORTF &= ~(1<<PF7);
            break;
        case 2:
            PORTF &= ~(1<<PF6);
            break;
        case 3:
            PORTF &= ~(1<<PF5);
            break;
        case 4:
            PORTB |=  (1<<PB5);
            break;
    }
}

void ledmap_led_off(uint8_t index)
{
    switch (index) {
        case 0:
            PORTB |= (1<<PB2);
            break;
        case 1:
            PORTF |= (1<<PF7);
            break;
        case 2:
            PORTF |= (1<<PF6);
            break;
        case 3:
            PORTF |= (1<<PF5);
            break;
        case 4:
            PORTB &= ~(1<<PB5);
            break;
    }
}
#endif

#endif
