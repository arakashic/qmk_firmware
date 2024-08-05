#include QMK_KEYBOARD_H
#include "analog.h"
#include "quantum.h"
#include "os_detection.h"
#ifdef ANALOG_JOYSTICK_ENABLE
#include "joystick.h"
#endif
#include "joystick.h"
#ifdef THUMBSTICK_ENABLE
#include "thumbstick.h"
#endif
#include "common/log.h"
#include <stdbool.h>
#include "common/rpt_macro.h"

enum layer_names {
    L_DEF = 0,
    L_GAME,
    L_D4,
    L_FUN,
    L_SYM,
    L_NAV,
    L_SET,
    L_CMD
};

#define PK_BSPC LT(L_SYM, KC_BSPC)
#define PK_SPC  RSFT_T(KC_SPC)
#define PK_LCTL LCTL_T(KC_ESC)
#define PK_TAB  LT(L_NAV, KC_TAB)

enum custom_keycodes {
    M_RPT1 = SAFE_RANGE,
    M_RPTS
};

os_variant_t os = OS_UNSURE;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* base layer PC */
    LAYOUT_gen2(
           KC_MUTE           , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_CAPS, KC_INS ,
           KC_DEL   , KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_HOME, KC_END ,
           KC_HOME  , PK_TAB ,          KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_DEL ,
           KC_END   , PK_LCTL,          KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_BSLS, MO(L_FUN),
           XXXXXXX  ,          SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          SC_RSPC, KC_PGUP,
           MO(L_CMD), PB_1   , PB_2   , KC_HYPR, KC_LGUI,          KC_LALT, PK_BSPC, PK_SPC , KC_ENT , KC_RALT, KC_RGUI, KC_LCTL, XXXXXXX, KC_UP  , KC_PGDN,
                                                                                                                                  KC_LEFT, KC_DOWN, KC_RGHT),
    /* Game layer PC */
    LAYOUT_gen2(
           KC_ESC            , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_CAPS, KC_INS ,
           KC_ESC   , KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_HOME, KC_END ,
           KC_HOME  , KC_TAB ,          KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSPC,
           KC_END   , PK_LCTL,          KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_BSLS, MO(L_FUN),
           KC_DEL   ,          SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          SC_RSPC, KC_PGUP,
           MO(L_CMD), XXXXXXX, M_RPTS , KC_HYPR, KC_LGUI,          KC_LALT, KC_SPC , KC_SPC , KC_ENT , KC_RALT, KC_RGUI, KC_LCTL, XXXXXXX, KC_UP  , KC_PGDN,
                                                                                                                                  KC_LEFT, KC_DOWN, KC_RGHT),
    /* Game layer PC */
    LAYOUT_gen2(
           KC_ESC            , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_CAPS, KC_INS ,
           KC_ESC   , KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_HOME, KC_END ,
           KC_HOME  , KC_TAB ,          KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSPC,
           KC_END   , PK_LCTL,          KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_BSLS, MO(L_FUN),
           KC_DEL   ,          SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          SC_RSPC, KC_PGUP,
           MO(L_CMD), XXXXXXX, M_RPTS , KC_HYPR, KC_LALT,          M_RPT1 , KC_SPC , KC_SPC , KC_ENT , KC_RALT, KC_RGUI, KC_LCTL, XXXXXXX, KC_UP  , KC_PGDN,
                                                                                                                                  KC_LEFT, KC_DOWN, KC_RGHT),
    /* additional func */
    LAYOUT_gen2(
           _______,          KC_PWR , KC_SLEP, KC_WAKE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_MUTE, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_VOLU, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_VOLD,          KC_LEFT, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, _______,
           _______, _______, _______, _______, _______         , _______, KC_SPC , KC_RSFT, KC_3   , _______, _______, _______, _______, _______, _______,
                                                                                                                                _______, _______, _______),

    /* symbol layer */
    LAYOUT_gen2(
           XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_NUM, KC_CAPS, KC_SCRL,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_EXLM, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_CIRC, XXXXXXX, KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          KC_AT  , KC_DLR , KC_PERC, KC_ASTR, KC_AMPR, KC_HASH, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, KC_4   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                XXXXXXX, XXXXXXX, XXXXXXX),

    /* NAV layer */
    LAYOUT_gen2(
           XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_UP  , XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP  , KC_END , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, KC_5   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                XXXXXXX, XXXXXXX, XXXXXXX),

    /* bootmagic key layer */
    LAYOUT_gen2(
           XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           NK_TOGG, NK_ON  , NK_OFF , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           AG_NORM, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, KC_CALC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AG_LNRM         , AG_LSWP, XXXXXXX, XXXXXXX, XXXXXXX, AG_RSWP, AG_RNRM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                XXXXXXX, XXXXXXX, XXXXXXX),

    /* command jump layer */
    LAYOUT_gen2(
           XXXXXXX         , DT_PRNT,   DT_UP, DT_DOWN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, DB_TOGG,  EE_CLR,  QK_RBT, OSL(L_SET),
           KC_ACL2, XXXXXXX,TO(L_DEF),TO(L_GAME),TO(L_D4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL1, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL0, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, KC_7   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                XXXXXXX, XXXXXXX, XXXXXXX),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L_DEF] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_GAME] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_FUN] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_SYM] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_NAV] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_SET] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L_CMD] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

