#include "protok.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* base layer PC */
    LAYOUT(
           KC_ESC , XXXXXXX       , KC_F13  , KC_F14 , KC_F15  , KC_F16  , KC_F17  , KC_F18 , KC_F19        , KC_F20  , KC_F21  , KC_F22  , KC_PSCR , KC_CLCK , KC_PAUS , KC_INS  ,
           KC_WBAK, KC_ESC        , KC_F1   , KC_F2  , KC_F3   , KC_F4   , KC_F5   , KC_F6  , KC_F7         , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_HOME , KC_PGUP ,
           KC_WFWD, KC_GRV        , KC_1    , KC_2   , KC_3    , KC_4    , KC_5    , KC_6   , KC_7          , KC_8    , KC_9    , KC_0    , KC_MINS , KC_EQL  , KC_END  , KC_PGDN ,
           XXXXXXX, KC_TAB        ,           KC_Q   , KC_W    , KC_E    , KC_R    , KC_T   , KC_Y          , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC , KC_RBRC , KC_DEL  ,
           XXXXXXX, LCTL_T(KC_ESC),           KC_A   , KC_S    , KC_D    , KC_F    , KC_G   , KC_H          , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_BSLS , MO(1)   ,
           XXXXXXX,                 KC_LSPO , KC_Z   , KC_X    , KC_C    , KC_V    , KC_B   , KC_N          , KC_M    , KC_COMM , KC_DOT  , KC_SLSH ,           KC_RSPC , KC_UP   ,
           MO(2)  , XXXXXXX       ,          KC_HYPR , KC_LGUI , KC_LALT , KC_BSPC , RSFT_T(KC_SPC) , RSFT_T(KC_SPC), KC_ENT, KC_RALT , KC_RGUI , KC_LEFT , KC_RGHT , KC_DOWN),

    /* additional func */
    LAYOUT(
           KC_PWR , KC_SLEP, KC_WAKE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_MUTE, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_VOLU, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_VOLD,          KC_LEFT, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, _______,
           _______, _______,          _______, _______, _______, _______, KC_SPC , KC_RSFT, _______,          KC_1   , _______, _______, _______, _______),

    /* command jump layer */
    LAYOUT(
          TERM_OFF, TERM_ON, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG  , EEP_RST, RESET  , OSL(3) ,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL1, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL0, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_2   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* bootmagic key layer */
    LAYOUT(
           LAG_SWP, LAG_NRM, RAG_SWP, RAG_NRM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
           AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           NK_TOGG, NK_ON  , NK_OFF , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, KC_CALC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_3   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    /* keyevent_t event = record->event; */

    switch (id) {

    }
    return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void led_set_user(uint8_t usb_led) {

    /* if (usb_led & (1 << USB_LED_NUM_LOCK)) { */
    /* } else { */
    /* } */

    /* if (usb_led & (1 << USB_LED_CAPS_LOCK)) { */
    /* } else { */
    /* } */

    /* if (usb_led & (1 << USB_LED_SCROLL_LOCK)) { */
    /* } else { */
    /* } */

    /* if (usb_led & (1 << USB_LED_COMPOSE)) { */
    /* } else { */
    /* } */

    /* if (usb_led & (1 << USB_LED_KANA)) { */
    /* } else { */
    /* } */

}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_SPC):
            return TAPPING_TERM + 100;
        /* case LT(1, KC_GRV): */
        /*     return 130; */
        default:
            return TAPPING_TERM;
    }
}

