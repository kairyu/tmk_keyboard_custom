/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>

// USB HID host
#include "Usb.h"
#include "usbhub.h"
#include "hid.h"
#include "hidboot.h"
#include "parser.h"

#include "keycode.h"
#include "util.h"
#include "print.h"
#include "debug.h"
#include "timer.h"
#include "matrix.h"
#include "led.h"
#include "action.h"
#include "host.h"

#define HID_MOUSE_ENABLE
#define HID_COMPOSITE_ENABLE
#define HID_KEYBOARD_COUNT 2
#define USB_HUB_COUNT 1

/* KEY CODE to Matrix
 *
 * HID keycode(1 byte):
 * Higher 5 bits indicates ROW and lower 3 bits COL.
 *
 *  7 6 5 4 3 2 1 0
 * +---------------+
 * |  ROW  |  COL  |
 * +---------------+
 *
 * Matrix space(16 * 16):
 *   r\c0123456789ABCDEF
 *   0 +----------------+
 *   : |                |
 *   : |                |
 *  16 +----------------+
 */
#define ROW_MASK 0xF0
#define COL_MASK 0x0F
#define CODE(row, col)  (((row) << 4) | (col))
#define ROW(code)       (((code) & ROW_MASK) >> 4)
#define COL(code)       ((code) & COL_MASK)
#define ROW_BITS(code)  (1 << COL(code))


// Integrated key state of all keyboards
static report_keyboard_t keyboard_report;
#ifdef HID_MOUSE_ENABLE
extern report_mouse_t mouse_report;
static uint8_t mouse_button;
#endif

static bool matrix_is_mod = false;

/*
 * USB Host Shield HID keyboards
 * This supports two cascaded hubs and four keyboards
 */
USB usb_host;

#ifdef USB_HUB_COUNT > 0
USBHub hub1(&usb_host);
#ifdef USB_HUB_COUNT > 1
USBHub hub2(&usb_host);
#endif
#endif

#ifdef HID_COMPOSITE_ENABLE
HIDBoot<HID_PROTOCOL_KEYBOARD | HID_PROTOCOL_MOUSE> composite(&usb_host);
#else
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd1(&usb_host);
#endif
#if HID_KEYBOARD_COUNT > 1
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd2(&usb_host);
#if HID_KEYBOARD_COUNT > 2
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd3(&usb_host);
#if HID_KEYBOARD_COUNT > 3
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd4(&usb_host);
#endif
#endif
#endif

KBDReportParser kbd_parser1;
#if HID_KEYBOARD_COUNT > 1
KBDReportParser kbd_parser2;
#if HID_KEYBOARD_COUNT > 1
KBDReportParser kbd_parser3;
#if HID_KEYBOARD_COUNT > 1
KBDReportParser kbd_parser4;
#endif
#endif
#endif

#ifdef HID_MOUSE_ENABLE
HIDBoot<HID_PROTOCOL_MOUSE>       mouse1(&usb_host);
MOUSEReportParser mouse_parser1;
#endif


uint8_t matrix_rows(void) { return MATRIX_ROWS; }
uint8_t matrix_cols(void) { return MATRIX_COLS; }
bool matrix_has_ghost(void) { return false; }
void matrix_init(void) {
    // USB Host Shield setup
    usb_host.Init();
#ifdef HID_COMPOSITE_ENABLE
    composite.SetReportParser(0, (HIDReportParser*)&kbd_parser1);
    composite.SetReportParser(1, (HIDReportParser*)&mouse_parser1);
#else
    kbd1.SetReportParser(0, (HIDReportParser*)&kbd_parser1);
#endif
#if HID_KEYBOARD_COUNT > 1
    kbd2.SetReportParser(0, (HIDReportParser*)&kbd_parser2);
#if HID_KEYBOARD_COUNT > 2
    kbd3.SetReportParser(0, (HIDReportParser*)&kbd_parser3);
#if HID_KEYBOARD_COUNT > 3
    kbd4.SetReportParser(0, (HIDReportParser*)&kbd_parser4);
#endif
#endif
#endif
#ifdef HID_MOUSE_ENABLE
    mouse1.SetReportParser(0, (HIDReportParser*)&mouse_parser1);
#endif
}

static void or_report(report_keyboard_t report) {
    // integrate reports into keyboard_report
    keyboard_report.mods |= report.mods;
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (IS_ANY(report.keys[i])) {
            for (uint8_t j = 0; j < KEYBOARD_REPORT_KEYS; j++) {
                if (! keyboard_report.keys[j]) {
                    keyboard_report.keys[j] = report.keys[i];
                    break;
                }
            }
        }
    }
}

