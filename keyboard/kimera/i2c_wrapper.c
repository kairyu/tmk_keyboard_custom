/*
Copyright 2016 Kai Ryu <kai1103@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "i2cmaster.h"
#include "i2c_wrapper.h"
#include "debug.h"

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

#define SCL_CLOCK       400000L
#define SCL_DURATION    (1000000L/SCL_CLOCK)/2

static uint8_t i2c_wdt_enabled = 0;

extern uint8_t i2c_force_stop;

static void wdt_init(void);

void i2c_wrapper_init(void)
{
    /* init i2c */
    i2c_init();

    /* init watch dog */
    wdt_init();
}

void i2c_wrapper_task(void)
{
    /* reset watch dog counter */
    wdt_reset();
}

void wdt_init(void)
{
    cli();
    wdt_reset();
    wdt_intr_enable(WDTO_2S);
    sei();
}

ISR(WDT_vect)
{
    xprintf("i2c timeout\n");

    /* let slave to release SDA */
    TWCR = 0;
    DDRD |=  (1<<PD0);
    DDRD &= ~(1<<PD1);
    if (!(PIND & (1<<PD1))) {
        for (uint8_t i = 0; i < 9; i++) {
            PORTD &= ~(1<<PD0);
            _delay_us(SCL_DURATION);
            PORTD |= (1<<PD0);
            _delay_us(SCL_DURATION);
        }
    }

    /* send stop condition */
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

    /* escape from loop */
    i2c_force_stop = 1;
}
