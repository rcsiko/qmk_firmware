/* Template
 *
 * ,-----------------------------------------.                        ,------------------------------------------.
 * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
 * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
 * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
 * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
 * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
 * |------+------+------+------+------+------|  ,------.    ,------.  |------+------+------+------+------+-------|
 * |      |      |      |      |      |      |  |      |    |      |  |      |      |      |      |      |       |
 * |------+------+------+------+------+------|  |      |    |      |  |------+------+------+------+------+-------|
 * |      |      |      |      |      |      |  |      |    |      |  |      |      |      |      |      |       |
 * `-----------------------------------------'  `------'    `------'  `------------------------------------------'
 *
 */


#include <stdarg.h>
#include "atreus62.h"
#include "action_layer.h"
#include "action_util.h"

#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_RSFT OSM(MOD_RSFT)
#define OSM_LGUI OSM(MOD_LGUI)

#define KC_HYP LSFT(LALT(LCTL(KC_LGUI)))

#define _NO_ KC_NO
#define _____ KC_TRNS
#define LS(arg) LSFT(arg)

#define G(arg) LGUI(arg)
#define GS(arg) G(S(arg))

// Layers
enum {
    BASE = 0,
    NAV,
    SYM,
    NUM
};

enum function_id {
    ESC,
    BSPC
};

#define LT_SYM_SPC 0x7100  //LT(SYM, KC_SPC)