// clang-format on

#ifdef ANALOG_JOYSTICK_ENABLE
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_IN_OUT(JOYSTICK_X, JOYSTICK_VCC, 0, 2047, 4096),
    [1] = JOYSTICK_AXIS_IN_OUT(JOYSTICK_Y, JOYSTICK_VCC, 0, 2047, 4096)
};
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_RGHT);
        } else {
            tap_code(KC_LEFT);
        }
    }
    if (index == 2) { /* Third encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif

void keyboard_pre_init_user(void) {
#ifdef THUMBSTICK_ENABLE
    setPinOutput(THUMBSTICK_VCC);
#endif
}

void matrix_init_user(void) {
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=false;
    debug_matrix=false;
    debug_keyboard=false;
    debug_mouse=false;
#ifdef OLED_ENABLE
    oled_clear();
#endif
    rpt_init();
}

void housekeeping_task_user(void)
{
    os_variant_t new_os = detected_host_os();
    if (os != new_os) {
        os = new_os;
        keymap_config.raw = eeconfig_read_keymap();
        if (os == OS_MACOS || os == OS_IOS) {
            keymap_config.swap_lalt_lgui = true;
        } else {
            keymap_config.swap_lalt_lgui = false;
        }
        eeconfig_update_keymap(keymap_config.raw);
    }
}

void matrix_scan_user(void) {
    /* int16_t val = (((uint32_t)timer_read() % 5000 - 2500) * 255) / 5000; */

    /* if (val != joystick_status.axes[0]) { */
    /*     joystick_status.axes[0] = val; */
    /*     joystick_status.status |= JS_UPDATED; */
    /* } */
    /* if (val != joystick_status.axes[1]) { */
    /*     joystick_status.axes[1] = val; */
    /*     joystick_status.status |= JS_UPDATED; */
    /* } */
    rpt_runner();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef __ENABLE_LOG
    if (keycode == DB_TOGG && record->event.pressed) {
        log_init(LOG_DEBUG);
    }
    if (debug_enable) {
        log_init(LOG_DEBUG);
    } else {
        log_init(LOG_INFO);
    }
#endif

#ifdef ANALOG_JOYSTICK_ENABLE
    uint16_t x_value = 0;
    uint16_t y_value = 0;
    x_value = analogReadPin(JOYSTICK_X);
    y_value = analogReadPin(JOYSTICK_Y);
    /* log_debug("x value %d, y value %d\n", joystick_status.axes[0], joystick_status.axes[1]); */
    uprintf("x value %d, y value %d\n", x_value, y_value);
#endif
#ifdef CONSOLE_ENABLE
    log_debug("KL: kc: 0x%04X, col: %u, row: %u, pressed: %x, time: %u, interrupt: %x, count: %u\n",
              keycode, record->event.key.col, record->event.key.row, record->event.pressed,
              record->event.time, record->tap.interrupted, record->tap.count);
#endif
    switch (keycode) {
    case M_RPT1:
        if (record->event.pressed) {
            rpt_toggle();
        } else {
        }
        break;

    case M_RPTS:
        if (record->event.pressed) {
            rpt_disable();
        } else {
        }
        break;
    }

    return true;
}

