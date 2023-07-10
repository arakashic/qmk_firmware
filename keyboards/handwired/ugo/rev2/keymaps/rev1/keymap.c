#include "protok.h"

bool d2r_auto_enabled = false;

enum custom_keycode {
    FOO = SAFE_RANGE,
    KC_D2R_AUTO
};

enum layer_names {
    L_DEF = 0,
    L_GAME,
    L_GAMEPAD,
    L_FUN,
    L_SYM,
    L_NAV,
    L_SET,
    L_CMD
};

// Tap Dance declarations
enum {
    BSPC_TO_SYM,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* base layer PC */
    LAYOUT_gen1(
           KC_ESC , XXXXXXX       , KC_F13  , KC_F14 , KC_F15  , KC_F16  , KC_F17  , KC_F18 , KC_F19        , KC_F20  , KC_F21  , KC_F22  , KC_PSCR , KC_CLCK , KC_PAUS , KC_INS  ,
           KC_WBAK, KC_ESC        , KC_F1   , KC_F2  , KC_F3   , KC_F4   , KC_F5   , KC_F6  , KC_F7         , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_HOME , KC_PGUP ,
           KC_DEL , KC_GRV        , KC_1    , KC_2   , KC_3    , KC_4    , KC_5    , KC_6   , KC_7          , KC_8    , KC_9    , KC_0    , KC_MINS , KC_EQL  , KC_END  , KC_PGDN ,
           KC_HOME, LT(L_NAV, KC_TAB) ,       KC_Q   , KC_W    , KC_E    , KC_R    , KC_T   , KC_Y          , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC , KC_RBRC , KC_DEL  ,
           KC_END , LCTL_T(KC_ESC),           KC_A   , KC_S    , KC_D    , KC_F    , KC_G   , KC_H          , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_BSLS , MO(L_FUN),
           XXXXXXX ,                KC_LSPO , KC_Z   , KC_X    , KC_C    , KC_V    , KC_B   , KC_N          , KC_M    , KC_COMM , KC_DOT  , KC_SLSH ,           KC_RSPC , KC_UP   ,
           MO(L_CMD), XXXXXXX       ,         KC_HYPR , KC_LGUI , KC_LALT , LT(L_SYM, KC_BSPC) , RSFT_T(KC_SPC) , RSFT_T(KC_SPC), KC_ENT, KC_RALT , KC_RGUI , KC_LEFT , KC_DOWN , KC_RGHT),

    /* Game layer */
    LAYOUT_gen1(
           KC_ESC , XXXXXXX       , KC_F13  , KC_F14 , KC_F15  , KC_F16  , KC_F17  , KC_F18 , KC_F19        , KC_F20  , KC_F21  , KC_F22  , KC_PSCR , KC_CLCK , KC_PAUS , KC_INS  ,
           KC_WBAK, KC_ESC        , KC_F1   , KC_F2  , KC_F3   , KC_F4   , KC_F5   , KC_F6  , KC_F7         , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_HOME , KC_PGUP ,
           KC_DEL , KC_GRV        , KC_1    , KC_2   , KC_3    , KC_4    , KC_5    , KC_6   , KC_7          , KC_8    , KC_9    , KC_0    , KC_MINS , KC_EQL  , KC_END  , KC_PGDN ,
           KC_HOME, KC_TAB ,                  KC_Q   , KC_W    , KC_E    , KC_R    , KC_T   , KC_Y          , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC , KC_RBRC , KC_BSPC  ,
           KC_END , LCTL_T(KC_ESC),           KC_A   , KC_S    , KC_D    , KC_F    , KC_G   , KC_H          , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_BSLS , MO(L_FUN),
           XXXXXXX ,                KC_LSFT , KC_Z   , KC_X    , KC_C    , KC_V    , KC_B   , KC_N          , KC_M    , KC_COMM , KC_DOT  , KC_SLSH ,           KC_RSFT , KC_UP   ,
           MO(L_CMD), XXXXXXX       ,         KC_HYPR , KC_LGUI , KC_LALT , KC_SPC , RSFT_T(KC_SPC) , RSFT_T(KC_SPC), KC_ENT, KC_RALT , KC_RGUI , KC_LEFT , KC_DOWN , KC_RGHT),

    /* Game Pad layer */
    LAYOUT_gen1(
           KC_ESC , KC_F24        , KC_F13  , KC_F14 , KC_F15  , KC_F16  , KC_F17  , KC_F18 , KC_F19        , KC_F20  , KC_F21  , KC_F22  , KC_PSCR , KC_CLCK , KC_PAUS , KC_INS  ,
           KC_F23 , KC_F17        , KC_F1   , KC_F2  , KC_F3   , KC_F4   , KC_F5   , KC_F6  , KC_F7         , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_HOME , KC_PGUP ,
           KC_F21 , KC_GRV        , KC_1    , KC_2   , KC_3    , KC_4    , KC_5    , KC_6   , KC_7          , KC_8    , KC_9    , KC_0    , KC_MINS , KC_EQL  , KC_END  , KC_PGDN ,
           KC_F20 , KC_TAB ,                  KC_Q   , KC_W    , KC_E    , KC_R    , KC_T   , KC_Y          , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC , KC_RBRC , KC_BSPC  ,
           KC_F19 , KC_LCTL,           KC_A   , KC_S    , KC_D    , KC_F    , KC_G   , KC_H          , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_BSLS , MO(L_FUN),
           KC_F18 ,                KC_LSFT , KC_Z   , KC_X    , KC_C    , KC_V    , KC_B   , KC_N          , KC_M    , KC_COMM , KC_DOT  , KC_SLSH ,           KC_RSFT , KC_UP   ,
           MO(L_CMD), KC_D2R_AUTO ,         KC_HYPR , KC_LGUI , KC_LALT , KC_SPC , RSFT_T(KC_SPC) , RSFT_T(KC_SPC), KC_ENT, KC_RALT , KC_RGUI , KC_LEFT , KC_DOWN , KC_RGHT),

