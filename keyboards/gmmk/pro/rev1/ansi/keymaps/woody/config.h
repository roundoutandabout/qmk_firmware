#pragma once

#ifdef RGB_MATRIX_ENABLE
	#define RGB_DISABLE_WHEN_USB_SUSPENDED
	#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // Heatmap, Rain
	#define RGB_MATRIX_KEYPRESSES // REACTIVE, SPLASH modes
	#define RGB_DISABLE_TIMEOUT 300000      // 5 minutes (5 * 60 * 1000ms)
#endif
