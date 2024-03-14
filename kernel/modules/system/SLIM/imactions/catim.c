#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/debug.h>

void catim(char c, int userinputmode) {
	if (userinputmode == CAT_APP_ID) {
		//cat screen
		if (c == MENU_KEY) {
			main_menu(1, CAT_APP_ID_TH, 1);
		}
	} else if (userinputmode == CAT_APP_ID_TW) {
		//about cat screen
		if (c == MENU_KEY) {
			main_menu(1, CAT_APP_ID_SX, 2);
		}
	} else if (userinputmode == CAT_APP_ID_TH) {
		//cat menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, CAT_APP_ID_FR, 1);
		}
	} else if (userinputmode == CAT_APP_ID_FR) {
		//cat menu if about is selected
		if (c == ENTER_KEY) {
			app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, CAT_APP_ID_TH, 1);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, CAT_APP_ID_FV, 1);
		}
	} else if (userinputmode == CAT_APP_ID_FV) {
		//cat menu if back is selected
		if (c == ENTER_KEY) {
			cat(lastcatfile);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, CAT_APP_ID_FR, 1);
		}
	} else if (userinputmode == CAT_APP_ID_SX) {
		//cat about menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, CAT_APP_ID_SV, 2);
		}
	} else if (userinputmode == CAT_APP_ID_SV) {
		//cat about menu if back is selected
		if (c == ENTER_KEY) {
			app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, CAT_APP_ID_SX, 2);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, CAT_APP_ID_EI, 2);
		}
	} else if (userinputmode == CAT_APP_ID_EI) {
		//cat about menu if back to app is selected
		if (c == ENTER_KEY) {
			//todo: go back to the original page opened
			cat(lastcatfile);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, CAT_APP_ID_SV, 2);
		}
	} else {
		//report the error to end user
		warning_box("IM Error", "Error occured in catim, unexpected UIM");
	}
}