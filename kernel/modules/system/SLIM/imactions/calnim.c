#include <system/im.h>
#include <shell/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <libsdk.h>
#include <system/debug.h>

void calnim(char c, int userinputmode) {
	if (userinputmode == CALN_APP_ID) {
		//caln screen
		if (c == MENU_KEY) {
			main_menu(1, CALN_APP_ID_TW, 1);
		} else if (c == ARROW_KEY_LEFT) {
			caln(CALN_APP_ID, 1);
		} else if (c == ARROW_KEY_RIGHT) {
			caln(CALN_APP_ID, 2);
		}
	} else if (userinputmode == CALN_APP_ID_TW) {
		//caln menu if Exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, CALN_APP_ID_TH, 1);
		}
	} else if (userinputmode == CALN_APP_ID_TH) {
		//caln menu if about is selected
		if (c == ENTER_KEY) {
			app_info("Calendar\nthe calendar app for SlylockOS\nVersion 1.0.0", CALN_APP_ID_FV, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, CALN_APP_ID_TW, 1);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, CALN_APP_ID_FR, 1);
		}
	} else if (userinputmode == CALN_APP_ID_FR) {
		//caln menu if back is selected
		if (c == ENTER_KEY) {
			caln(CALN_APP_ID, 0);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, CALN_APP_ID_TH, 1);
		}
	} else if (userinputmode == CALN_APP_ID_FV) {
		//caln about
		if (c == MENU_KEY) {
			main_menu(1, CALN_APP_ID_SX, 2);
		}
	} else if (userinputmode == CALN_APP_ID_SX) {
		//caln about menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, CALN_APP_ID_SV, 2);
		}
	} else if (userinputmode == CALN_APP_ID_SV) {
		//caln about menu if back is selected
		if (c == ENTER_KEY) {
			app_info("Calendar\nthe calendar app for SlylockOS\nVersion 1.0.0", CALN_APP_ID_FV, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, CALN_APP_ID_SX, 2);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, CALN_APP_ID_EI, 2);
		}
	} else if (userinputmode == CALN_APP_ID_EI) {
		//caln about menu if back to app is selected
		if (c == ENTER_KEY) {
			caln(CALN_APP_ID, 0);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, CALN_APP_ID_SV, 2);
		}
	}
}