#ifndef BREATHING_LED_H
#define BREATHING_LED_H


#ifdef BREATHING_LED_ENABLE

void breathing_led_init(void);
void breathing_led_enable(void);
void breathing_led_disable(void);
void breathing_led_toggle(void);
void breathing_led_set_duration(uint8_t dur);
void breathing_led_set_raw(uint8_t raw);

#else

#define breathing_led_init()
#define breathing_led_enable()
#define breathing_led_disable()
#define breathing_led_toggle()
#define breathing_led_set_duration()
#define breathing_led_set_raw()

#endif

#endif
