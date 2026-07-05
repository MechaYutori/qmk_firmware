/* Copyright 2020 yushakobo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
  How to Customize

  $ make helix/rev3_5rows:YOUR_KEYMAP:clean
  $ cp keyboards/helix/rev3_5rows/oled_display.c keyboards/helix/rev3_5rows/keymaps/YOUR_KEYMAP

  $ edit keyboards/helix/rev3_5rows/keymaps/YOUR_KEYMAP/oled_display.c
  $ make helix/rev3_5rows:YOUR_KEYMAP
  $ make helix/rev3_5rows:YOUR_KEYMAP:flash
*/

#include QMK_KEYBOARD_H
#include "oled_func.h"


// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _DVORAK,
  _COLEMAK_DH,
  _CANARY,
  _GAME,
  _GAME_Space,
  _GAME_Canary,
  _LOWER,
  _RAISE,
  _ADJUST
};

extern uint8_t oled_page;

#ifdef OLED_ENABLE

void render_host_status(uint8_t count) {
    switch (count) {
        case 0:
            draw_host_akanechan(count);
            //display_os_logo(count);
            layout_display();
            break;
        case 1:
            draw_host_akanechan(count);
            //display_os_logo(count);
            status_led_display();
            break;
        case 2:
            draw_host_akanechan(count);
            oled_write_P(PSTR(" Layer"), false);
            break;
        case 3:
            draw_host_akanechan(count);
            current_layer_display();
            break;
        default:
            break;
    }
}

void render_cliant_status(uint8_t count) {
    switch (count) {
        case 0:
            draw_cliant_akanechan(count);
            draw_twitch_logo(count);
            render_rgbled_status(count);
            break;
        case 1:
            draw_cliant_akanechan(count);
            draw_twitch_logo(count);
            render_rgbled_status(count);
            break;
        case 2:
            draw_cliant_akanechan(count);
            draw_twitch_logo(count);
            break;
        case 3:
            draw_cliant_akanechan(count);
            static const char UPARROW[] PROGMEM = {0x18, 0};
            oled_write_P(UPARROW, false);
            oled_write("/mechayutori", false);
            break;
        default:
            break;
    }
}

void render_hidden_mode(uint8_t count) {
    switch (count) {
        case 0:
            oled_write("Created by", false);
            break;
        case 1:
            oled_write("   Yosuke Doi", false);
            break;
        case 2:
            oled_write("     a.k.a", false);
            break;
        case 3:
            oled_write("        MechaYutori", false);
            break;
        default:
            break;
    }
}

void render_status_user(void) {
    // Host Keyboard Layer Status
    uint8_t count;
    for (count = 0; count <= 3; count++) {
        if (oled_page == 1) {
            render_host_status(count);
        } else if (oled_page == 2){
            render_cliant_status(count);
        } else if (oled_page == 3){
            render_hidden_mode(count);
        }
        oled_write_P(PSTR("\n"), false);
    }
}

bool oled_task_user(void) {
    if(oled_page != 0){
        render_status_user();
    }
    return false;
}
#endif
