#include "protok.h"
#include "song_list.h"
#include "analog.h"
#ifdef ANALOG_JOYSTICK_ENABLE
#include "joystick.h"
#endif
#ifdef THUMBSTICK_ENABLE
#include "thumbstick.h"
#endif
#include "log.h"
#ifdef RAW_ENABLE
#include "raw.h"
#endif

enum layer_names {
    L_DEF = 0,
    L_FUN,
    L_CMD,
    L_SET,
    L_SYM,
    L_NAV
};

// Tap Dance declarations
enum {
    BSPC_TO_SYM,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_SINGLE_TAP_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* base layer PC */
    LAYOUT(
           KC_ESC , XXXXXXX       , KC_F13  , KC_F14 , KC_F15  , KC_F16  , KC_F17  , KC_F18 , KC_F19        , KC_F20  , KC_F21  , KC_F22  , KC_PSCR , KC_CLCK , KC_PAUS , KC_INS  ,
           KC_WBAK, KC_ESC        , KC_F1   , KC_F2  , KC_F3   , KC_F4   , KC_F5   , KC_F6  , KC_F7         , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_HOME , KC_PGUP ,
           KC_DEL , KC_GRV        , KC_1    , KC_2   , KC_3    , KC_4    , KC_5    , KC_6   , KC_7          , KC_8    , KC_9    , KC_0    , KC_MINS , KC_EQL  , KC_END  , KC_PGDN ,
           KC_HOME, KC_TAB        ,           KC_Q   , KC_W    , KC_E    , KC_R    , KC_T   , KC_Y          , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC , KC_RBRC , KC_DEL  ,
           KC_END , LCTL_T(KC_ESC),           KC_A   , KC_S    , KC_D    , KC_F    , KC_G   , KC_H          , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_BSLS , MO(L_FUN),
           MO(L_NAV),                 KC_LSPO , KC_Z   , KC_X    , KC_C    , KC_V    , KC_B   , KC_N          , KC_M    , KC_COMM , KC_DOT  , KC_SLSH ,           KC_RSPC , KC_UP   ,
           MO(L_CMD), XXXXXXX       ,          KC_HYPR , KC_LGUI , KC_LALT , KC_BSPC , RSFT_T(KC_SPC) , RSFT_T(KC_SPC), KC_ENT, MO(L_SYM) , KC_RALT , KC_LEFT , KC_DOWN , KC_RGHT),

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
          TERM_OFF, TERM_ON, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG  , EEP_RST, RESET  , OSL(L_SET),
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
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_3   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* symbol layer */
    LAYOUT(
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_EXLM, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_CIRC, XXXXXXX, KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          KC_AT  , KC_DLR , KC_PERC, KC_ASTR, KC_AMPR, KC_HASH, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* NAV layer */
    LAYOUT(
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP  , KC_END , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_5   ,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

};
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
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    /* keyevent_t event = record->event; */

    switch (id) {

    }
    return MACRO_NONE;
}

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
}

#ifdef AUDIO_ENABLE
float my_song[][2] = SONG(QWERTY_SOUND);
float caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
float caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* uint16_t x_value = 0; */
    /* uint16_t y_value = 0; */
    /* x_value = analogReadPin(JOYSTICK_X); */
    /* y_value = analogReadPin(JOYSTICK_Y); */

#ifdef __ENABLE_LOG
    if (keycode == DEBUG && record->event.pressed) {
        log_init(LOG_DEBUG);
    }
    if (debug_enable) {
        log_init(LOG_DEBUG);
    } else {
        log_init(LOG_INFO);
    }
#endif

#ifdef ANALOG_JOYSTICK_ENABLE
    log_debug("x value %d, y value %d\n", joystick_status.axes[0], joystick_status.axes[1]);
    /* uprintf("x value %d, y value %d\n", x_value, y_value); */
