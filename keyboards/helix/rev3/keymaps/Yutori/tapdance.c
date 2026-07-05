// Tap Dance declarations
enum {
    TD_LB,
    TD_RB
};

extern uint8_t oled_page;
bool secret_page = false;

void td_lbb(tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      register_code16(KC_LPRN);
      secret_page = false;
      break;
    case 2:
      register_code16(KC_LCBR);
      secret_page = false;
      break;
    case 3:
      register_code(KC_LBRC);
      secret_page = false;
      break;
    case 5:
      secret_page = true;
      break;
    default:
      secret_page = false;
      break;
  }
}

void td_lbb_reset(tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      unregister_code16(KC_LPRN);
      break;
    case 2:
      unregister_code16(KC_LCBR);
      break;
    case 3:
      unregister_code(KC_LBRC);
      break;
  }
}

void td_rbb(tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      register_code16(KC_RPRN);
      secret_page = false;
      break;
    case 2:
      register_code16(KC_RCBR);
      secret_page = false;
      break;
    case 3:
      register_code(KC_RBRC);
      secret_page = false;
      break;
    case 10:
      if(secret_page){
        oled_page = 3;
      }
      secret_page = false;
      break;
    default:
      secret_page = false;
      break;
  }
}

void td_rbb_reset(tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      unregister_code16(KC_RPRN);
      break;
    case 2:
      unregister_code16(KC_RCBR);
      break;
    case 3:
      unregister_code(KC_RBRC);
      break;
  }
}


// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lbb, td_lbb_reset),
    [TD_RB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rbb, td_rbb_reset)
};