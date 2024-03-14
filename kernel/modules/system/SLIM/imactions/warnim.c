#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/debug.h>

void warnim(char c, int userinputmode) {
	if (userinputmode == WARN_BOX_ID) {		
		if (c == ENTER_KEY) {
			tui_reset();
		}
	} else {
		//report the error to end user
		warning_box("IM Error", "Error occured in warnim, unexpected UIM");
	}
}