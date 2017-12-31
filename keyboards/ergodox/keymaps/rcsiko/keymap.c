#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "led.h"
#include "keymap.h"
#include "timer.h"

// Custom 'KEYMAP' macro for more visual keymap format
#undef KEYMAP
#define KEYMAP(                                                       \
                                                                      \
    k00,k01,k02,k03,k04,k05,k06,       k07,k08,k09,k0A,k0B,k0C,k0D,   \
    k10,k11,k12,k13,k14,k15,k16,       k17,k18,k19,k1A,k1B,k1C,k1D,   \
    k20,k21,k22,k23,k24,k25,               k28,k29,k2A,k2B,k2C,k2D,   \
    k30,k31,k32,k33,k34,k35,k36,       k37,k38,k39,k3A,k3B,k3C,k3D,   \
    k40,k41,k42,k43,k44,                       k49,k4A,k4B,k4C,k4D,   \
                        k55,k56,       k57,k58,                       \
                            k54,       k59,                           \
                    k53,k52,k51,       k5C,k5B,k5A )                  \
   {                                                                  \
    { KC_##k00, KC_##k10, KC_##k20, KC_##k30, KC_##k40, KC_NO },      \
    { KC_##k01, KC_##k11, KC_##k21, KC_##k31, KC_##k41, KC_##k51 },   \
    { KC_##k02, KC_##k12, KC_##k22, KC_##k32, KC_##k42, KC_##k52 },   \
    { KC_##k03, KC_##k13, KC_##k23, KC_##k33, KC_##k43, KC_##k53 },   \
    { KC_##k04, KC_##k14, KC_##k24, KC_##k34, KC_##k44, KC_##k54 },   \
    { KC_##k05, KC_##k15, KC_##k25, KC_##k35, KC_NO,    KC_##k55 },   \
    { KC_##k06, KC_##k16, KC_NO,    KC_##k36, KC_NO,    KC_##k56 },   \
                                                                      \
    { KC_##k07, KC_##k17, KC_NO,    KC_##k37, KC_NO,    KC_##k57 },   \
    { KC_##k08, KC_##k18, KC_##k28, KC_##k38, KC_NO,    KC_##k58 },   \
    { KC_##k09, KC_##k19, KC_##k29, KC_##k39, KC_##k49, KC_##k59 },   \
    { KC_##k0A, KC_##k1A, KC_##k2A, KC_##k3A, KC_##k4A, KC_##k5A },   \
    { KC_##k0B, KC_##k1B, KC_##k2B, KC_##k3B, KC_##k4B, KC_##k5B },   \
    { KC_##k0C, KC_##k1C, KC_##k2C, KC_##k3C, KC_##k4C, KC_##k5C },   \
    { KC_##k0D, KC_##k1D, KC_##k2D, KC_##k3D, KC_##k4D, KC_NO }       \
   }

// Layers
#define BASE 0
#define NAV  1
#define NUM  2
#define NUMP 3

// Custom keys
#define KC_____       KC_NO
#define KC_xxxx       KC_TRNS

#define KC_C_ESC      CTL_T(KC_ESC)
#define KC_C_QUOT     CTL_T(KC_QUOT)
#define KC_T_NUM      TG(NUM)
#define KC_NUM        LT(NUM, KC_SPC)
#define KC_NAV        LT(NAV, KC_SCLN)
#define KC_LGAC       LCAG(KC_NO)

#define OSM_LCTL      OSM(MOD_LCTL)
#define OSM_LALT      OSM(MOD_LALT)
#define OSM_LSFT      OSM(MOD_LSFT)

#define KC_COPY       LCTL(KC_C)
#define KC_PASTE      LCTL(KC_V)
#define KC_UNDO       LCTL(KC_Z)
#define KC_REDO       LCTL(LSFT(KC_Z))

#define KC_SPOTLT                      LGUI(KC_SPC)
#define KC_ITERM                       LALT(KC_SPC)
#define KC_PREV_TAB                    LGUI(LSFT(KC_LBRC))
#define KC_NEXT_TAB                    LGUI(LSFT(KC_RBRC))
#define KC_PREV_WS                     LGUI(LALT(LCTL(KC_LBRC)))
#define KC_NEXT_WS                     LGUI(LALT(LCTL(KC_RBRC)))

#define BLINK_BASE  150U // timer threshold for blinking

static bool gSwapNumbersAndSymbols = true;
typedef enum onoff_t {OFF, ON} onoff;

enum own_keys {
  SWAP_SYMS = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Base Layer
  *
  * ,-----------------------------------------------------.           ,-----------------------------------------------------.
  * |    `~     |   !  |   @  |   #  |   $  |   %  |  F4  |           |NUMPAD|   ^  |   &  |   *  |   (  |   )  | Backspace |
  * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
  * |  Tab      |   Q  |   W  |   E  |   R  |   T  |  {   |           |   }  |   Y  |   U  |   I  |   O  |   P  |   \ |     |
  * |-----------+------+------+------+------+------|  [   |           |   ]  |------+------+------+------+------+-----------|
  * | ESC(CTRL) |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ; NAV| ' "/Ctrl  |
  * |-----------+------+------+------+------+------|  =   |           |   -  |------+------+------+------+------+-----------|
  * |   Shift   |   Z  |   X  |   C  |   V  |   B  |  +   |           |   _  |   N  |   M  |   ,  |   .  |  / ? |   Shift   |
  * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
  *     |       |      | LCtrl| LAlt | LGui |                                       | RAlt |      |      |      |  LGAC |
  *     `-----------------------------------'                                       `-----------------------------------'
  *                                         ,-------------.           ,-------------.
  *                                         |  Del |      |           |      | Ins  |
  *                                  ,------|------|------|           |------+------+------.
  *                                  |      |      |iTerm |           |      |      |      |
  *                                  |Space | Bspc |------|           |------|Space | Enter|
  *                                  |      |      |Spotl.|           |      | NUM  |      |
  *                                  `--------------------'           `--------------------'
  *
  */
  [BASE]= KEYMAP(
     GRV    ,1     ,2     ,3     ,4     ,5    ,F4                      ,T_NUM  ,6     ,7     ,8     ,9     ,0     ,BSPC
    ,TAB    ,Q     ,W     ,E     ,R     ,T    ,LBRC                    ,RBRC   ,Y     ,U     ,I     ,O     ,P     ,BSLS
    ,C_ESC  ,A     ,S     ,D     ,F     ,G                                     ,H     ,J     ,K     ,L     ,NAV   ,C_QUOT
    ,LSFT   ,Z     ,X     ,C     ,V     ,B    ,EQL                     ,MINS   ,N     ,M     ,COMM  ,DOT   ,SLSH  ,RSFT
    ,____   ,____  ,LCTL  ,LALT  ,LGUI                                                ,RALT  ,____  ,____  ,____  ,LGAC
                                        ,DEL  ,____                    ,____   ,INS
                                              ,ITERM                   ,____
                                ,SPC   ,BSPC  ,SPOTLT                  ,____   ,NUM   ,ENT
  ),

  /* Keymap 1: Navigation Layer
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |        |  F11 |  F12 |      |      |      |      |           |      |      | PgUp |  Up  | PgDn |      |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |------|           |------|      | Left | Down | Right|      |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
  // Navigation
  [NAV] = KEYMAP(
     xxxx  ,F1    ,F2    ,F3    ,F4    ,F5    ,xxxx             ,xxxx  ,F6    ,F7    ,F8    ,F9     ,F10   ,xxxx
    ,xxxx  ,F11   ,F12   ,xxxx  ,xxxx  ,xxxx  ,xxxx             ,xxxx  ,xxxx  ,PGUP  ,UP    ,PGDN   ,xxxx  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx                           ,xxxx  ,LEFT  ,DOWN  ,RIGHT  ,xxxx  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx             ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx   ,xxxx  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx                                         ,xxxx  ,xxxx  ,xxxx   ,xxxx  ,xxxx
                                       ,xxxx  ,xxxx             ,xxxx  ,xxxx
                                              ,xxxx             ,xxxx
                                ,xxxx  ,xxxx  ,xxxx             ,xxxx  ,xxxx   ,xxxx
    ),


  /* Keymap 4: Numpad and media keys
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |        |  F11 |  F12 |      |      |      |      |           | Next | Vol+ |  7   |  8   |  9   |  *   |        |
  * |--------+------+------+------+------+------|      |           | Song |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |------|           |------| Vol- |  4   |  5   |  6   |  +   |        |
  * |--------+------+------+------+------+------|      |           | Prev |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |           | Song | Mute |  1   |  2   |  3   |  /   |        |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |      |      |      |      |      |                                       |  .   |  0   |  .   |  -   | Play |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        |      |      |       |      |      |
  *                                 ,------|------|------|       |------+------+------.
  *                                 |      |      |      |       |      |      |      |
  *                                 |      |      |------        |------|      |      |
  *                                 |      |      |      |       |      |      |      |
  *                                 `--------------------'       `--------------------'
  */
  [NUM] = KEYMAP(
     xxxx  ,F1    ,F2    ,F3    ,F4    ,F5    ,xxxx             ,xxxx  ,F6    ,F7    ,F8  ,F9    ,F10   ,xxxx
    ,xxxx  ,F11   ,F12   ,xxxx  ,xxxx  ,xxxx  ,xxxx             ,MRWD  ,VOLU  ,P7    ,P8  ,P9    ,PAST  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx                           ,VOLD  ,P4    ,P5  ,P6    ,PPLS  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx             ,MFFD  ,MUTE  ,P3    ,P2  ,P1    ,PSLS  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx                                         ,PDOT  ,P0  ,PDOT  ,PMNS  ,MPLY
                                       ,xxxx  ,xxxx             ,xxxx  ,xxxx
                                              ,xxxx             ,xxxx
                                ,xxxx  ,xxxx  ,xxxx             ,xxxx  ,xxxx   ,xxxx
    ),

  /* Keymap 5: Numpad only
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |           |      |      |  7   |  8   |  9   |  *   |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |------|           |------|      |  4   |  5   |  6   |  +   |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |           |      |      |  1   |  2   |  3   |  /   |        |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |      |      |      |      |      |                                       |  .   |  0   |  .   |  -   |      |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        |      |      |       |      |      |
  *                                 ,------|------|------|       |------+------+------.
  *                                 |      |      |      |       |      |      |      |
  *                                 |      |      |------        |------|      |      |
  *                                 |      |      |      |       |      |      |      |
  *                                 `--------------------'       `--------------------'
  */
  [NUMP] = KEYMAP(
     xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx              ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx              ,xxxx  ,xxxx  ,P7    ,P8    ,P9    ,PAST  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx                            ,xxxx  ,P4    ,P5    ,P6    ,PPLS  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx              ,xxxx  ,xxxx  ,P3    ,P2    ,P1    ,PSLS  ,xxxx
    ,xxxx  ,xxxx  ,xxxx  ,xxxx  ,xxxx                                          ,PDOT  ,P0    ,PDOT  ,PMNS  ,xxxx
                                        ,xxxx  ,xxxx             ,xxxx  ,xxxx
                                               ,xxxx             ,xxxx
                                 ,xxxx  ,xxxx  ,xxxx             ,xxxx  ,xxxx   ,xxxx
    ),
};

qk_dual_role_action_t dual_role_keys[] = {
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
      if((layer != BASE && layer != NUMP) || keyboard_report->mods & MOD_BIT(KC_LSFT)) {
        ergodox_board_led_on();
        board_led_state = ON;
      } else {
       ergodox_board_led_off();
        board_led_state = OFF;
      }
  }

  if (layer == NUMP) {
    ergodox_right_led_1_on();
  } else {
    ergodox_right_led_1_off();
  }
};

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
