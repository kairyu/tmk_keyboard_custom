#include <avr/pgmspace.h>
#include "ledmap.h"
#include "debug.h"


#ifdef LEDMAP_ENABLE

static const uint8_t ledmaps[LED_COUNT] PROGMEM = {
    [0] = LEDMAP_CAPS_LOCK | LEDMAP_BACKLIGHT,  // CapsLock
    [1] = LEDMAP_LAYER(2) | LEDMAP_BACKLIGHT,   // NumLock
    [2] = LEDMAP_BACKLIGHT,                     // Backlight
};

uint8_t ledmap_get_code(uint8_t index)
{
    return pgm_read_byte(&ledmaps[index]);
}

/* LED pin configration
 *   REV_V2
 *     CapsLock  PB5 (D9)
 *     NumLock   PB2 (D16)
 *     Backlight PB6 (D10)
 *   REV_V3
 *     CapsLock  PC7
 *     NumLock   PC6
 *     Backlight PB6
 */
void ledmap_led_init(void)
{
#if defined(REV_V2)
    DDRB  |=  (1<<PB5 | 1<<PB2);
    PORTB &= ~(1<<PB5 | 1<<PB2);
#elif defined(REV_V3)
    DDRC  |=  (1<<PC7 | 1<<PC6);
    PORTC &= ~(1<<PC7 | 1<<PC6);
#endif
    DDRB  |=  (1<<PB6);
    PORTB &= ~(1<<PB6);
}

void ledmap_led_on(uint8_t index)
{
#if defined(REV_V2)
    switch (index) {
        case 0:
            PORTB |= (1<<PB5);
            break;
        case 1:
            PORTB |= (1<<PB2);
            break;
        case 2:
            PORTB |= (1<<PB6);
            break;
    }
#elif defined(REV_V3)
    switch (index) {
        case 0:
            PORTC |= (1<<PC7);
            break;
        case 1:
            PORTC |= (1<<PC6);
            break;
        case 2:
            PORTB |= (1<<PB6);
            break;
    }
#endif
}

void ledmap_led_off(uint8_t index)
{
#if defined(REV_V2)
    switch (index) {
        case 0:
            PORTB &= ~(1<<PB5);
            break;
        case 1:
            PORTB &= ~(1<<PB2);
            break;
        case 2:
            PORTB &= ~(1<<PB6);
            break;
    }
#elif defined(REV_V3)
    switch (index) {
        case 0:
            PORTC &= ~(1<<PC7);
            break;
        case 1:
            PORTC &= ~(1<<PC6);
            break;
        case 2:
            PORTB &= ~(1<<PB6);
            break;
    }
#endif
}

#endif
