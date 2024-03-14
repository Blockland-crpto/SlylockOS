#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/debug.h>

void settim(char c, int userinputmode) {
	if (userinputmode == SETT_APP_ID) {
		//sett screen
		if (c == ARROW_KEY_RIGHT) {
			sett(SETT_APP_ID, 1);
		} else if (c == ARROW_KEY_LEFT) {
			sett(SETT_APP_ID, 2);
		} else if (c == MENU_KEY) {
			main_menu(1, SETT_APP_ID_TW, 1); 
		}
	} else if (userinputmode == SETT_APP_ID_TW) {
		//sett menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, SETT_APP_ID_TH, 1);
		}
	} else if (userinputmode == SETT_APP_ID_TH) {
		//sett menu if about is selected
		if (c == ENTER_KEY) {
			app_info("Settings\nthe settings app for MINIOS\nVersion 1.0.0", SETT_APP_ID_FV, 1);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, SETT_APP_ID_FR, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, SETT_APP_ID_TW, 1);
		}
	} else if (userinputmode == SETT_APP_ID_FR) {
		//sett menu if back is selected
		if (c == ENTER_KEY) {
			sett(SETT_APP_ID, 0);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, SETT_APP_ID_TH, 1);
		}
	} else if (userinputmode == SETT_APP_ID_FV) {
		//sett about menu
		if (c == MENU_KEY) {
			main_menu(1, SETT_APP_ID_SX, 2);
		}
	} else if (userinputmode == SETT_APP_ID_SX) {
		//sett about menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, SETT_APP_ID_SV, 2);
		}
	} else if (userinputmode == SETT_APP_ID_SV) {
		//sett about menu if back is selected
		if (c == ENTER_KEY) {
			app_info("Settings\nthe settings app for MINIOS\nVersion 1.0.0", SETT_APP_ID_FV, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, SETT_APP_ID_SX, 2);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, SETT_APP_ID_EI, 2);
		}
	} else if (userinputmode == SETT_APP_ID_EI) {
		//sett about menu if back to app is selected
		if (c == ENTER_KEY) {
			sett(SETT_APP_ID, 0);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, SETT_APP_ID_SV, 2);
		}
	}
}