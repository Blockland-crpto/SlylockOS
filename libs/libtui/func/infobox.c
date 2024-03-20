#include <drivers/vga.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <shell/shell.h>
#include <system/kernel.h>

void infobox(char *title, char *cont, int callerid, int opts) {
	userinputmode = callerid;
	if (opts == 1) {
		make_tui(themeindex, themeindex, 0, 1);
	} else if (opts == 2) {
		make_tui(themeindex, themeindex, 0, 3);	
	} else {
		make_tui(themeindex, themeindex, 0, 0);
	}
	
	make_tui_windows(title, cont, 19, 10, 60, 20);
	set_cursor_pos(22, 15);
}