uint8_t matrix_scan(void) {
    static uint16_t last_time_stamp1 = 0;
#if HID_KEYBOARD_COUNT > 1
    static uint16_t last_time_stamp2 = 0;
#if HID_KEYBOARD_COUNT > 2
    static uint16_t last_time_stamp3 = 0;
#if HID_KEYBOARD_COUNT > 3
    static uint16_t last_time_stamp4 = 0;
#endif
#endif
#endif

    // check report came from keyboards
    if (kbd_parser1.time_stamp != last_time_stamp1
#if HID_KEYBOARD_COUNT > 1
        || kbd_parser2.time_stamp != last_time_stamp2
#if HID_KEYBOARD_COUNT > 2
        || kbd_parser3.time_stamp != last_time_stamp3
#if HID_KEYBOARD_COUNT > 3
        || kbd_parser4.time_stamp != last_time_stamp4
#endif
#endif
#endif
    ) {

        last_time_stamp1 = kbd_parser1.time_stamp;
#if HID_KEYBOARD_COUNT > 1
        last_time_stamp2 = kbd_parser2.time_stamp;
#if HID_KEYBOARD_COUNT > 2
        last_time_stamp3 = kbd_parser3.time_stamp;
#if HID_KEYBOARD_COUNT > 3
        last_time_stamp4 = kbd_parser4.time_stamp;
#endif
#endif
#endif

        // clear and integrate all reports
        keyboard_report = {};
        or_report(kbd_parser1.report);
#if HID_KEYBOARD_COUNT > 1
        or_report(kbd_parser2.report);
#if HID_KEYBOARD_COUNT > 2
        or_report(kbd_parser3.report);
#if HID_KEYBOARD_COUNT > 3
        or_report(kbd_parser4.report);
#endif
#endif
#endif

        matrix_is_mod = true;

        dprintf("state:  %02X %02X", keyboard_report.mods, keyboard_report.reserved);
        for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            dprintf(" %02X", keyboard_report.keys[i]);
        }
        dprint("\r\n");
    } else {
        matrix_is_mod = false;
    }

#ifdef HID_MOUSE_ENABLE
    static uint16_t last_mouse_time_stamp = 0;
    if (last_mouse_time_stamp != mouse_parser1.time_stamp) {
        last_mouse_time_stamp = mouse_parser1.time_stamp;
        if (mouse_parser1.report.x || mouse_parser1.report.y) {
            int8_t x = mouse_report.x;
            int8_t y = mouse_report.y;
            mouse_report.x = mouse_parser1.report.x;
            mouse_report.y = mouse_parser1.report.y;
            host_mouse_send(&mouse_report);
            mouse_report.x = x;
            mouse_report.y = y;
        }
        if (mouse_parser1.report.v) {
            uint8_t code = 0;
            if (mouse_parser1.report.v == 1) code = KC_MS_WH_UP;
            else if (mouse_parser1.report.v == -1) code = KC_MS_WH_DOWN;
            if (code) {
                keyevent_t e;
                e.key.row = ROW(code);
                e.key.col = COL(code);
                e.pressed = 1;
                e.time = (timer_read() | 1); /* time should not be 0 */
                action_exec(e);
                e.pressed = 0;
                e.time = (timer_read() | 1); /* time should not be 0 */
                action_exec(e);
            }
        }
        if (mouse_button != mouse_parser1.report.buttons) {
            mouse_button = mouse_parser1.report.buttons;
            matrix_is_mod |= true;
        }
    }
#endif

    uint16_t timer;
    timer = timer_read();
    usb_host.Task();
    timer = timer_elapsed(timer);
    if (timer > 100) {
        dprintf("host.Task: %d\n", timer);
    }

    return 1;
}

bool matrix_is_modified(void) {
    return matrix_is_mod;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    uint8_t code = CODE(row, col);

    if (IS_MOD(code)) {
        if (keyboard_report.mods & ROW_BITS(code)) {
            return true;
        }
    }
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report.keys[i] == code) {
            return true;
        }
    }
    return false;
}

matrix_row_t matrix_get_row(uint8_t row) {
    uint16_t row_bits = 0;

    if (IS_MOD(CODE(row, 0)) && keyboard_report.mods) {
        row_bits |= keyboard_report.mods;
    }

#ifdef HID_MOUSE_ENABLE
    if (IS_MOUSEKEY(CODE(row, 0)) && mouse_button) {
        if (mouse_button & (1<<0)) row_bits |= (1<<(KC_MS_BTN1 - KC_MS_UP));
        if (mouse_button & (1<<1)) row_bits |= (1<<(KC_MS_BTN2 - KC_MS_UP));
        if (mouse_button & (1<<2)) row_bits |= (1<<(KC_MS_BTN3 - KC_MS_UP));
        if (mouse_button & (1<<3)) row_bits |= (1<<(KC_MS_BTN4 - KC_MS_UP));
        if (mouse_button & (1<<4)) row_bits |= (1<<(KC_MS_BTN5 - KC_MS_UP));
    }
#endif

    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (IS_ANY(keyboard_report.keys[i])) {
            if (row == ROW(keyboard_report.keys[i])) {
                row_bits |= ROW_BITS(keyboard_report.keys[i]);
            }
        }
    }
    return row_bits;
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;

    count += bitpop(keyboard_report.mods);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (IS_ANY(keyboard_report.keys[i])) {
            count++;
        }
    }
    return count;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        xprintf("%02d: ", row);
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

void led_set(uint8_t usb_led)
{
#ifdef HID_COMPOSITE_ENABLE
    composite.SetReport(0, 0, 2, 0, 1, &usb_led);
#else
    kbd1.SetReport(0, 0, 2, 0, 1, &usb_led);
#endif
#if HID_KEYBOARD_COUNT > 1
    kbd2.SetReport(0, 0, 2, 0, 1, &usb_led);
#if HID_KEYBOARD_COUNT > 2
    kbd3.SetReport(0, 0, 2, 0, 1, &usb_led);
#if HID_KEYBOARD_COUNT > 3
    kbd4.SetReport(0, 0, 2, 0, 1, &usb_led);
#endif
#endif
#endif
}

extern bool kbd_init;

#ifdef __cplusplus
extern "C" {
void kbd_led_set(uint8_t usb_led)
{
    if (kbd_init) {
        dprintf("USB LED: %d\n", usb_led);
        led_set(usb_led);
    }
}
}
#endif
