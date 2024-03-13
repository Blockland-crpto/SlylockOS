#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>
#include <system/task.h>

void shellim(char c, int userinputmode) {
	if (userinputmode == SHELL_APP_ID) {
		//the "desktop"
		if (c == MENU_KEY) {
			main_menu(1, HOME_APP_ID, 3);
		}
	} else if (userinputmode == SHELL_APP_ID_TH) {
		//application menu if about is selected
		if (c == ENTER_KEY) {
			create_task("about", TASK_PRIORITY_APP, TASK_ID_KERNEL);
			about(1);
		} else if (c == ARROW_KEY_DOWN) {
			app_menu(2, SHELL_APP_ID_FR);
		}
	} else if (userinputmode == SHELL_APP_ID_FR) {
		//application menu if help is selected
		if (c == ENTER_KEY) {
			create_task("help", TASK_PRIORITY_APP, TASK_ID_KERNEL);
			avaliable_commands(1);
		} else if (c == ARROW_KEY_UP) {
			app_menu(1, SHELL_APP_ID_TH);
		} else if (c == ARROW_KEY_DOWN) {
			app_menu(3, SHELL_APP_ID_FV);
		}
	} else if (userinputmode == SHELL_APP_ID_FV) {
		//application menu if ls is selected
		if (c == ENTER_KEY) {
			create_task("files", TASK_PRIORITY_APP, TASK_ID_KERNEL);
			ls(0, LS_APP_ID, 1);
		} else if (c == ARROW_KEY_UP) {
			app_menu(2, SHELL_APP_ID_FR);
		} else if (c == ARROW_KEY_DOWN) {
			app_menu(4, SHELL_APP_ID_SX);
		}
	} else if (userinputmode == SHELL_APP_ID_SX) {
		//application menu if cat is selected
		if (c == ENTER_KEY) {
			create_task("cat", TASK_PRIORITY_APP, TASK_ID_KERNEL);
			textbox("cat", "Enter the file location", CAT_APP_ID);
		} else if (c == ARROW_KEY_UP) {
			app_menu(3, SHELL_APP_ID_FV);
		} else if (c == ARROW_KEY_DOWN) {
			app_menu(5, SHELL_APP_ID_SV);
		}
	} else if (userinputmode == SHELL_APP_ID_SV) {
		//application menu if calculator is selected
		if (c == ENTER_KEY) {
			create_task("calc", TASK_PRIORITY_APP, TASK_ID_KERNEL);
			calc_init();
			calc_index = 0;
			calc(CALC_APP_ID, 10);
		} else if (c == ARROW_KEY_UP) {
			app_menu(4, SHELL_APP_ID_SX);
		} else if (c == ARROW_KEY_DOWN) {
			app_menu(6, SHELL_APP_ID_EI);
		}
	} else if (userinputmode == SHELL_APP_ID_EI) {
		//application menu if shell is selected
		if (c == ENTER_KEY) {
			create_task("cmd", TASK_PRIORITY_APP, TASK_ID_KERNEL);
			cmd_init();
		} else if (c == ARROW_KEY_UP) {
			app_menu(5, SHELL_APP_ID_SV);
		} else if (c == ARROW_KEY_DOWN) {
			app_menu(7, SHELL_APP_ID_NI);
		}
	} else if (userinputmode == SHELL_APP_ID_NI) {
		//application menu if calendar is selected
		if (c == ENTER_KEY) {
			create_task("caln", TASK_PRIORITY_APP, TASK_ID_KERNEL);
			caln(CALN_APP_ID, 0);
		} else if (c == ARROW_KEY_UP) {
			app_menu(6, SHELL_APP_ID_EI);
		} else if (c == ARROW_KEY_DOWN) {
			app_menu(8, SHELL_APP_ID_TN);
		}
	} else if (userinputmode == SHELL_APP_ID_TN) {
		//application menu if settings is selected
		if (c == ENTER_KEY) {
			create_task("sett", TASK_PRIORITY_APP, TASK_ID_KERNEL);
			sett(SETT_APP_ID, 0);
		} else if (c == ARROW_KEY_UP) {
			app_menu(7, SHELL_APP_ID_NI);
		} else if (c == ARROW_KEY_DOWN) {
			app_menu(9, SHELL_APP_ID_EL);
		}
	} else if (userinputmode == SHELL_APP_ID_EL) {
		//application menu if exit is selected
		if (c == ENTER_KEY) {
			tui_reset();
		} else if (c == ARROW_KEY_UP) {
			app_menu(8, SHELL_APP_ID_TN);
		}
	} else {
		//report the error to end user
		warning_box("IM Error", "Error occured in shellim, unexpected UIM");
	}
}