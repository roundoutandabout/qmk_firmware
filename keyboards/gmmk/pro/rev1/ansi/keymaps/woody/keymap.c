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


#ifdef ENCODER_ENABLE
/* Knob (rotary encoder) */
bool encoder_update_user(uint8_t index, bool clockwise) {
	// https://beta.docs.qmk.fm/using-qmk/simple-keycodes/feature_advanced_keycodes#alt-escape-for-alt-tab-id-alt-escape-for-alt-tab
	if (get_mods() & MOD_MASK_SHIFT) {
		uint8_t mod_state = get_mods();
		unregister_mods(MOD_MASK_SHIFT);
		if (clockwise) {
			tap_code(KC_PGDN);
		} else {
			tap_code(KC_PGUP);
		}
		set_mods(mod_state);
	} else if (get_mods() & MOD_MASK_CTRL) { // If CTRL is held
		uint8_t mod_state = get_mods(); // Store all  modifiers that are held
		unregister_mods(MOD_MASK_CTRL); // Immediately unregister the CRTL key (don't send CTRL-PgDn) - del_mods doesn't work here (not immediate)
		if (clockwise) {
			#ifdef MOUSEKEY_ENABLE   // If using the mouse scroll - make sure MOUSEKEY is enabled
			tap_code(KC_MS_WH_DOWN);
			#else
			tap_code(KC_VOLU);
			#endif
		} else {
			#ifdef MOUSEKEY_ENABLE
			tap_code(KC_MS_WH_UP);
			#else
			tap_code(KC_VOLD);
			#endif
		}
		set_mods(mod_state); // Add back in the CTRL key - so ctrl-key will work if ctrl was never released after paging.
	} else if (clockwise) { // All else volume.
		tap_code(KC_VOLU);
	} else {
		tap_code(KC_VOLD);
	}
	//return true; //set to return false to counteract enabled encoder in pro.c
	return false;
}
#endif //ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE
static void set_rgb_caps_leds_on(void);
static void set_rgb_caps_leds_off(void);

/* Enable the caps lock LED indicator */
bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        set_rgb_caps_leds_on();
    } else {
      if (rgb_matrix_get_flags() == LED_FLAG_NONE){
        set_rgb_caps_leds_off();
      }
    }
    return false;
}

// RGB led number layout, function of the key

//  67, led 01   0, ESC    6, F1      12, F2      18, F3   23, F4   28, F5      34, F6   39, F7   44, F8      50, F9   56, F10   61, F11    66, F12    69, Prt       Rotary(Mute)   68, led 12
//  70, led 02   1, ~      7, 1       13, 2       19, 3    24, 4    29, 5       35, 6    40, 7    45, 8       51, 9    57, 0     62, -_     78, (=+)   85, BackSpc   72, Home       71, led 13
//  73, led 03   2, Tab    8, Q       14, W       20. E    25, R    30, T       36, Y    41, U    46, I       52, O    58, P     63, [{     89, ]}     93, \|        75, PgUp       74, led 14
//  76, led 04   3, Caps   9, A       15, S       21, D    26, F    31, G       37, H    42, J    47, K       53, L    59, ;:    64, '"                96, Enter     86, PgDn       77, led 15
//  80, led 05   4, Sh_L   10, Z      16, X       22, C    27, V    32, B       38, N    43, M    48, ,<      54, .<   60, /?               90, Sh_R   94, Up        82, End        81, led 16
//  83, led 06   5, Ct_L   11,Win_L   17, Alt_L                     33, SPACE                     49, Alt_R   55, FN             65, Ct_R   95, Left   97, Down      79, Right      84, led 17
//  87, led 07                                                                                                                                                                      88, led 18
//  91, led 08                                                                                                                                                                      92, led 19

static void set_rgb_caps_leds_on() {
        rgb_matrix_set_color(0, 255, 0, 0);       //Escape Key
        rgb_matrix_set_color(3, 255, 0, 0);       //capslock key
        rgb_matrix_set_color(5, 255, 0, 0);       //Left CTRL key
        rgb_matrix_set_color(67, 255, 0, 0);      //Left LED 01
        rgb_matrix_set_color(68, 255, 0, 0);      //Right LED 12
        rgb_matrix_set_color(70, 255, 127, 0);    //Left LED 02
        rgb_matrix_set_color(71, 255, 127, 0);    //Right LED 13
        rgb_matrix_set_color(73, 255, 255, 0);    //Left LED 03
        rgb_matrix_set_color(74, 255, 255, 0);    //Right LED 14
        rgb_matrix_set_color(76, 0, 255, 0);      //Left LED 04
        rgb_matrix_set_color(77, 0, 255, 0);      //Right LED 15
        rgb_matrix_set_color(80, 0, 0, 255);      //Left LED 05
        rgb_matrix_set_color(81, 0, 0, 255);      //Right LED 16
        rgb_matrix_set_color(83, 46, 43, 95);     //Left LED 06
        rgb_matrix_set_color(84, 46, 43, 95);     //Right LED 17
        rgb_matrix_set_color(87, 139, 0, 255);    //Left LED 07
        rgb_matrix_set_color(88, 139, 0, 255);    //Right LED 18
        rgb_matrix_set_color(91, 255, 255, 255);  //Left LED 08
        rgb_matrix_set_color(92, 255, 255, 255);  //Right LED 19
}

static void set_rgb_caps_leds_off() {
        rgb_matrix_set_color(0,  0, 0, 0); //Escape Key
        rgb_matrix_set_color(3,  0, 0, 0); //capslock key
        rgb_matrix_set_color(5,  0, 0, 0); //Left CTRL key
        rgb_matrix_set_color(67, 0, 0, 0); //Left LED 01
        rgb_matrix_set_color(68, 0, 0, 0); //Right LED 12
        rgb_matrix_set_color(70, 0, 0, 0); //Left LED 02
        rgb_matrix_set_color(71, 0, 0, 0); //Right LED 13
        rgb_matrix_set_color(73, 0, 0, 0); //Left LED 03
        rgb_matrix_set_color(74, 0, 0, 0); //Right LED 14
        rgb_matrix_set_color(76, 0, 0, 0); //Left LED 04
        rgb_matrix_set_color(77, 0, 0, 0); //Right LED 15
        rgb_matrix_set_color(80, 0, 0, 0); //Left LED 05
        rgb_matrix_set_color(81, 0, 0, 0); //Right LED 16
        rgb_matrix_set_color(83, 0, 0, 0); //Left LED 06
        rgb_matrix_set_color(84, 0, 0, 0); //Right LED 17
        rgb_matrix_set_color(87, 0, 0, 0); //Left LED 07
        rgb_matrix_set_color(88, 0, 0, 0); //Right LED 18
        rgb_matrix_set_color(91, 0, 0, 0); //Left LED 08
        rgb_matrix_set_color(92, 0, 0, 0); //Right LED 19
}

#endif // RGB_MATRIX_ENABLE