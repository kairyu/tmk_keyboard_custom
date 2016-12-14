/*************************************************************************
 * Title:    I2C master library using hardware TWI interface
 * Author:   Peter Fleury <pfleury@gmx.ch>  http://jump.to/fleury
 * File:     $Id: twimaster.c,v 1.3 2005/07/02 11:14:21 Peter Exp $
 * Software: AVR-GCC 3.4.3 / avr-libc 1.2.3
 * Target:   any AVR device with hardware TWI
 * Usage:    API compatible with I2C Software Library i2cmaster.h
 **************************************************************************/
#include <inttypes.h>
#include <compat/twi.h>
#include <util/delay.h>

#include <i2cmaster.h>
#include "timer.h"
#include "debug.h"


/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 4000000UL
#endif

/* I2C clock in Hz */
#define SCL_CLOCK  400000L
#define SCL_DURATION    (1000000L/SCL_CLOCK)/2

volatile uint8_t i2c_force_stop = 0;
#define TIMEOUT 3000
#define CHECK_FORCE_STOP() if(i2c_force_stop){i2c_force_stop=0;break;}
#define CHECK_TIMEOUT_PRE() \
    uint16_t start; \
    uint8_t once = 1;
#define CHECK_TIMEOUT_PRE2() \
    once = 1;
#define CHECK_TIMEOUT(retval) { \
    if (once) { \
        start = timer_read(); \
        once = 0; \
    } \
    else { \
        if (timer_elapsed(start) >= TIMEOUT) { \
            i2c_forceStop(); \
            return retval; \
        } \
    } \
}

static void i2c_forceStop(void);

/*************************************************************************
  Initialization of the I2C bus interface. Need to be called only once
 *************************************************************************/
void i2c_init(void)
{
    /* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */

    TWSR = 0;                         /* no prescaler */
    TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */

}/* i2c_init */


/*************************************************************************
  Issues a start condition and sends address and transfer direction.
  return 0 = device accessible, 1= failed to access device
 *************************************************************************/
unsigned char i2c_start(unsigned char address)
{
    uint8_t   twst;

    // send START condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

    // wait until transmission completed
    CHECK_TIMEOUT_PRE();
    while(!(TWCR & (1<<TWINT))) { CHECK_TIMEOUT(2); };

    // check value of TWI Status Register. Mask prescaler bits.
    twst = TW_STATUS & 0xF8;
    if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;

    // send device address
    TWDR = address;
    TWCR = (1<<TWINT) | (1<<TWEN);

    // wail until transmission completed and ACK/NACK has been received
    CHECK_TIMEOUT_PRE2();
    while(!(TWCR & (1<<TWINT))) { CHECK_TIMEOUT(2); };

    // check value of TWI Status Register. Mask prescaler bits.
    twst = TW_STATUS & 0xF8;
    if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

    return 0;

}/* i2c_start */


/*************************************************************************
  Issues a start condition and sends address and transfer direction.
  If device is busy, use ack polling to wait until device is ready

Input:   address and transfer direction of I2C device
 *************************************************************************/
void i2c_start_wait(unsigned char address)
{
    uint8_t   twst;


    while ( 1 )
    {
        // send START condition
        TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

        // wait until transmission completed
        while(!(TWCR & (1<<TWINT)));

        // check value of TWI Status Register. Mask prescaler bits.
        twst = TW_STATUS & 0xF8;
        if ( (twst != TW_START) && (twst != TW_REP_START)) continue;

        // send device address
        TWDR = address;
        TWCR = (1<<TWINT) | (1<<TWEN);

        // wail until transmission completed
        while(!(TWCR & (1<<TWINT)));

        // check value of TWI Status Register. Mask prescaler bits.
        twst = TW_STATUS & 0xF8;
        if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
        {
            /* device busy, send stop condition to terminate write operation */
            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

            // wait until stop condition is executed and bus released
            CHECK_TIMEOUT_PRE();
            while(TWCR & (1<<TWSTO)) { CHECK_TIMEOUT(); };

            continue;
        }
        //if( twst != TW_MT_SLA_ACK) return 1;
        break;
    }

}/* i2c_start_wait */


/*************************************************************************
  Issues a repeated start condition and sends address and transfer direction

Input:   address and transfer direction of I2C device

Return:  0 device accessible
1 failed to access device
 *************************************************************************/
unsigned char i2c_rep_start(unsigned char address)
{
    return i2c_start( address );

}/* i2c_rep_start */


/*************************************************************************
  Terminates the data transfer and releases the I2C bus
 *************************************************************************/
void i2c_stop(void)
{
    /* send stop condition */
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

    // wait until stop condition is executed and bus released
    CHECK_TIMEOUT_PRE();
    while(TWCR & (1<<TWSTO)) { CHECK_TIMEOUT(); };

}/* i2c_stop */


/*************************************************************************
  Send one byte to I2C device

Input:    byte to be transfered
Return:   0 write successful
1 write failed
 *************************************************************************/
unsigned char i2c_write( unsigned char data )
{
    uint8_t   twst;

    // send data to the previously addressed device
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);

    // wait until transmission completed
    CHECK_TIMEOUT_PRE();
    while(!(TWCR & (1<<TWINT))) { CHECK_TIMEOUT(2) };

    // check value of TWI Status Register. Mask prescaler bits
    twst = TW_STATUS & 0xF8;
    if( twst != TW_MT_DATA_ACK) return 1;
    return 0;

}/* i2c_write */


/*************************************************************************
  Read one byte from the I2C device, request more data from device

Return:  byte read from I2C device
 *************************************************************************/
unsigned char i2c_readAck(void)
{
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
    CHECK_TIMEOUT_PRE();
    while(!(TWCR & (1<<TWINT))) { CHECK_TIMEOUT(2); };

    return TWDR;

}/* i2c_readAck */


/*************************************************************************
  Read one byte from the I2C device, read is followed by a stop condition

Return:  byte read from I2C device
 *************************************************************************/
unsigned char i2c_readNak(void)
{
    TWCR = (1<<TWINT) | (1<<TWEN);
    CHECK_TIMEOUT_PRE();
    while(!(TWCR & (1<<TWINT))) { CHECK_TIMEOUT(2); };

    return TWDR;

}/* i2c_readNak */

void i2c_forceStop(void)
{
    xprintf("i2c timeout\n");

    /* let slave to release SDA */
    TWCR = 0;
    DDRD |=  (1<<PD0);
    DDRD &= ~(1<<PD1);
    _delay_us(30);
    if ((PIND & (1<<PD1)) == 0) {
        for (uint8_t i = 0; i < 9; i++) {
            PORTD &= ~(1<<PD0);
            _delay_us(SCL_DURATION);
            PORTD |= (1<<PD0);
            _delay_us(SCL_DURATION);
        }
    }
    DDRD &= ~(1<<PD0);

    /* send stop condition */
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}
