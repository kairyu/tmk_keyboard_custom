#ifndef SOFTPWM_LED_H
#define SOFTPWM_LED_H

#include "stdint.h"
#include "led.h"

typedef led_pack_t led_state_t;

#ifdef SOFTPWM_LED_ENABLE

void softpwm_init(void);
void softpwm_led_init(void);
void softpwm_led_enable(void);
void softpwm_led_disable(void);
void softpwm_led_toggle(void);
void softpwm_led_set(uint8_t index, uint8_t val);
void softpwm_led_set_all(uint8_t val);
void softpwm_led_on(uint8_t index);
void softpwm_led_off(uint8_t index);
uint8_t softpwm_led_get_state(void);
void softpwm_led_state_change(uint8_t state);

#ifdef BREATHING_LED_ENABLE
#define breathing_led_init()
void breathing_led_enable(uint8_t index);
void breathing_led_enable_all(void);
void breathing_led_disable(uint8_t index);
void breathing_led_disable_all(void);
void breathing_led_toggle(uint8_t index);
void breathing_led_toggle_all(void);
void breathing_led_set_duration(uint8_t index, uint8_t dur);
void breathing_led_set_duration_all(uint8_t dur);
#else
#define breathing_led_init()
#define breathing_led_enable()
#define breathing_led_enable_all()
#define breathing_led_disable()
#define breathing_led_disable_all()
#define breathing_led_toggle()
#define breathing_led_toggle_all()
#define breathing_led_set_duration()
#define breathing_led_set_duration_all()
#endif

#else

#define softpwm_init()
#define softpwm_led_init()
#define softpwm_led_enable()
#define softpwm_led_disable()
#define softpwm_led_toggle()
#define softpwm_led_set()
#define softpwm_led_set_all()
#define softpwm_led_on()
#define softpwm_led_off()
#define softpwm_led_get_state()
#define softpwm_led_state_change()

#endif

#endif
