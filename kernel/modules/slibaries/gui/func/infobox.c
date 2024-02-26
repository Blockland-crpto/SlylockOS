#include <drivers/vga.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <slibaries/shell.h>

void infobox(char *title, char *cont, int callerid, int opts) {
	userinputmode = callerid;
	if (opts == 1) {
		make_gui(3, 3, 0, 1);
	} else if (opts == 2) {
		make_gui(3, 3, 0, 3);	
	} else {
		make_gui(3, 3, 0, 0);
	}
	
	make_gui_windows(title, cont, 19, 10, 60, 20);
	set_cursor_pos(22, 15);
}