    /* additional func */
    LAYOUT_gen1(
           KC_PWR , KC_SLEP, KC_WAKE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_MUTE, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_VOLU, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_VOLD,          KC_LEFT, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, _______,
           _______, _______,          _______, _______, _______, _______, KC_SPC , KC_RSFT, _______,          KC_1   , _______, _______, _______, _______),

    /* symbol layer */
    LAYOUT_gen1(
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_EXLM, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_CIRC, XXXXXXX, KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          KC_AT  , KC_DLR , KC_PERC, KC_ASTR, KC_AMPR, KC_HASH, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* NAV layer */
    LAYOUT_gen1(
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP  , KC_END , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_5   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* bootmagic key layer */
    LAYOUT_gen1(
           LAG_SWP, LAG_NRM, RAG_SWP, RAG_NRM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
           AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           NK_TOGG, NK_ON  , NK_OFF , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, KC_CALC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_3   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* command jump layer */
    LAYOUT_gen1(
          TERM_OFF, TERM_ON, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG  , EEP_RST, RESET  , OSL(L_SET),
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL2, XXXXXXX, TO(L_DEF), TO(L_GAME), TO(L_GAMEPAD), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL1, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL0, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_2   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

};
// clang-format on

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

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=false;
    debug_matrix=false;
    debug_keyboard=false;
    debug_mouse=false;

    d2r_auto_enabled = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_D2R_AUTO && record->event.pressed) {
        if (d2r_auto_enabled) {
            d2r_auto_enabled = false;
        } else {
            d2r_auto_enabled = true;
        }
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (d2r_auto_enabled) {
        switch (keycode) {
            case KC_A:
            case KC_S:
            case KC_D:
            case KC_F:
            case KC_Q:
            case KC_W:
            case KC_E:
            case KC_R:
            case KC_C:
            case KC_V:
                if (!record->event.pressed) {
                    tap_code(KC_MS_BTN2);
                }
            default:
                break;
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case L_DEF:
        case L_GAME:
        case L_GAMEPAD:
        case L_FUN:
        case L_SYM:
        case L_NAV:
        case L_SET:
        case L_CMD:
        default: //  for any other layers, or the default layer
            d2r_auto_enabled = false;
    }
  return state;
}

void led_set_user(uint8_t usb_led) {
}

#ifdef OLED_ENABLE

void oled_task_user(void) {
    // Line 0:
    oled_write_P(PSTR("> "), false);
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case L_DEF:
            oled_write_P(PSTR("Default"), false);
            break;
        case L_GAME:
            oled_write_P(PSTR("Game"), false);
            break;
        case L_GAMEPAD:
            oled_write_P(PSTR("GamePad"), false);
            break;
        case L_FUN:
            oled_write_P(PSTR("FN"), false);
            break;
        case L_SYM:
            oled_write_P(PSTR("Symbol"), false);
            break;
        case L_NAV:
            oled_write_P(PSTR("Nav"), false);
            break;
        case L_SET:
            oled_write_P(PSTR("Setup"), false);
            break;
        case L_CMD:
            oled_write_P(PSTR("Command"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_ln_P(PSTR("\n"), false);

    // Line 1:
    oled_write_P(PSTR("> "), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    oled_write_P(PSTR("\n"), false);

    // Line 2:
    oled_write_P(PSTR("> "), false);
    // command
    oled_write_P(debug_enable ? PSTR("D") : PSTR(" "), false);
    oled_write_P(debug_keyboard ? PSTR("K") : PSTR(" "), false);
    oled_write_P(debug_matrix ? PSTR("X") : PSTR(" "), false);
    oled_write_P(debug_mouse ? PSTR("M") : PSTR(" "), false);
    oled_write_P(PSTR("\n"), false);

    // Line 3:
    oled_write_P(PSTR("> "), false);
    uint16_t eeconfig_keymap = eeconfig_read_keymap();
    oled_write_P((eeconfig_keymap & EECONFIG_KEYMAP_SWAP_LALT_LGUI) ? PSTR("SLAG ") : PSTR("     "), false);
    oled_write_P((eeconfig_keymap & EECONFIG_KEYMAP_SWAP_RALT_RGUI) ? PSTR("SRAG ") : PSTR("     "), false);
    oled_write_P(PSTR("\n"), false);

    // Line 4:
    oled_write_P(PSTR("> "), false);
    oled_write_P((d2r_auto_enabled) ? PSTR("AUTO ACT") : PSTR("        "), false);
    oled_write_P(PSTR("\n"), false);
    // Line 5:
    oled_write_P(PSTR("> "), false);
    oled_write_P(PSTR("\n"), false);
    // Line 6:
    oled_write_P(PSTR("> "), false);
    oled_write_P(PSTR("\n"), false);
    // Line 6:
    oled_write_P(PSTR("> "), false);
#ifdef RAW_ENABLE
    switch (protok_os_type) {
        case OS_TYPE_WIN:
            oled_write_P(PSTR("WIN  "), false);
            break;
        case OS_TYPE_LINUX:
            oled_write_P(PSTR("LINUX"), false);
            break;
        case OS_TYPE_MAC:
            oled_write_P(PSTR("MAC  "), false);
            break;
        default:
            break;
    }
#endif
    oled_write_P(PSTR("\n"), false);
}
#endif

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
            return TAPPING_TERM - 50;
        /* case LT(1, KC_GRV): */
        /*     return 130; */
        default:
            return TAPPING_TERM;
    }
}

