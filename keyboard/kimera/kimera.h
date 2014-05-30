/*
Copyright 2014 Kai Ryu <kai1103@gmail.com>

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

#ifndef KIMERA_H
#define KIMERA_H

#include <stdint.h>
#include <avr/pgmspace.h>
#include "matrix.h"

/*
              Pro Micro
           ,----------------.
      TX --| TX0(PD3)   RAW |--
      RX --| RX1(PD2)   GND |--
         --| GND      RESET |-- RST
         --| GND        VCC |--
     SDA --| 2(PD1) (PF4)A3 |-- (Z4)
     SCL --| 3(PD0) (PF5)A2 |-- (Z1)
   (RCK) --| 4(PD4) (PF6)A1 |-- (Z2)
    LED1 --| 5(PC6) (PF7)A0 |-- (Z3)
    LED2 --| 6(PD7) (PB1)15 |-- SCK
   (SJ1) --| 7(PE6) (PB3)14 |-- MISO
   (SJ2) --| 8(PB4) (PB2)16 |-- MOSI
      BL --| 9(PB5) (PB6)10 |-- LED3
          `----------------'
*/

#define LED1_PORT   PORTC
#define LED1_PIN    PINC
#define LED1_DDR    DDRC
#define LED1_BIT    PC6

#define LED2_PORT   PORTD
#define LED2_PIN    PIND
#define LED2_DDR    DDRD
#define LED2_BIT    PD7

#define LED3_PORT   PORTB
#define LED3_PIN    PINB
#define LED3_DDR    DDRB
#define LED3_BIT    PB6

#define BL_PORT     PORTB
#define BL_PIN      PINB
#define BL_DDR      DDRB
#define BL_BIT      PB5
#define BL_OCR      OCR1A

#define RCK_PORT    PORTD
#define RCK_PIN     PIND
#define RCK_DDR     DDRD
#define RCK_BIT     PD4

#define SCK_PORT    PORTB
#define SCK_PIN     PINB
#define SCK_DDR     DDRB
#define SCK_BIT     PB1

#define MOSI_PORT   PORTB
#define MOSI_PIN    PINB
#define MOSI_DDR    DDRB
#define MOSI_BIT    PB2

#define MISO_PORT   PORTB
#define MISO_PIN    PINB
#define MISO_DDR    DDRB
#define MISO_BIT    PB3

#define ZX_PORT     PORTF
#define ZX_PIN      PINF
#define ZX_DDR      DDRF
#ifdef KIMERA_C
const uint8_t PROGMEM zx_bit[] = {
    PF5, PF6, PF7, PF4
};
#endif

/*
        Shift Register    Multiplexer
         ,----------.    ,------------.
  MOSI --| SER    0 |----| INH  X0~X7 |===============.
   SCK --|>SCK    1 |----| A          |                |
   RCK --|>RCK    2 |----| B          |  ,-------------+-------------.
         |        3 |----| C          |  |   |   |   |   |   |   |   |
         |          |    `------------'  P26 P27 P28 P25 P29 P32 P30 P31
         |          |    ,------------.
         |        4 |----| A    X0~X7 |===============.
         |        5 |----| B          |                |
         |        6 |----| C          |  ,-------------+-------------.
         |        7 |----| INH        |  |   |   |   |   |   |   |   |
         |          |    `------------'  P2  P3  P4  P1  P5  P8  P6  P7
         |          |    ,------------.
         |        8 |----| INH  X0~X7 |===============.
         |        9 |----| A          |                |
         |       10 |----| B          |  ,-------------+-------------.
         |       11 |----| C          |  |   |   |   |   |   |   |   |
         |          |    `------------'  P10 P11 P12 P9 P13  P16 P14 P15
         |          |    ,------------.
         |       12 |----| A    X0~X7 |===============.
         |       13 |----| B          |                |
         |       14 |----| C          |  ,-------------+-------------.
         |       15 |----| INH        |  |   |   |   |   |   |   |   |
         `----------'    `------------'  P18 P19 P20 P17 P21 P24 P22 P23
*/

#define MUX_COUNT 4
#define MUX_PORTS 8
#define PX_TO_MUX(x) (x>>3) // (x / MUX_PORTS)

enum {
    MUX4_INH = 0,
    MUX4_A,
    MUX4_B,
    MUX4_C,
    MUX1_A,
    MUX1_B,
    MUX1_C,
    MUX1_INH,
    MUX2_INH,
    MUX2_A,
    MUX2_B,
    MUX2_C,
    MUX3_A,
    MUX3_B,
    MUX3_C,
    MUX3_INH
};

#ifdef KIMERA_C
const uint16_t PROGMEM px_to_shift_out[] = {
    3<<MUX1_A, 0<<MUX1_A, 1<<MUX1_A, 2<<MUX1_A, 4<<MUX1_A, 6<<MUX1_A, 7<<MUX1_A, 5<<MUX1_A,
    3<<MUX2_A, 0<<MUX2_A, 1<<MUX2_A, 2<<MUX2_A, 4<<MUX2_A, 6<<MUX2_A, 7<<MUX2_A, 5<<MUX2_A,
    3<<MUX3_A, 0<<MUX3_A, 1<<MUX3_A, 2<<MUX3_A, 4<<MUX3_A, 6<<MUX3_A, 7<<MUX3_A, 5<<MUX3_A,
    3<<MUX4_A, 0<<MUX4_A, 1<<MUX4_A, 2<<MUX4_A, 4<<MUX4_A, 6<<MUX4_A, 7<<MUX4_A, 5<<MUX4_A
};

const uint16_t PROGMEM mux_inh_to_shift_out[] = {
    1<<MUX1_INH, 1<<MUX2_INH, 1<<MUX3_INH, 1<<MUX4_INH
};
#endif

/* Matrix Mapping in EEPROM */

#define EECONFIG_MUX_MAPPING        (uint8_t *)7
#define EECONFIG_ROW_COL_MAPPING    (uint8_t *)8
#define MATRIX_MAPPING_SIZE         MUX_COUNT * MUX_PORTS

typedef struct {
    uint8_t mux_mapping;
    uint8_t row_col_mapping;
} matrix_mapping_t;

#define MUX_INPUT           0
#define MUX_OUTPUT          1
#define MUX_FOR_COL         MUX_INPUT
#define MUX_FOR_ROW         MUX_OUTPUT
#define UNCONFIGURED        0xFF

/* Functions */

void kimera_init(void);
uint8_t read_matrix_mapping(void);
void write_matrix_mapping(void);
void shift_out_word(uint16_t word);
matrix_row_t read_cols(void);
void init_cols(void);
void unselect_rows(void);
void select_row(uint8_t row);

#endif
