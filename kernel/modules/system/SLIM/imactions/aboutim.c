#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/debug.h>

void aboutim(char c, int userinputmode) {
	if (userinputmode == ABOUT_APP_ID) {
		//about main page
		if (c == ARROW_KEY_LEFT) {
			//Do nothing
		} else if (c == ARROW_KEY_RIGHT) {
			about(2);
		} else if (c == MENU_KEY) {
			main_menu(1, ABOUT_APP_ID_FR, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_TW) {
		//about second page
		if (c == ARROW_KEY_LEFT) {
			about(1);
		} else if (c == ARROW_KEY_RIGHT) {
			//Do nothing
		} else if (c == MENU_KEY) {
			main_menu(1, ABOUT_APP_ID_FR, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_TH) {
		//about about screen
		if (c == MENU_KEY) {
			main_menu(1, ABOUT_APP_ID_SV, 2);
		}
	} else if (userinputmode == ABOUT_APP_ID_FR) {
		//about menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, ABOUT_APP_ID_FV, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_FV) {
		//about menu if about is selected
		if (c == ENTER_KEY) {
			app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, ABOUT_APP_ID_FR, 1);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, ABOUT_APP_ID_SX, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_SX) {
		//about menu if back is selected
		if (c == ENTER_KEY) {
			about(1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, ABOUT_APP_ID_FV, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_SV) {
		//about about menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, ABOUT_APP_ID_EI, 2);
		}
	} else if (userinputmode == ABOUT_APP_ID_EI) {
		//about about menu if back is selected
		if (c == ENTER_KEY) {
			app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, ABOUT_APP_ID_SV, 2);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, ABOUT_APP_ID_NI, 2);
		}
	} else if (userinputmode == ABOUT_APP_ID_NI) {
		//about about menu if back to app is selected
		if (c == ENTER_KEY) {
			about(1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, ABOUT_APP_ID_EI, 2);
		}
	} else {
		//report the error to end user
		warning_box("IM Error", "Error occured in aboutim, unexpected UIM");
	}
}