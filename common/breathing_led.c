#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "breathing_led.h"
#include "debug.h"

#define BREATHING_LED_TIMER_TOP F_CPU/256

static uint8_t breathing_led_duration = 0;

void breathing_led_init(void)
{
#ifdef BREATHING_LED_TIMER1
    /* Timer1 setup */
    /* CTC mode */
    TCCR1B |= (1<<WGM12);
    /* Clock selelct: clk/8 */
    TCCR1B |= (1<<CS10);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR1AH = (BREATHING_LED_TIMER_TOP>>8)&0xff;
    OCR1AL = BREATHING_LED_TIMER_TOP&0xff;
#else
    /* Timer3 setup */
    /* CTC mode */
    TCCR3B |= (1<<WGM32);
    /* Clock selelct: clk/8 */
    TCCR3B |= (1<<CS30);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR3AH = (BREATHING_LED_TIMER_TOP>>8)&0xff;
    OCR3AL = BREATHING_LED_TIMER_TOP&0xff;
#endif
    SREG = sreg;
}

void breathing_led_enable(void)
{
    /* Enable Compare Match Interrupt */
#ifdef BREATHING_LED_TIMER1
    TIMSK1 |= (1<<OCIE1A);
    dprintf("breathing led on: %u\n", TIMSK1 & (1<<OCIE1A));
#else
    TIMSK3 |= (1<<OCIE3A);
    dprintf("breathing led on: %u\n", TIMSK3 & (1<<OCIE3A));
#endif
}

void breathing_led_disable(void)
{
    /* Disable Compare Match Interrupt */
#ifdef BREATHING_LED_TIMER1
    TIMSK1 &= ~(1<<OCIE1A);
    dprintf("breathing led off: %u\n", TIMSK1 & (1<<OCIE1A));
#else
    TIMSK3 &= ~(1<<OCIE3A);
    dprintf("breathing led off: %u\n", TIMSK3 & (1<<OCIE3A));
#endif
}

void breathing_led_toggle(void)
{
    /* Disable Compare Match Interrupt */
#ifdef BREATHING_LED_TIMER1
    TIMSK1 ^= (1<<OCIE1A);
    dprintf("breathing led toggle: %u\n", TIMSK1 & (1<<OCIE1A));
#else
    TIMSK3 ^= (1<<OCIE3A);
    dprintf("breathing led toggle: %u\n", TIMSK3 & (1<<OCIE3A));
#endif
}

void breathing_led_set_duration(uint8_t dur)
{
    breathing_led_duration = dur;
    dprintf("breathing led set duration: %u\n", breathing_led_duration);
}

/* Breathing LED brighness(PWM On period) table
 *
 * http://www.wolframalpha.com/input/?i=Table%5Bfloor%28%28exp%28sin%28x%2F256*2*pi%2B3%2F2*pi%29%29-1%2Fe%29*%28256%2F%28e-1%2Fe%29%29%29%2C+%7Bx%2C0%2C255%2C1%7D%5D
 * Table[floor((exp(sin(x/256*2*pi+3/2*pi))-1/e)*(256/(e-1/e))), {x,0,255,1}]
 * (0..255).each {|x| print ((exp(sin(x/256.0*2*PI+3.0/2*PI))-1/E)*(256/(E-1/E))).to_i, ', ' }
 */
static const uint8_t breathing_table[256] PROGMEM = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 10, 11, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 29, 30, 32, 34, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 56, 58, 61, 63, 66, 68, 71, 74, 77, 80, 83, 86, 89, 92, 95, 98, 102, 105, 108, 112, 116, 119, 123, 126, 130, 134, 138, 142, 145, 149, 153, 157, 161, 165, 169, 173, 176, 180, 184, 188, 192, 195, 199, 203, 206, 210, 213, 216, 219, 223, 226, 228, 231, 234, 236, 239, 241, 243, 245, 247, 248, 250, 251, 252, 253, 254, 255, 255, 255, 255, 255, 255, 255, 254, 253, 252, 251, 250, 248, 247, 245, 243, 241, 239, 236, 234, 231, 228, 226, 223, 219, 216, 213, 210, 206, 203, 199, 195, 192, 188, 184, 180, 176, 173, 169, 165, 161, 157, 153, 149, 145, 142, 138, 134, 130, 126, 123, 119, 116, 112, 108, 105, 102, 98, 95, 92, 89, 86, 83, 80, 77, 74, 71, 68, 66, 63, 61, 58, 56, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 34, 32, 30, 29, 27, 26, 25, 23, 22, 21, 19, 18, 17, 16, 15, 14, 13, 12, 11, 11, 10, 9, 8, 8, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#ifdef BREATHING_LED_TIMER1
ISR(TIMER1_COMPA_vect)
#else
ISR(TIMER3_COMPA_vect)
#endif
{
    static uint8_t index = 0;
    static uint8_t step = 0;
    step++;
    if (step > breathing_led_duration) {
        step = 0;
        breathing_led_set_raw(pgm_read_byte(&breathing_table[index]));
        index++;
    }
}
