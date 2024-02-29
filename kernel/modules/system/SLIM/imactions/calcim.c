#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void calcim(char c, int userinputmode) {
	if (userinputmode == CALC_APP_ID_FR) {
		//calc screen
		if (c == 'm') {
			main_menu(1, CALC_APP_ID_SV, 1);
		} else if (c == '\n') {
			tui_reset();
		}
	} else if (userinputmode == CALC_APP_ID_SX) {
		//calc about screen
		if (c == 'm') {
			main_menu(1, CALC_APP_ID_TN, 2);
		}
	} else if (userinputmode == CALC_APP_ID_SV) {
		//calc menu if Exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, CALC_APP_ID_EI, 1);
		}
	} else if (userinputmode == CALC_APP_ID_EI) {
		//calc menu if about is selected
		if (c == '\n') {
			app_info("Calculator\nthe calculator app for MINIOS\nVersion 1.0.0", CALC_APP_ID_SX, 1);
		} else if (c == '{') {
			main_menu(1, CALC_APP_ID_SV, 1);
		} else if (c == '}') {
			main_menu(3, CALC_APP_ID_NI, 1);
		}
	} else if (userinputmode == CALC_APP_ID_NI) {
		//calc menu if back is selected
		if (c == '\n') {
			textbox("Enter the first number", "", CALC_APP_ID);
		} else if (c == '{') {
			main_menu(2, CALC_APP_ID_EI, 1);
		}
	} else if (userinputmode == CALC_APP_ID_TN) {
		//calc about menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, CALC_APP_ID_EL, 2);
		}
	} else if (userinputmode == CALC_APP_ID_EL) {
		//calc about menu if back is selected
		if (c == '\n') {
			app_info("Calculator\nthe calculator app for MINIOS\nVersion 1.0.0", CALC_APP_ID_SX, 1);
		} else if (c == '{') {
			main_menu(1, CALC_APP_ID_TN, 2);
		} else if (c == '}') {
			main_menu(3, CALC_APP_ID_TL, 2);
		}
	} else if (userinputmode == CALC_APP_ID_TL) {
		//calc about menu if back to app is selected
		if (c == '\n') {
			textbox("Enter the first number", "", CALC_APP_ID);
		} else if (c == '{') {
			main_menu(2, CALC_APP_ID_EL, 2);
		}
	} else {
		//todo: send error box
		warn("Error occured in calcim, unexpected UIM");
	}
}