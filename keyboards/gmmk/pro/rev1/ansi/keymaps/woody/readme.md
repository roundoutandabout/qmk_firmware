# roundoutandabout's GMMK Pro layout

* **Differences compared to [stock](https://config.qmk.fm/#/gmmk/pro/rev1/ansi/LAYOUT) layout:**
	* Knob [functions](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/rev1/ansi/keymaps/stickandgum):
		* Default: Volume Up/Down
		* Ctrl: Mouse Wheel Down/Up
		* Shift: Page Down/Up
	* Caps lock indicator:
		* Side Light Rainbow Indicators and Left-side RED Indicators
			* Has a bug: Caps light don't turn off properly when Heatmap and Matrix FrameBuffer effects are enabled
	* Enable [reactive](https://docs.qmk.fm/#/feature_rgb_matrix?id=additional-configh-options) RGB effects
	* RGB timeout 5 minutes
	* Disable RGB when USB suspended (e.g. when PC goes to sleep)
	* [VIA](https://www.caniusevia.com/docs/configuring_qmk/) support enabled

* Compile and flash this firmware:
	* Install `qmk`, e.g.:
		* `$ sudo pacman -S qmk`
	* `$ git clone --recurse-submodules git@github.com:roundoutandabout/qmk_firmware.git`
	* `$ cd qmk_firmware`
	* `$ git checkout woodys_keymap_gmmk_pro`
	* `$ qmk compile -kb gmmk/pro/rev1/ansi -km woody`
	* Put your GMMK Pro in bootloader mode (https://docs.qmk.fm/#/newbs_flashing)
	* `$ qmk flash`

---

![Layout Image Layer 0](https://i.imgur.com/aOjgBho.png)


![Layout Image Layer 1](https://i.imgur.com/K6oiyxc.png)
