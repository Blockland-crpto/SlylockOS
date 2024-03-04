#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void powerim(char c, int userinputmode) {
	if (userinputmode == POWER_APP_ID) {		
		if (c == ENTER_KEY) {
			shutdown();
		} else if (c == ARROW_KEY_DOWN) {
			power_menu(2, POWER_APP_ID_TW);
		}
	} else if (userinputmode == POWER_APP_ID_TW) {
		if (c == ENTER_KEY) {
			reboot();
		} else if (c == ARROW_KEY_DOWN) {
			power_menu(3, POWER_APP_ID_TH);
		} else if (c == ARROW_KEY_UP) {
			power_menu(1, POWER_APP_ID);
		}
	} else if (userinputmode == POWER_APP_ID_TH) {
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_UP) {
			power_menu(2, POWER_APP_ID_TW);
		}
	} else {
		//report the error to end user
		warning_box("IM Error", "Error occured in powerim, unexpected UIM");
	}
}