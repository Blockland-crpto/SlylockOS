#include <slibaries/gui.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/shell.h>

void tui_shell() {
	make_gui(3, 3, 1, 2);
	userinputmode = SHELL_APP_ID;
}