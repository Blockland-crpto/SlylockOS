#include <libtui.h>
#include <shell/shell.h>
#include <drivers/perip/keybrd.h>
#include <string.h>

void textinputhandler(char *input, int uim) {
	if (uim == CAT_APP_ID) {
		lastcatfile = input;
		cat(input);
	}
	
}