// #ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
    // Line 0:
    oled_write_P(PSTR("\x80\x81\x82\x83 "), false);
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case L_DEF:
            oled_write_P(PSTR("Default"), false);
            break;
        case L_GAME:
            oled_write_P(PSTR("Game"), false);
            break;
        case L_D4:
            oled_write_P(PSTR("Diablo 4"), false);
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
            oled_write_P(PSTR("Undefined"), false);
    }
    oled_write_P(PSTR("\n"), false);

    // Line 1:
    oled_write_P(PSTR("\xa0\xa1\xa2\xa3 "), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("\x86\x87") : PSTR("  "), false);
    oled_write_P(led_state.caps_lock ? PSTR("\x84\x85") : PSTR("  "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("\x88\x89") : PSTR("  "), false);
    oled_write_P(PSTR("\n"), false);

    // Line 2:
    oled_write_P(PSTR("\xc0\xc1\xc2\xc3 "), false);
    // command
    oled_write_P(led_state.num_lock ? PSTR("\xa6\xa7") : PSTR("  "), false);
    oled_write_P(led_state.caps_lock ? PSTR("\xa4\xa5") : PSTR("  "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("\xa8\xa9") : PSTR("  "), false);
    oled_write_P(debug_enable ? PSTR("D") : PSTR(" "), false);
    oled_write_P(debug_keyboard ? PSTR("K") : PSTR(" "), false);
    oled_write_P(debug_matrix ? PSTR("X") : PSTR(" "), false);
    oled_write_P(debug_mouse ? PSTR("M") : PSTR(" "), false);
    oled_write_P(PSTR("\n"), false);

    // Line 3:
    oled_write_P(PSTR(">    "), false);
    uint16_t eeconfig_keymap = eeconfig_read_keymap();
    oled_write_P((eeconfig_keymap & EECONFIG_KEYMAP_SWAP_LALT_LGUI) ? PSTR("\x8a\x8b ") : PSTR("   "), false);
    oled_write_P((eeconfig_keymap & EECONFIG_KEYMAP_SWAP_RALT_RGUI) ? PSTR("SRAG ") : PSTR("     "), false);
    oled_write_P(rpt_message(), false);
    oled_write_P(PSTR("\n"), false);

    // Line 4:
    oled_write_P(PSTR("> "), false);
    switch (os) {
        case OS_UNSURE:
            oled_write_P(PSTR("  "), false);
            break;
        case OS_LINUX:
            oled_write_P(PSTR("\x99\x9a"), false);
            break;
        case OS_WINDOWS:
            oled_write_P(PSTR("\x97\x98"), false);
            break;
        case OS_MACOS:
            oled_write_P(PSTR("\x95\x96"), false);
            break;
        case OS_IOS:
            oled_write_P(PSTR("\x95\x96"), false);
            break;
        default:
            oled_write_P(PSTR("  "), false);
    }
    oled_write_P(PSTR("\n"), false);
    // Line 5:
    oled_write_P(PSTR("> "), false);
    switch (os) {
        case OS_UNSURE:
            oled_write_P(PSTR("  "), false);
            break;
        case OS_LINUX:
            oled_write_P(PSTR("\xb9\xba"), false);
            break;
        case OS_WINDOWS:
            oled_write_P(PSTR("\xb7\xb8"), false);
            break;
        case OS_MACOS:
            oled_write_P(PSTR("\xb5\xb6"), false);
            break;
        case OS_IOS:
            oled_write_P(PSTR("\xb5\xb6"), false);
            break;
        default:
            oled_write_P(PSTR("  "), false);
    }
    oled_write_P(PSTR("\n"), false);
    // Line 6:
    oled_write_P(PSTR("> "), false);
    oled_write_P(PSTR("\n"), false);
    // Line 6:
    oled_write_P(PSTR("> "), false);
    oled_write_P(PSTR("\n"), false);

    return true;
}
// #endif

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            // Immediately select the hold action when another key is pressed.
            return false;
        default:
            // Do not select the hold action when another key is pressed.
            return true;
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
            return TAPPING_TERM;
        /* case LT(1, KC_GRV): */
            return 130;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_SPC):
            return 50;
        default:
            return QUICK_TAP_TERM;
    }
}
