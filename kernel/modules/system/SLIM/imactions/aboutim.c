#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void aboutim(char c, int userinputmode) {
	if (userinputmode == ABOUT_APP_ID) {
		//about main page
		if (c == '<') {
			//Do nothing
		} else if (c == '>') {
			about(2);
		} else if (c == 'm') {
			main_menu(1, ABOUT_APP_ID_FR, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_TW) {
		//about second page
		if (c == '<') {
			about(1);
		} else if (c == '>') {
			//Do nothing
		} else if (c == 'm') {
			main_menu(1, ABOUT_APP_ID_FR, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_TH) {
		//about about screen
		if (c == 'm') {
			main_menu(1, ABOUT_APP_ID_SV, 2);
		}
	} else if (userinputmode == ABOUT_APP_ID_FR) {
		//about menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, ABOUT_APP_ID_FV, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_FV) {
		//about menu if about is selected
		if (c == '\n') {
			app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		} else if (c == '{') {
			main_menu(1, ABOUT_APP_ID_FR, 1);
		} else if (c == '}') {
			main_menu(3, ABOUT_APP_ID_SX, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_SX) {
		//about menu if back is selected
		if (c == '\n') {
			about(1);
		} else if (c == '{') {
			main_menu(2, ABOUT_APP_ID_FV, 1);
		}
	} else if (userinputmode == ABOUT_APP_ID_SV) {
		//about about menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, ABOUT_APP_ID_EI, 2);
		}
	} else if (userinputmode == ABOUT_APP_ID_EI) {
		//about about menu if back is selected
		if (c == '\n') {
			app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		} else if (c == '{') {
			main_menu(1, ABOUT_APP_ID_SV, 2);
		} else if (c == '}') {
			main_menu(3, ABOUT_APP_ID_NI, 2);
		}
	} else if (userinputmode == ABOUT_APP_ID_NI) {
		//about about menu if back to app is selected
		if (c == '\n') {
			about(1);
		} else if (c == '{') {
			main_menu(2, ABOUT_APP_ID_EI, 2);
		}
	} else {
		//todo: send error box
		warn("Error occured in aboutim, unexpected UIM");
	}
}