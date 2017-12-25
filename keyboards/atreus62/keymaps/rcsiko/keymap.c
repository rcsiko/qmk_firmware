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

static bool gSwapNumbersAndSymbols = true;

enum own_keys {
  SWAP_SYMS = SAFE_RANGE
};

// Layers
enum {
    BASE = 0,
    NAV,
    SYM,
    NUM
};

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

        { KC_GRV         ,KC_1     ,KC_2     ,KC_3     ,KC_4     ,KC_5          ,_NO_               ,KC_6           ,KC_7    ,KC_8    ,KC_9    ,KC_0              ,KC_BSPC },
        { KC_TAB         ,KC_Q     ,KC_W     ,KC_E     ,KC_R     ,KC_T          ,_NO_               ,KC_Y           ,KC_U    ,KC_I    ,KC_O    ,KC_P              ,KC_BSLS },
        {CTL_T(KC_ESC)   ,KC_A     ,KC_S     ,KC_D     ,KC_F     ,KC_G          ,_NO_               ,KC_H           ,KC_J    ,KC_K    ,KC_L    ,LT(NAV,KC_SCLN)   ,KC_QUOT },
        { KC_LSFT        ,KC_Z     ,KC_X     ,KC_C     ,KC_V     ,KC_B          ,LT(SYM, KC_ENT)    ,KC_N           ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH           ,KC_RSFT },
        { MO(NUM)        ,KC_NO    ,KC_NO    ,KC_NO    ,KC_LALT  ,KC_RGUI       ,LT(SYM, KC_SPC)    ,GUI_T(KC_ENT)  ,KC_RALT ,KC_NO   ,KC_NO   ,KC_RCTRL          ,LCAG(KC_NO) }

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

        { _____  ,KC_F1    ,KC_F2    ,KC_F3    ,KC_F4    ,KC_F5    ,_NO_    ,KC_F6      ,KC_F7       ,KC_F8       ,KC_F9        ,KC_F10   ,KC_DEL },
        { _____  ,_____    ,_____    ,_____    ,_____    ,_____    ,_NO_    ,_____      ,KC_PGUP     ,KC_UP       ,KC_PGDN      ,_____    ,_____ },
        { _____  ,KC_LSFT  ,KC_LCTL  ,KC_LALT  ,KC_LGUI  ,_____    ,_NO_    ,_____      ,KC_LEFT     ,KC_DOWN     ,KC_RIGHT     ,_____    ,_____ },
        { _____  ,_____    ,_____    ,_____    ,_____    ,_____    ,_____   ,_____      ,_____       ,_____       ,_____        ,_____    ,_____ },
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

      { _____   ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5    ,_NO_    ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_DEL },
      { _____   ,_____   ,_____   ,_____   ,_____   ,KC_LBRC  ,_NO_    ,KC_RBRC ,_____   ,_____   ,_____   ,_____   ,_____ },
      { KC_CAPS ,_____   ,_____   ,_____   ,_____   ,KC_LCBR  ,_NO_    ,KC_RCBR ,_____   ,_____   ,_____   ,_____   ,_____ },
      { _____   ,_____   ,_____   ,_____   ,_____   ,KC_EQL   ,_____   ,KC_MINS ,_____   ,_____   ,_____   ,_____   ,_____ },
      { _____   ,_____   ,_____   ,_____   ,_____   ,_____    ,_____   ,_____   ,_____   ,_____   ,_____   ,_____   ,_____ }
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

        { _____  ,_____  ,_____  ,_____  ,_____  ,SWAP_SYMS    ,_NO_       ,_____   ,_____   ,_____  ,_____   ,_____   ,_____ },
        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_NO_       ,KC_VOLU ,KC_P7   ,KC_P8  ,KC_P9   ,KC_PAST ,_____ },
        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_NO_       ,KC_VOLD ,KC_4    ,KC_5   ,KC_6    ,KC_PPLS ,_____ },
        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_____      ,KC_MUTE ,KC_1    ,KC_2   ,KC_3    ,KC_PSLS ,_____ },
        { _____  ,_____  ,_____  ,_____  ,_____  ,_____        ,_____      ,_____   ,KC_PDOT ,KC_0   ,KC_PDOT ,KC_PMNS ,_____ }
    }
};

const uint16_t PROGMEM fn_actions[] = {
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{

}

bool process_record_user(uint16_t kc, keyrecord_t *rec) {
    uint8_t layer = biton32(layer_state);

    if (kc == SWAP_SYMS) {
      if (rec->event.pressed) {
        gSwapNumbersAndSymbols = !gSwapNumbersAndSymbols;
      }
    }

    // Swap the numbers and symbols on the base layer if no other modifier is pressed
    if (gSwapNumbersAndSymbols &&
        !(keyboard_report->mods & (~MOD_BIT(KC_LSFT) & ~MOD_BIT(KC_RSFT))) && //    modifier being pressed
        layer == BASE &&
        (kc == KC_1 ||
         kc == KC_2 ||
         kc == KC_3 ||
         kc == KC_4 ||
         kc == KC_5 ||
         kc == KC_6 ||
         kc == KC_7 ||
         kc == KC_8 ||
         kc == KC_9 ||
         kc == KC_0)) {

        if (rec->event.pressed) {
            uint8_t lshifted = keyboard_report->mods & MOD_BIT(KC_LSFT);
            uint8_t osmlshifted = get_oneshot_mods() & MOD_BIT(KC_LSFT) && !has_oneshot_mods_timed_out();

            unregister_mods(MOD_LSFT);

            if (lshifted) {
                unregister_mods(MOD_LSFT);
                register_code(kc);
                register_mods(MOD_LSFT);
            } else if (osmlshifted) {
                clear_oneshot_mods();
                register_code(kc);
            } else {
                register_mods(MOD_LSFT);
                register_code(kc);
                unregister_mods(MOD_LSFT);
            }
        } else {
            unregister_code(kc);
        }

        return false;
    }

    return true;

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
