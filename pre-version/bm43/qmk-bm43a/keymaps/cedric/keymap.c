/* Copyright 2020 Stefano Maragò
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.666666666
 */
#include QMK_KEYBOARD_H

enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR = SAFE_RANGE
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FOO:
            if (record->event.pressed) {
				SEND_STRING("plop");
            }
            return false;
    }

    return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 12+11+11+9
    [0] = LAYOUT(                                                                                          //
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,                       //
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT,                              //
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_UP, KC_DOT,                         //
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(1), MO(2), KC_LEFT, KC_DOWN, KC_RGHT                         //
        ),                                                                                                 //
    [1] = LAYOUT(                                                                                          //
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,                        //
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  //
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCLN, KC_QUOT, KC_PGUP, KC_SLSH, //
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_HOME, KC_PGDN, KC_END                       //
        ),
    [2] = LAYOUT(                                                                              //
        KC_ESC , KC_F1  , KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_DEL, //
        KC_PSCR, KC_SCRL, KC_BRK,  KC_NO, UC(0x20AC), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TT(3),           //
        KC_NO  , KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     //
        KC_NO, KC_NO  , KC_NO, RGB_TOG, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO                      //
        ),
    [3] = LAYOUT(                                                                                          //
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0),              //
        KC_NO, RGB_SPI, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_TRNS, //
        RGB_TOG, RGB_SPD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,           //
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD                             //
        ),
};
