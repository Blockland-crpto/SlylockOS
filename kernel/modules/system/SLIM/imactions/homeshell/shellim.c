#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void shellim(char c, int userinputmode) {
	if (userinputmode == SHELL_APP_ID) {
		//the "desktop"
		if (c == 'm') {
			main_menu(1, HOME_APP_ID, 3);
		}
	} else if (userinputmode == SHELL_APP_ID_TH) {
		//application menu
		if (c == '\n') {
			about(1);
		} else if (c == '}') {
			app_menu(2, SHELL_APP_ID_FR);
		}
	} else if (userinputmode == SHELL_APP_ID_FR) {
		//application menu if help is selected
		if (c == '\n') {
			avaliable_commands(1);
		} else if (c == '{') {
			app_menu(1, SHELL_APP_ID_TH);
		} else if (c == '}') {
			app_menu(3, SHELL_APP_ID_FV);
		}
	} else if (userinputmode == SHELL_APP_ID_FV) {
		//application menu if ls is selected
		if (c == '\n') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '{') {
			app_menu(2, SHELL_APP_ID_FR);
		} else if (c == '}') {
			app_menu(4, SHELL_APP_ID_SX);
		}
	} else if (userinputmode == SHELL_APP_ID_SX) {
		//application menu if cat is selected
		if (c == '\n') {
			textbox("cat", "Enter the file location", CAT_APP_ID);
		} else if (c == '{') {
			app_menu(3, SHELL_APP_ID_FV);
		} else if (c == '}') {
			app_menu(5, SHELL_APP_ID_SV);
		}
	} else if (userinputmode == SHELL_APP_ID_SV) {
		//application menu if calculator is selected
		if (c == '\n') {
			textbox("Enter the first number", "", CALC_APP_ID);
		} else if (c == '{') {
			app_menu(4, SHELL_APP_ID_SX);
		} else if (c == '}') {
			app_menu(6, SHELL_APP_ID_EI);
		}
	} else if (userinputmode == SHELL_APP_ID_EI) {
		//application menu if exit is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '{') {
			app_menu(5, SHELL_APP_ID_SV);
		}
	} else {
		//todo: send error box
		warn("Error occured in shellim, unexpected UIM");
	}
}