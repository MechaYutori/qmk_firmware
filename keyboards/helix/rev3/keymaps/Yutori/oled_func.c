#include QMK_KEYBOARD_H
#include "oled_func.h"

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

void layout_display(void) {
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" QWERTY"), false);
            break;
        case _DVORAK:
            oled_write_P(PSTR(" DVORAK"), false);
            break;
        case _COLEMAK_DH:
            oled_write_P(PSTR(" COLEMAK-DH"), false);
            break;
        case _CANARY:
            oled_write_P(PSTR(" CANARY"), false);
            break;
        case _GAME:
            oled_write_P(PSTR(" GAME"), false);
            break;
        case _GAME_Space:
            oled_write_P(PSTR(" GAME_S"), false);
            break;
        case _GAME_Canary:
            oled_write_P(PSTR(" GAME_Canary"), false);
            break;
        default:
            break;
    }
}

// void display_os_logo(uint8_t count) {
//    static const char os_logo[][2][3] PROGMEM = {
//            {
//                {0x95, 0x96, 0},
//                {0xb5, 0xb6, 0}
//            },
//            {
//                {0x97, 0x98, 0},
//                {0xb7, 0xb8, 0}
//            }
//        };
//    if (count <= 1) {
//        if (is_mac_mode()) {
//            oled_write_P(os_logo[0][count], false);
//        } else {
//            oled_write_P(os_logo[1][count], false);
//        }
//    }
//}

void status_led_display(void) {
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR(" [N") : PSTR(" [ "), false);
    oled_write_P(led_state.caps_lock ? PSTR("C") : PSTR(" "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("S]") : PSTR(" ]"), false);
    oled_write_P(keymap_config.nkro ? PSTR(" NK") : PSTR("   "), false);
}

void current_layer_display(void) {
    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            oled_write_P(PSTR(" Numbers"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR(" Arrows"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR(" Adjust"), false);
            break;
        default:
            oled_write_P(PSTR(" Base"), false);
            break;
    }
}

void draw_host_akanechan(uint8_t count) {
    static const char AkaneStatus[][4][7] PROGMEM = {
        {
            {0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xD5, 0},
            {0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0},
            {0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0},
            {0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0}
        }, {
            {0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xD5, 0},
            {0xC6, 0xC7, 0x91, 0xC9, 0xCA, 0xCB, 0},
            {0x8B, 0xCC, 0xB1, 0x8E, 0x8F, 0x90, 0},
            {0xAB, 0xAC, 0xD1, 0xAE, 0xAF, 0xB0, 0}
        }, {
            {0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xD5, 0},
            {0xC6, 0xC7, 0x92, 0xC9, 0xCA, 0xCB, 0},
            {0x8B, 0xCD, 0xB2, 0x8E, 0x8F, 0x90, 0},
            {0xAB, 0xAC, 0xD2, 0xAE, 0xAF, 0xB0, 0}
        }, {
            {0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xD5, 0},
            {0xC6, 0xC7, 0x93, 0xC9, 0xCA, 0xCB, 0},
            {0x8B, 0xCE, 0xB3, 0x8E, 0x8F, 0x90, 0},
            {0xAB, 0xAC, 0xD3, 0xAE, 0xAF, 0xB0, 0}
        }};
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(AkaneStatus[3][count], false);
            break;
        case _RAISE:
            oled_write_P(AkaneStatus[1][count], false);
            break;
        case _LOWER:
            oled_write_P(AkaneStatus[0][count], false);
            break;
        case _ADJUST:
            oled_write_P(AkaneStatus[2][count], false);
            break;
        default:
            break;
    }
}

const char *u8_str_mod(uint8_t curr_num, char curr_pad) {
    static char buf[4] = {0};
    uint8_t digit = 0;
    uint8_t num = curr_num;
    while(num != 0 || digit == 0){
        num = num / 10;
        ++digit;
    }
    return get_numeric_str(buf, digit + 1, curr_num, curr_pad);
}


void render_rgbled_status(uint8_t count) {
#ifdef RGB_MATRIX_ENABLE
    if (rgb_matrix_is_enabled()) {
        switch (count) {
            case 0:
                oled_write_P(PSTR(" LED "), false);
                oled_write(get_u8_str(rgb_matrix_get_mode(), ' '), false);
                break;
            case 1:
                oled_write_P(PSTR(" "), false);
                oled_write(u8_str_mod(rgb_matrix_get_hue() / RGB_MATRIX_HUE_STEP, ' '), false);
                oled_write_P(PSTR(","), false);
                oled_write(u8_str_mod(rgb_matrix_get_sat() / RGB_MATRIX_SAT_STEP, ' '), false);
                oled_write_P(PSTR(","), false);
                oled_write(u8_str_mod(rgb_matrix_get_val() / RGB_MATRIX_VAL_STEP, ' '), false);
                break;
        }
    }
#endif
}

void draw_cliant_akanechan(uint8_t count) {
    static const char AkaneCliant[4][7] PROGMEM = {
        {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x00},
        {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0x00},
        {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0x00},
        {0x86, 0x87, 0x88, 0x89, 0x8A, 0xD5, 0x00}
        };
    oled_write_P(AkaneCliant[count], false);
}

void draw_twitch_logo(uint8_t count) {
    static const char AkaneCliant[3][6] PROGMEM = {
        {0xD8, 0xDA, 0x9D, 0x9E, 0x9F, 0x00},
        {0xD9, 0xDB, 0xBD, 0xBE, 0xBF, 0x00},
        {0xD5, 0xDC, 0xDD, 0xDE, 0xDF, 0x00}
        };
    oled_write_P(AkaneCliant[count], false);
}
