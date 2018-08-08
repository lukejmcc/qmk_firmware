#include QMK_KEYBOARD_H

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define ____ KC_TRNS
#define XXXX KC_NO

// Layer definition
#define L0 0
#define L1 1
#define L2 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        [L0] = LAYOUT(
		F(0), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRAVE, KC_BSLS,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
		KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
                KC_LSFT, XXXX, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, XXXX,
                KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, LT(1, KC_ESC), KC_SPC, KC_RCTL, KC_RALT, XXXX, KC_RGUI, KC_RCTL),

        [L1] = LAYOUT(
                KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, ____, ____,
                ____, KC_VOLD, KC_MUTE, KC_VOLU, ____, ____, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, ____, ____, ____, KC_DEL,
                ____, KC_MPRV, KC_MPLY, KC_MNXT, ____, ____, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_MS_BTN1, KC_MS_BTN2, ____,
                ____, XXXX, ____, ____, ____, ____, KC_INSERT, KC_HOME, KC_PGDN, KC_PGUP, KC_END, ____, ____, XXXX,
                LT(2, KC_LCTL), ____, ____, ____, ____, ____, ____, ____, KC_HOME, KC_PGDN, KC_END),


        [L2] = LAYOUT(
                ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
                ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
                ____, ____, ____, ____, RESET, ____, ____, ____, ____, ____, ____, ____, ____,
                ____, XXXX, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, XXXX,
                ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____),
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRB |= (1 << 2); PORTB &= ~(1 << 2);
    } else {
        DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
    }
}
