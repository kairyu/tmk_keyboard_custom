#ifndef BREATHING_LED_H
#define BREATHING_LED_H


#ifdef BREATHING_LED_ENABLE

#include <stdint.h>
#include <stdbool.h>

#ifndef BREATHING_LED_LEVEL
#define BREATHING_LED_LEVEL 1
#endif

typedef union {
    uint8_t raw;
    struct {
        bool    enable:1;
        uint8_t level:7;
    };
} breathing_led_config_t;

void breathing_led_init(void);
bool breathing_led_is_enabled(void);
void breathing_led_enable(void);
void breathing_led_disable(void);
void breathing_led_toggle(void);
void breathing_led_increase(void);
void breathing_led_decrease(void);

#else

#define breathing_led_init()
#define breathing_led_enable()
#define breathing_led_disable()
#define breathing_led_toggle()

#endif

#endif
