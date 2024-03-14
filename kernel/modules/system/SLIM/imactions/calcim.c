#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/debug.h>

void calcim(char c, int userinputmode) {
	if (userinputmode == CALC_APP_ID) {
		//calc screen
		if (c == MENU_KEY) {
			main_menu(1, CALC_APP_ID_TH, 1);
		} else if (c == '0') {
			calc(CALC_APP_ID, 0);
		} else if (c == '1') {
			calc(CALC_APP_ID, 1);
		} else if (c == '2') {
			calc(CALC_APP_ID, 2);
		} else if (c == '3') {
			calc(CALC_APP_ID, 3);
		} else if (c == '4') {
			calc(CALC_APP_ID, 4);
		} else if (c == '5') {
			calc(CALC_APP_ID, 5);
		} else if (c == '6') {
			calc(CALC_APP_ID, 6);
		} else if (c == '7') {
			calc(CALC_APP_ID, 7);
		} else if (c == '8') {
			calc(CALC_APP_ID, 8);
		} else if (c == '9') {
			calc(CALC_APP_ID, 9);
		} else if (c == 'a') {
			calc(CALC_APP_ID, 10);
		} else if (c == 'm') {
			calc(CALC_APP_ID, 11);
		} else if (c == 's') {
			calc(CALC_APP_ID, 12);
		} else if (c == 'd') {
			calc(CALC_APP_ID, 13);
		} else if (c == 'c') {
			calc(CALC_APP_ID, 14);
		} else if (c == 'n') {
			calc(CALC_APP_ID, 15);
		} else if (c == ENTER_KEY) {
			calc(CALC_APP_ID, 16);
		} 
	} else if (userinputmode == CALC_APP_ID_TW) {
		//calc about screen
		if (c == MENU_KEY) {
			main_menu(1, CALC_APP_ID_SX, 2);
		}
	} else if (userinputmode == CALC_APP_ID_TH) {
		//calc menu if Exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, CALC_APP_ID_FR, 1);
		}
	} else if (userinputmode == CALC_APP_ID_FR) {
		//calc menu if about is selected
		if (c == ENTER_KEY) {
			app_info("Calculator\nthe calculator app for MINIOS\nVersion 1.0.0", CALC_APP_ID_TW, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, CALC_APP_ID_TH, 1);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, CALC_APP_ID_FV, 1);
		}
	} else if (userinputmode == CALC_APP_ID_FV) {
		//calc menu if back is selected
		if (c == ENTER_KEY) {
			calc(CALC_APP_ID, 22);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, CALC_APP_ID_FR, 1);
		}
	} else if (userinputmode == CALC_APP_ID_SX) {
		//calc about menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, CALC_APP_ID_SV, 2);
		}
	} else if (userinputmode == CALC_APP_ID_SV) {
		//calc about menu if back is selected
		if (c == ENTER_KEY) {
			app_info("Calculator\nthe calculator app for MINIOS\nVersion 1.0.0", CALC_APP_ID_SX, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, CALC_APP_ID_SX, 2);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, CALC_APP_ID_EI, 2);
		}
	} else if (userinputmode == CALC_APP_ID_EI) {
		//calc about menu if back to app is selected
		if (c == ENTER_KEY) {
			calc(CALC_APP_ID, 0);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, CALC_APP_ID_SV, 2);
		}
	} else {
		//report the error to end user
		warning_box("IM Error", "Error occured in calcim, unexpected UIM");
	}
}