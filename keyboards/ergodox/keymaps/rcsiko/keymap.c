#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "led.h"
#include "keymap.h"
#include "timer.h"

#define BASE   0
#define SYM    1
#define NAV    2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |    `~     |   1  |   2  |   3  |   4  |   5  | = +  |           |  - _ |   6  |   7  |   8  |   9  |   0  | Backspace |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |  Tab      |   Q  |   W  |   E  |   R  |   T  |  {   |           |   }  |   Y  |   U  |   I  |   O  |   P  |   \ |     |
 * |-----------+------+------+------+------+------|  [   |           |   ]  |------+------+------+------+------+-----------|
 * | ESC(CTRL) |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   ' "     |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |  LShift   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |   LShift  |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      |LCtrl | LAlt | LGui |                                       | RGui | Left | Down |  Up  | Right |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Home | End  |           | PgDn | PgUp |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |Space |Shift |------|           |------|Shift | Enter|
 *                                  |      | Bspc |  SYM |           |  NAV | Spc  |      |
 *                                  `--------------------'           `--------------------'
 *
 */
[BASE]=KEYMAP(//left half
              KC_GRV,         KC_1,       KC_2,     KC_3,           KC_4,       KC_5,     KC_EQL,
              KC_TAB,         KC_Q,       KC_W,     KC_E,           KC_R,       KC_T,     KC_LBRC,
              CTL_T(KC_ESC),  KC_A,       KC_S,     KC_D,           KC_F,       KC_G,
              KC_LSFT,        KC_Z,       KC_X,     KC_C,           KC_V,       KC_B,     KC_NO,
              KC_NO,          KC_NO,  KC_LCTRL,  KC_LALT,        KC_LGUI,
                                                                                KC_HOME, KC_END,
                                                                                          KC_NO,
                                                              KC_SPC,   SFT_T(KC_BSPC), TT(SYM),


              //right half
              KC_MINS,        KC_6,       KC_7,     KC_8,           KC_9,       KC_0,     KC_BSPC,
              KC_RBRC,        KC_Y,       KC_U,     KC_I,           KC_O,       KC_P,     KC_BSLS,
                              KC_H,       KC_J,     KC_K,           KC_L,       KC_SCLN,  KC_QUOT,
              KC_NO,          KC_N,       KC_M,     KC_COMM,        KC_DOT,     KC_SLSH,  KC_LSFT,
                              KC_RGUI,    KC_LEFT,  KC_DOWN,        KC_UP,      KC_RIGHT,
              KC_PGDOWN,      KC_PGUP,
              KC_NO,
              TT(NAV),        SFT_T(KC_SPC),     KC_ENT),

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   .  |   0  |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYM] = KEYMAP(
                // left hand
                KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
                KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
                KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
                KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS,
                KC_TRNS,
                KC_TRNS,KC_TRNS,KC_TRNS,
                // right hand
                KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
                KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                KC_DOT,  KC_0,  KC_0,    KC_EQL,  KC_TRNS,
                KC_TRNS, KC_TRNS,
                KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS ),

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   .  |   0  |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// NAVIGATION
[NAV] = KEYMAP(
               // left hand
               KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
               KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
               KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
               KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS,
               KC_TRNS,
               KC_TRNS,KC_TRNS,KC_TRNS,
               // right hand
               KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
               KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_TRNS, KC_TRNS, 
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS,
               KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS ),
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

uint8_t current_layer = BASE;

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_led_all_off();
  current_layer = layer;

  // layer leds
  if (current_layer != BASE) {
    ergodox_board_led_on();
  }

  // capslock
  if (host_keyboard_leds() & (3<<USB_LED_CAPS_LOCK)) {
    ergodox_board_led_on();
  }

  // Temporary leds

  // if the shifted is pressed I show the case led in a brighter color. This is nice to
  // differenciate the shift from the capslock.
  // Notice that I make sure that we're not using the shift on a chord shortcut (pressing
  // shift togather with other modifiers).
  if((keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) &&                                 // is shift pressed and there is no other
      !(keyboard_report->mods & (~MOD_BIT(KC_LSFT) & ~MOD_BIT(KC_RSFT)))) ||                           //    modifier being pressed as well
     (get_oneshot_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) && !has_oneshot_mods_timed_out())) {  // or the one shot shift didn't timed out
    ergodox_board_led_on();
  }
};

bool process_record_user(uint16_t kc, keyrecord_t *rec) {

    if (kc == KC_1 ||
        kc == KC_2 ||
        kc == KC_3 ||
        kc == KC_4 ||
        kc == KC_5 ||
        kc == KC_6 ||
        kc == KC_7 ||
        kc == KC_8 ||
        kc == KC_9 ||
        kc == KC_0) {

        if (rec->event.pressed) {
            bool lshifted = keyboard_report->mods & MOD_BIT(KC_LSFT);

            unregister_mods(MOD_LSFT);

            if (lshifted) {
                unregister_mods(MOD_LSFT);
                register_code(kc);
                register_mods(MOD_LSFT);
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
