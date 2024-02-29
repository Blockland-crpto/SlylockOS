#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void lsim(char c, int userinputmode) {
	if (userinputmode == LS_APP_ID) {
		  //ls first screen
		  if (c == '<') {
			//Do nothing
		  } else if (c == '>') {
			ls(16, LS_APP_ID_TW, 2);
		  } else if (c == 'm') {
			main_menu(1, LS_APP_ID_FV, 1);
		  }
	} else if (userinputmode == LS_APP_ID_TW) {
		//ls second screen
		if (c == '<') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '>') {
			ls(32, LS_APP_ID_TH, 3);
		} else if (c == 'm') {
			main_menu(1, LS_APP_ID_FV, 1);
		}
	} else if (userinputmode == LS_APP_ID_TH) {
		//ls third screen
		if (c == '<') {
			ls(16, LS_APP_ID_TW, 2);
		} else if (c == '>') {
		//Do nothing
		} else if (c == 'm') {
			main_menu(1, LS_APP_ID_FV, 1);
		}
	} else if (userinputmode == LS_APP_ID_FR)  {
		//ls about menu
		if (c == 'm') {
			main_menu(1, LS_APP_ID_EI, 2);
		}
	} else if (userinputmode == LS_APP_ID_FV) {
		//ls menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, LS_APP_ID_SX, 1);
		}
	} else if (userinputmode == LS_APP_ID_SX) {
		//ls menu if About is selected
		if (c == '\n') {
			app_info("Ls\nthe file manager for MINIOS\nVersion 1.0.0", LS_APP_ID_FR, 2);
		} else if (c == '{') {
			main_menu(1, LS_APP_ID_FV, 1);
		} else if (c == '}') {
			main_menu(3, LS_APP_ID_SV, 1);	
		}
	} else if (userinputmode == LS_APP_ID_SV) {
		//ls menu if back is selected
		if (c == '\n') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '{') {
			main_menu(2, LS_APP_ID_SX, 1);
		}
	} else if (userinputmode == LS_APP_ID_EI) {
		//ls about menu if exit is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, LS_APP_ID_NI, 2);
		}
	} else if (userinputmode == LS_APP_ID_NI) {
		//ls about menu if back is selected
		if (c == '\n') {
			app_info("Ls\nthe file manager for MINIOS\nVersion 1.0.0", LS_APP_ID_FR, 2);
		} else if (c == '{') {
			main_menu(1, LS_APP_ID_EI, 2);
		} else if (c == '}') {
			main_menu(3, LS_APP_ID_TN, 2);
		}
	} else if (userinputmode == LS_APP_ID_TN) {
		//ls about menu if back to app is selected
		if (c == '\n') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '{') {
			main_menu(2, LS_APP_ID_NI, 2);
		}
	} else {
		//todo: send error box
		warn("Error occured in lsim, unexpected UIM");
	}
}