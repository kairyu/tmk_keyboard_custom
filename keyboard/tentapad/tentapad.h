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

#ifndef TENTAPAD_H
#define TENTAPAD_H

enum {
    KEY_K1 = 0,
    KEY_K2,
    KEY_TT,
    KEY_TP,
    KEY_CFG
};

enum {
    LED_KEY_1 = 0,
    LED_KEY_2,
    LED_KEY_SIDE,
    LED_BOARD_SIDE
};

void enter_config_mode(void);
void exit_config_mode(void);
void switch_layout(void);
void switch_backlight(void);
void set_layer_indicator(uint8_t layer);
void set_backlight_indicator(uint8_t backlight);

#endif