bool layer_interrupted = false;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Keymap 0: Base Layer
         *
         * ,-----------------------------------------.                        ,------------------------------------------.
         * |      |   !  |   @  |   #  |   $  |   %  |                        |   ^  |   &  |   *  |   (  |   )  | Backs |
         * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
         * |      |   Q  |   W  |   E  |   R  |   T  |                        |   Y  |   U  |   I  |   O  |   P  |   \ | |
         * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
         * |      |   A  |   S  |   D  |   F  |   G  |                        |   H  |   J  |   K  |   L  | ; NAV| ' "/C |
         * |------+------+------+------+------+------|  ,------.    ,------.  |------+------+------+------+------+-------|
         * |      |   Z  |   X  |   C  |   V  |   B  |  |      |    |      |  |   N  |   M  |   ,  |   .  |  / ? |   Sh  |
         * |------+------+------+------+------+------|  |Space |    | Enter|  |------+------+------+------+------+-------|
         * |      |      |      | LAlt | LGui |      |  |      |    |      |  | RAlt |      |      |      |  LGAC|       |
         * `-----------------------------------------'  `------'    `------'  `------------------------------------------'
         *
         */
    [BASE] = {

        { F(ESC)   ,KC_1     ,KC_2     ,KC_3     ,KC_4     ,KC_5          ,_NO_               ,KC_6           ,KC_7    ,KC_8    ,KC_9    ,KC_0      ,KC_BSPC },
        { KC_TAB   ,KC_Q     ,KC_W     ,KC_E     ,KC_R     ,KC_T          ,_NO_               ,KC_Y           ,KC_U    ,KC_I    ,KC_O    ,KC_P      ,KC_BSLS },
        { KC_LCTL  ,KC_A     ,KC_S     ,KC_D     ,KC_F     ,KC_G          ,_NO_               ,KC_H           ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN   ,KC_QUOT },
        { KC_LSFT  ,KC_Z     ,KC_X     ,KC_C     ,KC_V     ,KC_B          ,LT(NAV, KC_SPC)    ,KC_N           ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH   ,KC_RSFT },
        { KC_LCTL  ,MO(NUM)  ,KC_NO    ,KC_NO    ,KC_LALT  ,GUI_T(KC_SPC) ,LT_SYM_SPC         ,GUI_T(KC_ENT)  ,MO(NAV) ,KC_RALT ,KC_NO   ,KC_RCTRL  ,LCAG(KC_NO) }

    },

        /* Template
         *
         * ,-----------------------------------------.                        ,------------------------------------------.
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|  ,------.    ,------.  |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |  |      |    |      |  |      |      |      |      |      |       |
         * |------+------+------+------+------+------|  |      |    |      |  |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |  |      |    |      |  |      |      |      |      |      |       |
         * `-----------------------------------------'  `------'    `------'  `------------------------------------------'
         *
         */
    [NAV] = {

        { _____  ,KC_F1    ,KC_F2    ,KC_F3    ,KC_F4    ,KC_F5    ,_NO_    ,KC_F6      ,KC_F7       ,KC_F8       ,KC_F9        ,KC_F10   ,KC_F11 },
        { _____  ,_____    ,_____    ,_____    ,_____    ,_____    ,_NO_    ,KC_HOME    ,KC_PGDN     ,KC_PGUP     ,KC_END       ,_____    ,KC_F12 },
        { _____  ,KC_LSFT  ,KC_LCTL  ,KC_LALT  ,KC_LGUI  ,_____    ,_NO_    ,KC_LEFT    ,KC_DOWN     ,KC_UP       ,KC_RIGHT     ,_____    ,_____ },
        { _____  ,_____    ,_____    ,_____    ,_____    ,_____    ,_____   ,G(KC_LEFT) ,G(KC_RIGHT) ,GS(KC_LEFT) ,GS(KC_RIGHT) ,_____    ,_____ },
        { _____  ,_____    ,_____    ,_____    ,_____    ,_____    ,_____   ,_____      ,_____       ,_____       ,_____        ,_____    ,_____ }

    },

        /* Template
         *
         * ,-----------------------------------------.                        ,------------------------------------------.
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|  ,------.    ,------.  |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |  |      |    |      |  |      |      |      |      |      |       |
         * |------+------+------+------+------+------|  |      |    |      |  |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |  |      |    |      |  |      |      |      |      |      |       |
         * `-----------------------------------------'  `------'    `------'  `------------------------------------------'
         *
         */
    [SYM] = {

        { KC_BSPC  ,KC_F1     ,KC_F2     ,KC_F3    ,KC_F4    ,M(0)         ,_NO_       ,_____     ,M(3)      ,M(2)         ,M(4)        ,_____        ,_____ },
        { _____    ,KC_LABK   ,KC_RABK   ,KC_LCBR  ,KC_RCBR  ,KC_PLUS      ,_NO_       ,KC_AT     ,KC_DQT    ,KC_QUOT      ,KC_GRV      ,KC_BSLS      ,_____ },
        { KC_CAPS  ,KC_EXLM   ,KC_EQL    ,KC_LBRC  ,KC_RBRC  ,KC_MINS      ,_NO_       ,KC_UNDS   ,KC_CIRC   ,KC_DLR       ,KC_AMPR     ,KC_PIPE      ,_____ },
        { _____    ,KC_TILD   ,KC_PERC   ,KC_LPRN  ,KC_RPRN  ,KC_ASTR      ,_____      ,KC_HASH   ,KC_SCLN   ,KC_COLN      ,KC_QUES     ,KC_SLSH      ,_____ },
        { _____    ,_____     ,_____     ,_____    ,_____    ,_____        ,_____      ,_____     ,_____     ,_____        ,_____       ,_____        ,_____ }

    },

        /* Template
         *
         * ,-----------------------------------------.                        ,------------------------------------------.
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|                        |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |                        |      |      |      |      |      |       |
         * |------+------+------+------+------+------|  ,------.    ,------.  |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |  |      |    |      |  |      |      |      |      |      |       |
         * |------+------+------+------+------+------|  |      |    |      |  |------+------+------+------+------+-------|
         * |      |      |      |      |      |      |  |      |    |      |  |      |      |      |      |      |       |
         * `-----------------------------------------'  `------'    `------'  `------------------------------------------'
         *
         */
    [NUM] = {

        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_NO_       ,_____  ,_____  ,_____  ,_____  ,_____   ,_____ },
        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_NO_       ,_____  ,KC_7   ,KC_8   ,KC_9   ,_____   ,_____ },
        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_NO_       ,_____  ,KC_4   ,KC_5   ,KC_6   ,_____   ,_____ },
        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_____      ,_____  ,KC_1   ,KC_2   ,KC_3   ,_____   ,_____ },
        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_____      ,_____  ,_____  ,KC_0   ,_____  ,_____   ,_____ }
    }
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(ESC),
    [1] = ACTION_FUNCTION(BSPC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (id == ESC) {
        void (*method)(uint8_t) = (record->event.pressed) ? &add_key : &del_key;
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

        if(layer_state == 0) {
            method(shifted ? KC_GRAVE : KC_ESCAPE);
        } else {
            method(shifted ? KC_ESCAPE : KC_GRAVE);
        }

        send_keyboard_report();
    }

    if( id == BSPC) {
        void (*method)(uint8_t) = (record->event.pressed) ? &add_key : &del_key;
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

        if(layer_state == 0) {
            method(shifted ? KC_MINS : KC_BSPC);
        } else {
            method(shifted ? KC_BSPC : KC_MINS);
        }

        send_keyboard_report();
    }
}

