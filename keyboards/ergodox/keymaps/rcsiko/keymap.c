#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "led.h"
#include "keymap.h"
#include "timer.h"

#define BASE      0
#define MOUSE     1
#define NAV       2
#define CAPS      3

#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)

#define KC_COPY     LCTL(KC_C)
#define KC_PASTE    LCTL(KC_V)
#define KC_UNDO     LCTL(KC_Z)
#define KC_REDO     LCTL(LSFT(KC_Z))

#define _____ KC_NO
#define xxxxx KC_TRNS

#define SPOTLT                      LGUI(KC_SPC)
#define ITERM                       LALT(KC_SPC)
#define PREV_TAB                    LGUI(LSFT(KC_LBRC))
#define NEXT_TAB                    LGUI(LSFT(KC_RBRC))
#define PREV_WS                     LGUI(LALT(LCTL(KC_LBRC)))
#define NEXT_WS                     LGUI(LALT(LCTL(KC_RBRC)))
#define XCODE_SHOW_ITEMS            LCTL(KC_6)
#define XCODE_QUICK_OPEN            LGUI(LSFT(KC_O))
#define XCODE_JUMP_COUNTERPART      LGUI(LCTL(KC_UP))
#define XCODE_MOVE_DOWN             LALT(KC_DOWN)
#define XCODE_MOVE_UP               LALT(KC_UP)

#define BLINK_BASE  150U // timer threshold for blinking on CAPS layer

typedef enum onoff_t {OFF, ON} onoff;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |    `~     |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  | Backspace |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |  Tab      |   Q  |   W  |   E  |   R  |   T  |  {   |           |   }  |   Y  |   U  |   I  |   O  |   P  |   \ |     |
 * |-----------+------+------+------+------+------|  [   |           |   ]  |------+------+------+------+------+-----------|
 * | ESC(CTRL) |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ; NAV|   ' "     |
 * |-----------+------+------+------+------+------|  =   |           |   -  |------+------+------+------+------+-----------|
 * |   Shift   |   Z  |   X  |   C  |   V  |   B  |  +   |           |   _  |   N  |   M  |   ,  |   .  |  / ? |   Shift   |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |Capslck|      |LCtrl | LAlt | LGui |                                       | Left | Down |  Up  | Right|       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |Ctl+6 | Q.Op |           | XJmp.|      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |iTerm |           | PgUp |      |      |
 *                                  |Space | Bspc |------|           |------|Space | Enter|
 *                                  | NAV  |      |Spotl.|           | PgDn |  MS  |  NAV |
 *                                  `--------------------'           `--------------------'
 *
 */
[BASE]=KEYMAP(//left half
              KC_GRV,         KC_1,           KC_2,     KC_3,           KC_4,       KC_5,     KC_LABK,
              KC_TAB,         KC_Q,           KC_W,     KC_E,           KC_R,       KC_T,     KC_LBRC,
              CTL_T(KC_ESC),  KC_A,           KC_S,     KC_D,           KC_F,       KC_G,
              KC_LSFT,        KC_Z,           KC_X,     KC_C,           KC_V,       KC_B,     KC_EQL,
              TT(CAPS),      _____,           KC_LCTRL,   KC_LALT,        KC_LGUI,
                                                                       XCODE_SHOW_ITEMS,  XCODE_QUICK_OPEN,
                                                                                                     ITERM,
                                                                        LT(NAV, KC_SPC), KC_BSPC,   SPOTLT,


              //right half
              KC_RABK,        KC_6,       KC_7,     KC_8,        KC_9,       KC_0,              KC_BSPC,
              KC_RBRC,        KC_Y,       KC_U,     KC_I,        KC_O,       KC_P,              KC_BSLS,
                              KC_H,       KC_J,     KC_K,        KC_L,       LT(NAV, KC_SCLN),  KC_QUOT,
              KC_MINS,        KC_N,       KC_M,     KC_COMM,     KC_DOT,     KC_SLSH,           KC_LSFT,
                                          KC_LEFT,  KC_DOWN,     KC_UP,      KC_RIGHT,          _____,
              XCODE_JUMP_COUNTERPART,    _____,
              KC_PGUP,
              KC_PGDOWN,   LT(MOUSE, KC_SPC),   LT(NAV, KC_ENT)),

