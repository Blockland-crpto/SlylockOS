#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void homeim(char c, int userinputmode) {
	if (userinputmode == HOME_APP_ID) {
		//home menu when poweroptions is selected
		if (c == '\n') {
			power_menu(1, POWER_APP_ID);
		} else if (c == '}') {
			main_menu(2, HOME_APP_ID_TW, 3);
		}
	} else if (userinputmode == HOME_APP_ID_TW) {
		//home menu when applicatons is selected
		if (c == '\n') {
			app_menu(1, SHELL_APP_ID_TH);
		} else if (c == '}') {
			main_menu(3, HOME_APP_ID_TH, 3);
		} else if (c == '{') {
			main_menu(1, HOME_APP_ID, 3);
		}
	} else if (userinputmode == HOME_APP_ID_TH) {
		//home menu when back is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '{') {
			main_menu(2, HOME_APP_ID_TW, 3);
		}
	} else {
		//todo: make warning box
		warn("Error occured in homeim, unexpected UIM");
	}
}