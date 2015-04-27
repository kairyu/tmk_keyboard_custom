#ifndef SOFTPWM_LED_H
#define SOFTPWM_LED_H

#include "stdint.h"
#include "led.h"


#ifdef SOFTPWM_LED_ENABLE

void softpwm_init(void);
void softpwm_led_init(void);
void softpwm_led_enable(void);
void softpwm_led_disable(void);
void softpwm_led_toggle(void);
void softpwm_led_set(uint8_t index, uint8_t val);
void softpwm_led_set_all(uint8_t val);
void softpwm_led_increase(uint8_t index, uint8_t offset);
void softpwm_led_increase_all(uint8_t offset);
void softpwm_led_decrease(uint8_t index, uint8_t offset);
void softpwm_led_decrease_all(uint8_t offset);
void softpwm_led_on(uint8_t index);
void softpwm_led_off(uint8_t index);
uint8_t softpwm_led_get_state(void);
void softpwm_led_state_change(uint8_t state);

enum {
    FADING_LED_FADE_IN = 0,
    FADING_LED_FADE_OUT
};
#ifdef FADING_LED_ENABLE
void fading_led_enable(uint8_t index);
void fading_led_enable_all(void);
void fading_led_disable(uint8_t index);
void fading_led_disable_all(void);
void fading_led_toggle(uint8_t index);
void fading_led_toggle_all(void);
void fading_led_set_direction(uint8_t index, uint8_t dir);
void fading_led_set_direction_all(uint8_t dir);
void fading_led_set_duration(uint8_t dur);
void fading_led_set_delay(uint8_t index, uint8_t delay);
void fading_led_set_delay_all(uint8_t delay);
#else
#define fading_led_enable()
#define fading_led_enable_all()
#define fading_led_disable()
#define fading_led_disable_all()
#define fading_led_toggle()
#define fading_led_toggle_all()
#define fading_led_set_direction()
#define fading_led_set_direction_all()
#define fading_led_set_duration()
#define fading_led_set_delay()
#define fading_led_set_delay_all()
#endif

#ifdef BREATHING_LED_ENABLE
#define breathing_led_init()
void breathing_led_enable(uint8_t index);
void breathing_led_enable_once(uint8_t index);
void breathing_led_enable_all(void);
void breathing_led_disable(uint8_t index);
void breathing_led_disable_all(void);
void breathing_led_toggle(uint8_t index);
void breathing_led_toggle_all(void);
void breathing_led_set_duration(uint8_t dur);
void breathing_led_set_index(uint8_t index, uint8_t value);
void breathing_led_set_index_all(uint8_t value);
void breathing_led_set_delay(uint8_t index, uint8_t delay);
void breathing_led_set_delay_all(uint8_t delay);
#else
#define breathing_led_init()
#define breathing_led_enable()
#define breathing_led_enable_all()
#define breathing_led_disable()
#define breathing_led_disable_all()
#define breathing_led_toggle()
#define breathing_led_toggle_all()
#define breathing_led_set_duration()
#define breathing_led_set_index()
#define breathing_led_set_index_all()
#define breathing_led_set_delay()
#define breathing_led_set_delay_all()
#endif

#ifdef CUSTOM_LED_ENABLE
void softpwm_led_custom(void);
void fading_led_custom(uint8_t *value);
void breathing_led_custom(uint8_t *value);
#else
#define custom_led_proc()
#endif

#else

#define softpwm_init()
#define softpwm_led_init()
#define softpwm_led_enable()
#define softpwm_led_disable()
#define softpwm_led_toggle()
#define softpwm_led_set()
#define softpwm_led_set_all()
#define softpwm_led_increase()
#define softpwm_led_increase_all()
#define softpwm_led_decrease()
#define softpwm_led_decrease_all()
#define softpwm_led_on()
#define softpwm_led_off()
#define softpwm_led_get_state()
#define softpwm_led_state_change()

#endif

#endif
