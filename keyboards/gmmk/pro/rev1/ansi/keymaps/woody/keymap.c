/* Copyright 2021 Oleksii Zolotarevskyi
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_MUTE, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_END, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
	[1] = LAYOUT(KC_TRNS, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUI, RGB_VAI, RGB_SAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS, KC_TRNS, RGB_HUD, RGB_VAD, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPD, RGB_RMOD, RGB_SPI)
};

bool encoder_update_user(uint8_t index, bool clockwise) { /* Enable knob */
	if (clockwise) {
		tap_code(KC_VOLU);
	} else {
		tap_code(KC_VOLD);
	}
	return true;
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        if (!rgb_matrix_is_enabled()) {
            /* Turn ON the RGB Matrix for CAPS LOCK */
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_enable();
        }
    } else if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        /* RGB Matrix was only ON because of CAPS LOCK. Turn it OFF. */
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgb_matrix_disable();
    }
    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	/* Enable Caps Lock LEDs*/
	if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
		rgb_matrix_set_color(LED_CAPS, RGB_WHITE);
		rgb_matrix_set_color(LED_L3, RGB_WHITE);
		rgb_matrix_set_color(LED_L4, RGB_WHITE);
		rgb_matrix_set_color(LED_L5, RGB_WHITE);
		rgb_matrix_set_color(LED_L6, RGB_WHITE);
		rgb_matrix_set_color(LED_R3, RGB_WHITE);
		rgb_matrix_set_color(LED_R4, RGB_WHITE);
		rgb_matrix_set_color(LED_R5, RGB_WHITE);
		rgb_matrix_set_color(LED_R6, RGB_WHITE);
	}
	return false;
}