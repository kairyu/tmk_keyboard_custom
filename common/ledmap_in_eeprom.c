#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "ledmap.h"
#include "ledmap_in_eeprom.h"

#ifdef LEDMAP_IN_EEPROM_ENABLE

#undef ledmap_get_code

static uint8_t ledmap[LED_COUNT];

void ledmap_in_eeprom_init(void)
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        ledmap[i] = eeprom_read_byte(EECONFIG_LEDMAP + i);
        //ledmap[i] = LEDMAP_UNCONFIGURED;
        if (ledmap[i] == LEDMAP_UNCONFIGURED) {
            ledmap[i] = ledmap_get_code(i);
            eeprom_write_byte(EECONFIG_LEDMAP + i, ledmap[i]);
        }
    }
}

void write_ledmap_to_eeprom(void)
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        eeprom_write_byte(EECONFIG_LEDMAP + i, ledmap_get_code(i));
    }
}

uint8_t ledmap_in_eeprom_get_code(uint8_t i)
{
    return ledmap[i];
}

#endif
