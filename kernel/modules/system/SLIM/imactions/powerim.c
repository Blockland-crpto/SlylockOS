#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/debug.h>

void powerim(char c, int userinputmode) {
	if (userinputmode == POWER_APP_ID) {		
		if (c == '\n') {
			shutdown();
		} else if (c == '}') {
			power_menu(2, POWER_APP_ID_TW);
		}
	} else if (userinputmode == POWER_APP_ID_TW) {
		if (c == '\n') {
			reboot();
		} else if (c == '}') {
			power_menu(3, POWER_APP_ID_TH);
		} else if (c == '{') {
			power_menu(1, POWER_APP_ID);
		}
	} else if (userinputmode == POWER_APP_ID_TH) {
		if (c == '\n') {
			tui_reset();
		} else if (c == '{') {
			power_menu(2, POWER_APP_ID_TW);
		}
	} else {
		//todo: send error box
		warn("Error occured in powerim, unexpected UIM");
	}
}