#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/debug.h>

void helpim(char c, int userinputmode) {
	if (userinputmode == HELP_APP_ID) {
		//help main page
		if (c == ARROW_KEY_LEFT) {
		  //Do nothing
		} else if (c == ARROW_KEY_RIGHT) {
		  avaliable_commands(2);
		} else if (c == MENU_KEY) {
		  main_menu(1, HELP_APP_ID_FR, 1);
		}
	} else if(userinputmode == HELP_APP_ID_TW) {
		//help second page
		if (c == ARROW_KEY_LEFT) {
		  avaliable_commands(1);
		} else if (c == ARROW_KEY_RIGHT) {
		  //Do nothing
		} else if (c == MENU_KEY) {
			main_menu(1, HELP_APP_ID_FR, 1);
		}
	} else if(userinputmode == HELP_APP_ID_TH) {
		//help about screen
		if (c == MENU_KEY) {
			main_menu(1, HELP_APP_ID_SV, 2);
		}
	} else if(userinputmode == HELP_APP_ID_FR) {
		//help menu
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, HELP_APP_ID_FV, 1);
		}

	} else if(userinputmode == HELP_APP_ID_FV) {
		//help menu if about is selected
		if (c == ENTER_KEY) {
			app_info("Help\nthe Help app for MINIOS\nVersion 1.0.0", HELP_APP_ID_TH, 2);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, HELP_APP_ID_FR, 1);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, HELP_APP_ID_SX, 1);
		}

	} else if(userinputmode == HELP_APP_ID_SX) {
		//help menu if back is selected
		if (c == ENTER_KEY) {
			avaliable_commands(1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, HELP_APP_ID_FV, 1);
		}

	} else if (userinputmode == HELP_APP_ID_SV) {
		//help about menu
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, HELP_APP_ID_EI, 2);
		}
	} else if (userinputmode == HELP_APP_ID_EI) {
		//help about menu if back is selected
		if (c == ENTER_KEY) {
			app_info("Help\nthe Help app for MINIOS\nVersion 1.0.0", HELP_APP_ID_TH, 2);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, HELP_APP_ID_SV, 2);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, HELP_APP_ID_NI, 2);
		}
	} else if (userinputmode == HELP_APP_ID_NI) {
		//help about menu if back to app is selected
		if (c == ENTER_KEY) {
			avaliable_commands(1);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, HELP_APP_ID_EI, 2);
		}
	} else {
		//report the error to end user
		warning_box("IM Error", "Error occured in helpim, unexpected UIM");
	}
}