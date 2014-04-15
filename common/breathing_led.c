#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "led.h"
#include "breathing_led.h"
#include "backlight.h"
#include "debug.h"

#define BREATHING_LED_TIMER_TOP F_CPU/64

breathing_led_config_t breathing_led_config;

void breathing_led_init(void)
{
    /* Timer3 setup */
    /* CTC mode */
    TCCR3B |= _BV(WGM12);
    /* Clock selelct: clk/1 */
    TCCR3B |= _BV(CS10);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR3AH = (BREATHING_LED_TIMER_TOP>>8)&0xff;
    OCR3AL = BREATHING_LED_TIMER_TOP&0xff;
    SREG = sreg;
}

bool breathing_led_is_enabled(void)
{
    return breathing_led_config.enable;
}

void breathing_led_enable(void)
{
    /* Enable Compare Match Interrupt */
    TIMSK3 |= _BV(OCIE3A);
    breathing_led_config.enable = true;
    dprintf("breathing led on: %u\n", breathing_led_config.enable);
    eeconfig_write_breathing_led(breathing_led_config.raw);
}

void breathing_led_disable(void)
{
    /* Disable Compare Match Interrupt */
    TIMSK3 &= ~_BV(OCIE3A);
    breathing_led_config.enable = false;
    dprintf("breathing led off: %u\n", breathing_led_config.enable);
    eeconfig_write_breathing_led(breathing_led_config.raw);
}

void breathing_led_toggle(void)
{
    /* Disable Compare Match Interrupt */
    TIMSK3 ^= _BV(OCIE3A);
    breathing_led_config.enable ^= 1;
    dprintf("breathing led toggle: %u\n", breathing_led_config.enable);
    eeconfig_write_breathing_led(breathing_led_config.raw);
}

void breathing_led_increase(void)
{
    if (breathing_led_config.enable) {
        if (breathing_led_config.level < BREATHING_LED_LEVELS) {
            breathing_led_config.level++;
            eeconfig_write_breathing_led(breathing_led_config.raw);
        }
        dprintf("breathing led speed increase: %u\n", breathing_led_config.level);
    }
}

void breathing_led_decrease(void)
{
    if (breathing_led_config.enable) {
        if (breathing_led_config.level > 0)
        {
            breathing_led_config.level--;
            eeconfig_write_breathing_led(breathing_led_config.raw);
        }
        dprintf("breathing led speed decrease: %u\n", breathing_led_config.level);
    }
}

/* Breathing LED brighness(PWM On period) table
 * (64[steps] * 4[duration]) / 64[PWM periods/s] = 4 second breath cycle
 *
 * http://www.wolframalpha.com/input/?i=%28sin%28+x%2F64*pi%29**8+*+255%2C+x%3D0+to+63
 * (0..63).each {|x| p ((sin(x/64.0*PI)**8)*255).to_i }
 */
static const uint8_t breathing_table[64] PROGMEM = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 6, 10,
15, 23, 32, 44, 58, 74, 93, 113, 135, 157, 179, 199, 218, 233, 245, 252,
255, 252, 245, 233, 218, 199, 179, 157, 135, 113, 93, 74, 58, 44, 32, 23,
15, 10, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

ISR(TIMER3_COMPA_vect)
{
    uint8_t index = 0;
    uint8_t step = 0;
    step++;
    if (step >= BREATHING_LED_LEVELS - breathing_led_config.level) {
        step = 0;
        index++;
        backlight_set_raw(pgm_read_byte(&breathing_table[index]));
    }
}
