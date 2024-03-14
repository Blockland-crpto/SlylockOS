#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/debug.h>

void cmdim(char c, int userinputmode) {
	if (userinputmode == CMD_APP_ID) {
		//cmd once finished
		if (c == ENTER_KEY) {
			cmd_init();
		} else if (c == MENU_KEY) {
			main_menu(1, CMD_APP_ID_TW, 1);
		}
	} else if (userinputmode == CMD_APP_ID_TW) {
		//cmd menu if exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, CMD_APP_ID_TH, 1);
		}
	} else if (userinputmode == CMD_APP_ID_TH) {
		//cmd menu if about is selected
		if (c == ENTER_KEY) {
			app_info("Command Line Interface\nfor MINIOS\nVersion 1.0.0", CMD_APP_ID_FV, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, CMD_APP_ID_TW, 1);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, CMD_APP_ID_FR, 1);
		}
	} else if (userinputmode == CMD_APP_ID_FR) {
		//cmd menu if back is selected
		if (c == ENTER_KEY) {
			cmd_init();
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, CMD_APP_ID_TH, 1);
		}
	} else if (userinputmode == CMD_APP_ID_FV) {
		//cmd about
		if (c == MENU_KEY) {
			main_menu(1, CMD_APP_ID_SX, 2);
		}
	} else if (userinputmode == CMD_APP_ID_SX) {
		//cmd about menu if Exit app is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(2, CMD_APP_ID_SV, 2);
		}
	} else if (userinputmode == CMD_APP_ID_SV) {
		//cmd about menu if back is selected
		if (c == ENTER_KEY) {
			app_info("Command Line Interface\nfor MINIOS\nVersion 1.0.0", CMD_APP_ID_FV, 1);
		} else if (c == ARROW_KEY_UP) {
			main_menu(1, CMD_APP_ID_SX, 2);
		} else if (c == ARROW_KEY_DOWN) {
			main_menu(3, CMD_APP_ID_EI, 2);
		}
	} else if (userinputmode == CMD_APP_ID_EI) {
		//cmd about menu if back to app is selected
		if (c == ENTER_KEY) {
			cmd_init();
		} else if (c == ARROW_KEY_UP) {
			main_menu(2, CMD_APP_ID_SV, 2);
		}
	}
}