bool command_extra(uint8_t code)
{
    switch (code) {
        case KC_B:
            clear_keyboard();
            print("\n\nJump to bootloader... ");
            _delay_ms(1000);
            bootloader_jump(); // not return
            print("not supported.\n");
            break;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool queue = true;

    //Cancle one-shot mods.
    switch (keycode)
        case KC_ESC:
            if (record->event.pressed && get_oneshot_mods() && !has_oneshot_mods_timed_out()) {
                    clear_oneshot_mods();
                    queue = false;
                    break;

        ///https://github.com/qmk/qmk_firmware/issues/303
        case LT_SYM_SPC:
            if (record->event.pressed) {
                layer_interrupted = false;
                layer_on(SYM);
            } else {
                if (!layer_interrupted) {
                    register_code(KC_SPC);
                    unregister_code(KC_SPC);
                }
                layer_off(SYM);
            }
            return false;
            break;
        default:
            layer_interrupted = true;
            break;
    }

    return queue;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case 0:
            if (record->event.pressed) {
                return MACRO( T(MINS), D(LSHIFT), T(DOT), U(LSHIFT), END  );
            }
            break;
        case 1: // Delete an entile line (macOS)
            if (record->event.pressed) {
                return MACRO( D(LGUI), T(LEFT), T(LEFT), D(LSFT), T(RIGHT), U(LGUI), U(LSFT), T(BSPC), T(BSPC), END  );
            }
            break;
        case 2:
            if (record->event.pressed) {
                return MACRO( D(LALT), T(E), END  );
            }
        case 3:
            if (record->event.pressed) {
                return MACRO( D(LALT), T(J), END  );
            }
        case 4:
            if (record->event.pressed) {
                return MACRO( D(LALT), T(U), END  );
            }
            break;
//        case 2: // é
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(E), T(E), END  );
//            }
//            break;
//        case 3: // á
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(E), T(A), END  );
//            }
//            break;
//        case 4: // ó
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(E), T(O), END  );
//            }
//            break;
//        case 5: // ú
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(E), T(U), END  );
//            }
//            break;
//        case 6: // í
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(E), T(U), END  );
//            }
//            break;
//       case 7: // ö
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(U), T(O), END  );
//            }
//            break;
//        case 8: // ü
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(U), T(U), END  );
//            }
//            break;
//        case 9: // ő
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(J), T(O), END  );
//            }
//            break;
//        case 9: // ű
//            if (record->event.pressed) {
//                return MACRO( D(LALT), T(J), T(U), END  );
//            }
//            break;

    }
    return MACRO_NONE;
};