#endif
#ifdef AUDIO_ENABLE
    if (keycode == DEBUG && record->event.pressed) {
        PLAY_SONG(my_song);
        log_debug("debug pressed.\n");
    }
#endif
#ifdef CONSOLE_ENABLE
    log_debug("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n",
              keycode, record->event.key.col, record->event.key.row, record->event.pressed,
              record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

bool led_update_user(led_t led_state) {
#ifdef AUDIO_ENABLE
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
        log_debug("LED Status Changed.\n");
        led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
        caps_state = led_state.caps_lock;
    }
#endif
    return true;
}

#ifdef OLED_ENABLE

/* void render_status(void); */
/* void render_logo(void); */

/* void render_status(void) { */

    // Render to mode icon
    /* static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}}; */

    /* oled_clear(); */

    /* oled_write_P(PSTR("A\n"), false); */
    /* oled_write_P(PSTR("BC\n"), false); */
    /* oled_write_P(PSTR("0123456789ABCDEFGHIJKL\n"), false); */
    /* oled_write_char(0x7f, false); */
    /* oled_write_char(0x0, false); */
    /* oled_write_pixel(64, 32, true); */
    /* if (is_mac_mode()) { */
    /* oled_write_P(os_logo[0][0], false); */
    /* oled_write_P(PSTR("\n"), false); */
    /* oled_write_P(os_logo[0][1], false); */
    /* }else{ */
    /* oled_write_P(os_logo[1][0], false); */
    /* oled_write_P(PSTR("\n"), false); */
    /* oled_write_P(os_logo[1][1], false); */
    /* } */

    /* oled_write_P(PSTR(" "), false); */

    /* oled_write_P(eeconfig_read_debug() ? PSTR("DBG ") : PSTR("NDBG "), false); */

    /* oled_write_P(PSTR("\n"), false); */

    /* // Host Keyboard LED Status */
    /* led_t led_state = host_keyboard_led_state(); */
    /* oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("NAH"), false); */
    /* oled_write_P(host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAP ") : PSTR("NAH"), false); */
    /* oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("NAH"), false); */
    /* static const char PROGMEM qmk_logo[] = { */
    /*     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, */
    /*     0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, */
    /*     0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00 */
    /* }; */

    /* oled_write_P(qmk_logo, false); */
/* } */

/* void render_logo(void) { */
/*     static const char PROGMEM qmk_logo[] = { */
/*         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, */
/*         0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, */
/*         0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00 */
/*     }; */

/*     oled_write_P(qmk_logo, false); */
/* } */

/* void oled_task_user(void) { */
    /* if(is_keyboard_master()){ */
    /* render_status(); */
    /* }else{ */
    /* render_logo(); */
    /*   /1* render_rgbled_status(true); *1/ */
    /* } */
/* } */

void oled_task_user(void) {
    // Line 0:
    oled_write_P(PSTR("> "), false);
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case L_DEF:
            oled_write_P(PSTR("Default"), false);
            break;
        case L_FUN:
            oled_write_P(PSTR("FN"), false);
            break;
        case L_CMD:
            oled_write_P(PSTR("Command"), false);
            break;
        case L_SET:
            oled_write_P(PSTR("Setup"), false);
            break;
        case L_SYM:
            oled_write_P(PSTR("Symbol"), false);
            break;
        case L_NAV:
            oled_write_P(PSTR("Nav"), false);
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

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }
    /* else if (state->count == 2) return TD_DOUBLE_TAP; */
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(L_SYM);
            break;
        /* case TD_DOUBLE_TAP: */
        /*     // Check to see if the layer is already set */
        /*     if (layer_state_is(_MY_LAYER)) { */
        /*         // If already set, then switch it off */
        /*         layer_off(_MY_LAYER); */
        /*     } else { */
        /*         // If not already set, then switch the layer on */
        /*         layer_on(_MY_LAYER); */
        /*     } */
        /*     break; */
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(L_SYM);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [BSPC_TO_SYM] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};
