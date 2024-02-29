#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void catim(char c, int userinputmode) {
	if (userinputmode == CAT_APP_ID) {
		//cat screen
		if (c == 'm') {
			main_menu(1, CAT_APP_ID_TH, 1);
		}
	} else if (userinputmode == CAT_APP_ID_TW) {
		//about cat screen
		if (c == 'm') {
			main_menu(1, CAT_APP_ID_SX, 2);
		}
	} else if (userinputmode == CAT_APP_ID_TH) {
		//cat menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, CAT_APP_ID_FR, 1);
		}
	} else if (userinputmode == CAT_APP_ID_FR) {
		//cat menu if about is selected
		if (c == '\n') {
			app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		} else if (c == '{') {
			main_menu(1, CAT_APP_ID_TH, 1);
		} else if (c == '}') {
			main_menu(3, CAT_APP_ID_FV, 1);
		}
	} else if (userinputmode == CAT_APP_ID_FV) {
		//cat menu if back is selected
		if (c == '\n') {
			textbox("cat", "Enter the file location", CAT_APP_ID);
		} else if (c == '{') {
			main_menu(2, CAT_APP_ID_FR, 1);
		}
	} else if (userinputmode == CAT_APP_ID_SX) {
		//cat about menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, CAT_APP_ID_SV, 2);
		}
	} else if (userinputmode == CAT_APP_ID_SV) {
		//cat about menu if back is selected
		if (c == '\n') {
			app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		} else if (c == '{') {
			main_menu(1, CAT_APP_ID_SX, 2);
		} else if (c == '}') {
			main_menu(3, CAT_APP_ID_EI, 2);
		}
	} else if (userinputmode == CAT_APP_ID_EI) {
		//cat about menu if back to app is selected
		if (c == '\n') {
			//todo: go back to the original page opened
			textbox("cat", "Enter the file location", CAT_APP_ID);
		} else if (c == '{') {
			main_menu(2, CAT_APP_ID_SV, 2);
		}
	} else {
		//todo: send error box
		warn("Error occured in catim, unexpected UIM");
	}
}