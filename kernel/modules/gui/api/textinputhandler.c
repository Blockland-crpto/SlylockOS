#include <gui.h>
#include <shell.h>
#include <keyboard.h>

void textinputhandler(char *input[], int uim) {
	//printf("%s", input);
	if (uim == CAT_APP_ID) {
		cat(input);
	}
}