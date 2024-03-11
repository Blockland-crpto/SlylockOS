#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void homeim(char c, int userinputmode) {
	if (userinputmode == HOME_APP_ID) {
		//home menu when poweroptions is selected
		if (c == ENTER_KEY) {
			power_menu(1, POWER_APP_ID);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, HOME_APP_ID_TW, 3);
		}
	} else if (userinputmode == HOME_APP_ID_TW) {
		//home menu when applicatons is selected
		if (c == ENTER_KEY) {
			app_menu(1, SHELL_APP_ID_TH);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, HOME_APP_ID_TH, 3);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, HOME_APP_ID, 3);
		}
	} else if (userinputmode == HOME_APP_ID_TH) {
		//home menu when back is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, HOME_APP_ID_TW, 3);
		}
	} else {
		//report the error to end user
		warning_box("IM Error", "Error occured in homeim, unexpected UIM");
	}
}