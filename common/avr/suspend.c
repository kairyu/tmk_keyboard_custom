#include <stdbool.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "matrix.h"
#include "action.h"
#include "backlight.h"
#include "softpwm_led.h"
#include "suspend_avr.h"
#include "suspend.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#endif


#define wdt_intr_enable(value)   \
__asm__ __volatile__ (  \
    "in __tmp_reg__,__SREG__" "\n\t"    \
    "cli" "\n\t"    \
    "wdr" "\n\t"    \
    "sts %0,%1" "\n\t"  \
    "out __SREG__,__tmp_reg__" "\n\t"   \
    "sts %0,%2" "\n\t" \
    : /* no outputs */  \
    : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
    "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)), \
    "r" ((uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) | \
        _BV(WDIE) | (value & 0x07)) ) \
    : "r0"  \
)

void suspend_idle(uint8_t time)
{
    cli();
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
}

/* Power down MCU with watchdog timer
 * wdto: watchdog timer timeout defined in <avr/wdt.h>
 *          WDTO_15MS
 *          WDTO_30MS
 *          WDTO_60MS
 *          WDTO_120MS
 *          WDTO_250MS
 *          WDTO_500MS
 *          WDTO_1S
 *          WDTO_2S
 *          WDTO_4S
 *          WDTO_8S
 */
void suspend_power_down(uint8_t wdto)
{
#ifdef PROTOCOL_LUFA
    if (USB_DeviceState == DEVICE_STATE_Configured) return;
#endif

    // Watchdog Interrupt Mode
    wdt_intr_enable(wdto);

    // TODO: more power saving
    // See PicoPower application note
    // - I/O port input with pullup
    // - prescale clock
    // - BOD disable
    // - Power Reduction Register PRR

#ifdef SUSPEND_ACTION
    suspend_power_down_action();
#endif

#ifdef SOFTPWM_LED_ENABLE
    softpwm_led_disable();
#endif

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();

    // Disable watchdog after sleep
    wdt_disable();
}

bool suspend_wakeup_condition(void)
{
    matrix_power_up();
    matrix_scan();
    matrix_power_down();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        if (matrix_get_row(r)) return true;
    }
    return false;
}

// run immediately after wakeup
void suspend_wakeup_init(void)
{
    // clear keyboard state
    clear_keyboard();
#ifdef SUSPEND_ACTION
    suspend_wakeup_init_action();
#endif
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
}

#ifndef NO_SUSPEND_POWER_DOWN
/* watchdog timeout */
ISR(WDT_vect)
{
    /* wakeup from MCU sleep mode */
/*
    // blink LED
    static uint8_t led_state = 0;
    static uint8_t led_count = 0;
    led_count++;
    if ((led_count & 0x07) == 0) {
        led_set((led_state ^= (1<<USB_LED_CAPS_LOCK)));
    }
*/
}
#endif

#ifdef SUSPEND_ACTION
__attribute__ ((weak))
void suspend_power_down_action(void)
{
}

__attribute__ ((weak))
void suspend_wakeup_init_action(void)
{
}
#endif
