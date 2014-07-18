#ifndef SOFTPWM_LED_H
#define SOFTPWM_LED_H

#ifdef SOFTPWM_LED_ENABLE

void softpwm_led_init(void);
void softpwm_led_enable(void);
void softpwm_led_disable(void);
void softpwm_led_toggle(void);
void softpwm_led_set(uint8_t val);
void softpwm_led_on(void);
void softpwm_led_off(void);

#ifdef BREATHING_LED_ENABLE
#define breathing_led_init()
void breathing_led_enable(void);
void breathing_led_disable(void);
void breathing_led_toggle(void);
void breathing_led_set_duration(uint8_t dur);
#else
#define breathing_led_init()
#define breathing_led_enable()
#define breathing_led_disable()
#define breathing_led_toggle()
#define breathing_led_set_duration()
#endif

#else

#define softpwm_led_init()
#define softpwm_led_enable()
#define softpwm_led_disable()
#define softpwm_led_toggle()
#define softpwm_led_set()
#define softpwm_led_on()
#define softpwm_led_off()

#endif

#endif