/* Keymap 1: Navigation Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      | Prev |           | Next |      | PgUp |  Up  |PgDown|      |   F12  |
 * |--------+------+------+------+------+------| Tab  |           | Tab  |------+------+------+------+------+--------|
 * |        |  Sft | Ctrl |  Alt | GUI  |      |------|           |------|      | Left | Down | Rigth|      |Vol.Up. |
 * |--------+------+------+------+------+------| Prev |           | Next |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |  WS  |           |  WS  |      |      |      |      |      |Vol.Down|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | Prev | Next |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | Play |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Navigation
[NAV] = KEYMAP(
                // left hand
                xxxxx,    KC_F1,    KC_F2,    KC_F3,     KC_F4,    KC_F5,  xxxxx,
                xxxxx,    _____,   _____,     _____,     _____,    _____,  PREV_TAB,
                xxxxx,    KC_LSFT, KC_LCTRL,  KC_LALT,   KC_LGUI,  _____,
                xxxxx,    _____,   _____,     _____,     _____,    _____,  PREV_WS,
                xxxxx,    xxxxx,   xxxxx,     xxxxx,     xxxxx,
                                                              xxxxx, xxxxx,
                                                                     xxxxx,
                                                         xxxxx,xxxxx,xxxxx,
                // right hand
                xxxxx,    KC_F6,  KC_F7,     KC_F8,      KC_F9,      KC_F10,   KC_F11,
                NEXT_TAB, _____,  KC_PGUP,    KC_UP,     KC_PGDOWN,  _____,   KC_F12,
                          _____,  KC_LEFT,   KC_DOWN,    KC_RIGHT,   xxxxx,   KC_VOLU,
                NEXT_WS,  _____,  _____,     _____,      _____,      _____,   KC_VOLD,
                                  xxxxx,     xxxxx,      xxxxx,      xxxxx,   xxxxx,
                KC_MRWD, KC_MFFD,
                KC_MPLY,
                xxxxx, xxxxx, xxxxx ),

/* Keymap 1: Navigation Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |     |         |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Lclk | MsUp | Rclk |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  Sft | Ctrl |  Alt | GUI  |      |------|           |------|      |MsLeft|MsDown|MsRght|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |WhRght|WhDown| WhUp |WhLeft|WhClk |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Mouse
[MOUSE] = KEYMAP(
               // left hand
              xxxxx,    xxxxx,   xxxxx,     xxxxx,     xxxxx,    xxxxx,  xxxxx,
              xxxxx,    _____,   KC_ACL0,   KC_ACL1,   KC_ACL2,  _____,  xxxxx,
              xxxxx,    KC_LSFT, KC_LCTRL,  KC_LALT,   KC_LGUI,  _____,
              xxxxx,    _____,   _____,     _____,     _____,    _____,  xxxxx,
              xxxxx,    xxxxx,   xxxxx,     xxxxx,     xxxxx,
                                                              xxxxx, xxxxx,
                                                                     xxxxx,
                                                         xxxxx,xxxxx,xxxxx,
               // right hand
               xxxxx, xxxxx,   xxxxx,     xxxxx,    xxxxx,     xxxxx,   xxxxx,
               xxxxx, _____,   KC_BTN1,   KC_MS_U,  KC_BTN2,   _____,   xxxxx,
                      _____,   KC_MS_L,   KC_MS_D,  KC_MS_R,   _____,   xxxxx,
               xxxxx, KC_WH_L, KC_WH_D,   KC_WH_U,  KC_WH_R,   KC_BTN3, xxxxx,
                               xxxxx,     xxxxx,    xxxxx,     xxxxx,   xxxxx,
               xxxxx, xxxxx,
               xxxxx,
               xxxxx, xxxxx, xxxxx ),
// Capslock
// Custom caps lock layer to workaround macOS caps lock delay
[CAPS] = KEYMAP(
               // left hand
               xxxxx, xxxxx, xxxxx, xxxxx, xxxxx, xxxxx, xxxxx,
               xxxxx, xxxxx, xxxxx, xxxxx, xxxxx, xxxxx, xxxxx,
               xxxxx, xxxxx, xxxxx, xxxxx, xxxxx, xxxxx,
               xxxxx, xxxxx, xxxxx, xxxxx, xxxxx, xxxxx, xxxxx,
               xxxxx, xxxxx, xxxxx, xxxxx, xxxxx,
               xxxxx, xxxxx,
               xxxxx,
               xxxxx,xxxxx,xxxxx,
               // right hand
               xxxxx, xxxxx,   xxxxx,   xxxxx,   xxxxx,    xxxxx, xxxxx,
               xxxxx, xxxxx,   xxxxx,   xxxxx,   xxxxx,    xxxxx, xxxxx,
               xxxxx, xxxxx,   xxxxx,   xxxxx,   xxxxx,    xxxxx,
               xxxxx, xxxxx,   xxxxx,   xxxxx,   xxxxx,    xxxxx, xxxxx,
               xxxxx, xxxxx,   xxxxx,    xxxxx, xxxxx,
               xxxxx, xxxxx,
               xxxxx,
               xxxxx, xxxxx, xxxxx ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  static onoff board_led_state = OFF;
  static uint16_t dt = 0;

  if ((get_oneshot_mods() && !has_oneshot_mods_timed_out())) {
      if(timer_elapsed(dt) > BLINK_BASE) {

        dt = timer_read();
        if(board_led_state == OFF) {
          ergodox_board_led_on();
          board_led_state = ON;
        } else {
          ergodox_board_led_off();
          board_led_state = OFF;
        }
      }
  } else {
      if(layer == BASE) {
        ergodox_board_led_off();
        board_led_state = OFF;
      } else {
       ergodox_board_led_on();
        board_led_state = ON;
      }
  }
};

bool process_record_user(uint16_t kc, keyrecord_t *rec) {
    uint8_t layer = biton32(layer_state);

    // Swap the numbers and symbols on the base layer if no other modifier is pressed
    if (!(keyboard_report->mods & (~MOD_BIT(KC_LSFT) & ~MOD_BIT(KC_RSFT))) && //    modifier being pressed
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
