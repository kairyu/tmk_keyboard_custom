#ifndef LEDMAP_IN_EEPROM_H
#define LEDMAP_IN_EEPROM_H

#ifndef EECONFIG_LEDMAP_IN_EEPROM
#define EECONFIG_LEDMAP_IN_EEPROM 7
#endif

#define EECONFIG_LEDMAP (uint8_t*)EECONFIG_LEDMAP_IN_EEPROM
#define LEDMAP_SIZE (sizeof(uint8_t) * LED_COUNT)

#define LEDMAP_UNCONFIGURED 0xFF

#ifdef LEDMAP_IN_EEPROM_ENABLE
#define ledmap_get_code ledmap_in_eeprom_get_code
void ledmap_in_eeprom_init(void);
void write_ledmap_to_eeprom(void);
uint8_t ledmap_in_eeprom_get_code(uint8_t index);
#else
#define ledmap_in_eeprom_init()
#define write_ledmap_to_eeprom()
#define ledmap_in_eeprom_get_code()
#endif

#endif
