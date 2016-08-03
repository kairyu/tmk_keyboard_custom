#include <avr/pgmspace.h>
#include "ledmap.h"
#include "debug.h"


#ifdef LEDMAP_ENABLE

static const uint16_t ledmaps[LED_COUNT] PROGMEM = {
    [0] = LEDMAP_NUM_LOCK,
    [1] = LEDMAP_CAPS_LOCK,
    [2] = LEDMAP_SCROLL_LOCK
};
static uint8_t usb_led;
void kbd_led_set(uint8_t usb_led);

ledmap_t ledmap_get_code(uint8_t index)
{
    return (ledmap_t) { .code = pgm_read_word(&ledmaps[index]) };
}

void ledmap_led_init(void)
{
    usb_led = 0;
}

void ledmap_led_on(uint8_t index)
{
    usb_led |= (1<<index);
    kbd_led_set(usb_led);
}

void ledmap_led_off(uint8_t index)
{
    usb_led &= ~(1<<index);
    kbd_led_set(usb_led);
}

#endif
