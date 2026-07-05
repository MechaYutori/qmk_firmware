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
#include QMK_KEYBOARD_H
#include "tapdance.c"

uint8_t oled_page = 0;

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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  _OLED = SAFE_RANGE,
  RAISE_LT,
  LOWER_LT,
  EK_MODE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJ_L MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Lower|   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |  ESC |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  | Alt  |Delete|Raise |Space |Enter |Lower | Bksp | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_5row( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
      LOWER,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ESC,  KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, KC_DEL,  RAISE_LT,KC_SPC,  KC_ENT,  LOWER_LT,KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
    ),
  /* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  |   /  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Lower|   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |   -  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |  ESC |   -  |   B  |   M  |   W  |   V  |   Z  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  | Alt  |Delete|Raise |Space |Enter |Lower | Bksp | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT_5row( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
      LOWER,   KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_ESC,  KC_ESC,  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, KC_DEL,  RAISE_LT,KC_SPC,  KC_ENT,  LOWER_LT,KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
    ),
  /* Colemak_DH
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   B  |             |   J  |   L  |   U  |   Y  |   ;  |   -  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Lower|   A  |   R  |   S  |   T  |   G  |             |   M  |   N  |   E  |   I  |   O  |   '  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   D  |   V  |  ESC |  ESC |   K  |   H  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  | Alt  |Delete|Raise |Space |Enter |Lower | Bksp | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_COLEMAK_DH] = LAYOUT_5row( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINS, \
      LOWER,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_ESC,  KC_ESC,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, KC_DEL,  RAISE_LT,KC_SPC,  KC_ENT,  LOWER_LT,KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
    ),
      /* CANARY
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   W  |   L  |   Y  |   P  |   B  |             |   Z  |   F  |   O  |   U  |   ;  |   -  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Lower|   C  |   R  |   S  |   T  |   G  |             |   M  |   N  |   E  |   I  |   A  |   '  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Q  |   J  |   V  |   D  |   K  |  ESC |  ESC |   X  |   H  |   /  |   ,  |   .  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  | Alt  |Delete|Raise |Space |Enter |Lower | Bksp | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_CANARY] = LAYOUT_5row( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                      KC_Z,    KC_F,    KC_O,    KC_U,    KC_SCLN, KC_MINS, \
      LOWER,   KC_C,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_A,    KC_QUOT, \
      KC_LSFT, KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,    KC_ESC,  KC_ESC,  KC_X,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, KC_DEL,  RAISE_LT,KC_SPC,  KC_ENT,  LOWER_LT,KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
    ),
  /* Game
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   /  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |Adjust|   N  |   M  |   ,  |   .  |  Up  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Esc  | LAlt | RAlt |   =  |   [  |Space |Enter |   ]  | Bksp |RCtrl | Left | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_GAME] = LAYOUT_5row( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
      KC_SLSH, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    ADJ_L,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT, \
      KC_LCTL, KC_ESC,  KC_LALT, KC_RALT, KC_EQL,  KC_LBRC, KC_SPC,  KC_ENT,  KC_RBRC, KC_BSPC, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT \
    ),
  /* Game Both thumb has space
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   /  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |Adjust|   N  |   M  |   ,  |   .  |  Up  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Esc  | LAlt | RAlt |   =  |   [  |Space | Space|   ]  | Bksp |Enter | Left | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_GAME_Space] = LAYOUT_5row( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
      KC_SLSH, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    ADJ_L,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT, \
      KC_LCTL, KC_ESC,  KC_LALT, KC_RALT, KC_EQL,  KC_LBRC, KC_SPC,  KC_SPC,  KC_RBRC, KC_BSPC, KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT \
    ),
      /* Game with Canary layout
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   W  |   L  |   Y  |   P  |   B  |             |   Z  |   F  |   O  |   U  |   :  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   /  |   C  |   R  |   S  |   T  |   G  |             |   M  |   N  |   E  |   I  |   A  |  "   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Q  |   J  |   V  |   D  |   K  |   X  |Adjust|   X  |   H  |   ,  |   .  |  Up  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Esc  | LAlt | RAlt |   =  |   [  |Space | Space|   ]  | Bksp |Enter | Left | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_GAME_Canary] = LAYOUT_5row( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                      KC_Z,    KC_F,    KC_O,    KC_U,    KC_SCLN, KC_MINS, \
      KC_SLSH, KC_C,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_A,    KC_QUOT, \
      KC_LSFT, KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,    KC_X,    ADJ_L,   KC_X,    KC_H,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT, \
      KC_LCTL, KC_ESC,  KC_LALT, KC_RALT, KC_EQL,  KC_LBRC, KC_SPC,  KC_SPC,  KC_RBRC, KC_BSPC, KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT \
    ),
  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   !  |   @  |   #  |   $  |   %  |             |PG UP | Home |  Up  | End  | Pscr |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   ~  |   ^  |   &  |   *  |   _  |   =  |             |PG DN | Left | Down |Right |Rshift|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |S(Del)|      |A(Ent)|      |      |Delete|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |Adjust|      |      |      |      | Pause| xxxx | xxxx |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_5row( \
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PSCR, KC_F12, \
      KC_TILD, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_EQL,                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_RSFT, _______, \
      _______, _______, _______, _______, _______, _______, _______,S(KC_DEL),_______,A(KC_ENT),_______, _______, KC_DEL,  _______, \
      _______, _______, _______, _______, _______, ADJ_L,   _______, _______, _______, _______, KC_PAUS, XXXXXXX, XXXXXXX, _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |Alt+F4|      |      |      |DMRec2|DMRec1|             |DM_STP|      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |   [  |  ]   |      |      |             |      |   7  |   8  |   9  |   *  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |  ({[ | )}]  |      |      |             |      |   4  |   5  |   6  |   +  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |   1  |   2  |   3  |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |A(Ent)|Adjust|   0  |      |   .  | xxxx | xxxx |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_5row( \
      A(KC_F4),_______, _______, _______, DM_REC2, DM_REC1,                   DM_RSTP, _______, _______, _______, _______, _______, \
      _______, _______, KC_LBRC, KC_RBRC, _______, _______,                   _______, KC_7,    KC_8,    KC_9,    KC_PAST, _______, \
      _______, _______, TD(TD_LB),TD(TD_RB),_______,_______,                  _______, KC_4,    KC_5,    KC_6,    KC_PPLS, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______, \
      DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, A(KC_ENT),ADJ_L,  KC_0,    XXXXXXX, KC_DOT,  XXXXXXX, XXXXXXX \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Caps |      |      |Game_S|Game_S| Game |             |Qwerty|Dvorak|Colema|      |      | NKRO |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Nlock|      |      |      |      |      |             |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Slock|      |      |      |      |      |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Insert|      |      |      |      |      | OLED | RESET|      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |RGB ON| MODE | HUE- | HUE+ |      |      |      |      |      |      | SAT- | SAT+ | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT_5row( \
      KC_CAPS, _______, _______, DF(6), DF(5),   DF(4),                       DF(0),   DF(1),   DF(2),   DF(3),   _______, NK_TOGG, \
      KC_NUM,  _______, _______, _______, _______, _______,                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11, \
      KC_SCRL, _______, _______, _______, _______, _______,                   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
      KC_INS,  RM_PREV, _______, _______, _______, _______, _OLED,    QK_BOOT,_______, _______, _______, _______, _______, _______, \
      RM_TOGG, RM_NEXT, RM_HUEU, RM_HUED, _______, _______, EK_MODE,  _______,_______, _______, RM_SATD, RM_SATU, RM_VALD, RM_VALU \
      )
};

static bool     LT_bool = false;
static uint16_t LT_time = 0;
static bool oled_trigger = false;
static uint16_t oled_timer = 0;
static bool eisu_kana = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  int current_default_layer;
  switch (keycode) {
    case RAISE_LT:
      if (record->event.pressed) {
        layer_on(_RAISE);
        LT_bool = true;
        LT_time = record->event.time;
      } else {
        layer_off(_RAISE);
        if (LT_bool && (TIMER_DIFF_16(record->event.time, LT_time) < TAPPING_TERM)) {
          if(eisu_kana){
            register_code(KC_LNG2);
            unregister_code(KC_LNG2);
          } else {
            register_code(KC_LALT);
            register_code(KC_GRV);
            unregister_code(KC_GRV);
            unregister_code(KC_LALT);
          }
        LT_bool = false;
        }
      }
      return false;
      break;
    case LOWER_LT:
      if (record->event.pressed) {
        layer_on(_LOWER);
        LT_bool = true;
        LT_time = record->event.time;
      } else {
        layer_off(_LOWER);
        if (LT_bool && (TIMER_DIFF_16(record->event.time, LT_time) < TAPPING_TERM && eisu_kana)) {
          register_code(KC_LNG1);
          unregister_code(KC_LNG1);
        }
        LT_bool = false;
      }
      return false;
      break;
    case EK_MODE:
      if (record->event.pressed) {
        eisu_kana = !eisu_kana;
      } else {
        
      }
      return false;
      break;
    case DF(0):
      current_default_layer = _QWERTY;
      eeconfig_update_default_layer(1UL << current_default_layer);
      default_layer_set(1UL << current_default_layer);
      if(oled_page == 0 || oled_trigger){
        oled_trigger = true;
        oled_timer = timer_read();
      }
      break;
    case DF(1):
      current_default_layer = _DVORAK;
      eeconfig_update_default_layer(1UL << current_default_layer);
      default_layer_set(1UL << current_default_layer);
      if(oled_page == 0 || oled_trigger){
        oled_trigger = true;
        oled_timer = timer_read();
      }
      break;
    case DF(2):
      current_default_layer = _COLEMAK_DH;
      eeconfig_update_default_layer(1UL << current_default_layer);
      default_layer_set(1UL << current_default_layer);
      if(oled_page == 0 || oled_trigger){
        oled_trigger = true;
        oled_timer = timer_read();
      }
      break;
    case DF(3):
      current_default_layer = _CANARY;
      eeconfig_update_default_layer(1UL << current_default_layer);
      default_layer_set(1UL << current_default_layer);
      if(oled_page == 0 || oled_trigger){
        oled_trigger = true;
        oled_timer = timer_read();
      }
      break;
    case DF(4):
      current_default_layer = _GAME;
      eeconfig_update_default_layer(1UL << current_default_layer);
      default_layer_set(1UL << current_default_layer);
      if(oled_page == 0 || oled_trigger){
        oled_trigger = true;
        oled_timer = timer_read();
      }
      break;
    case DF(5):
      current_default_layer = _GAME_Space;
      eeconfig_update_default_layer(1UL << current_default_layer);
      default_layer_set(1UL << current_default_layer);
      if(oled_page == 0 || oled_trigger){
        oled_trigger = true;
        oled_timer = timer_read();
      }
      break;
    case DF(6):
      current_default_layer = _GAME_Canary;
      eeconfig_update_default_layer(1UL << current_default_layer);
      default_layer_set(1UL << current_default_layer);
      if(oled_page == 0 || oled_trigger){
        oled_trigger = true;
        oled_timer = timer_read();
      }
      break;
    case _OLED:
      if (record->event.pressed && is_keyboard_master()){
        if(oled_page < 2){
          oled_page += 1;
        } else {
          oled_page = 0;
        }
      }
      break;
    default:
      if (record->event.pressed) {
        LT_bool = false;
      }
      break;
  }
  return true;
}

void housekeeping_task_user(void) {
  if(oled_trigger == true){
    if((timer_elapsed (oled_timer) > 1500)){
      oled_page = 0;
      oled_timer = 0;
      oled_trigger = false;
    }else if(oled_page == 2){
      oled_timer = 0;
      oled_trigger = false;
    }else{
    oled_page = 1;
    }
  }
}