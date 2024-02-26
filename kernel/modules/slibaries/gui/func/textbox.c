#include <drivers/vga.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <slibaries/shell.h>

void textbox(char *title, char *cont, int callerid) {

	textboxactive = 1;
	userinputmode = callerid;
	make_gui(3, 3, 0, 0);
	make_gui_windows(title, "", 19, 10, 60, 20);
	for (int x = 21; x < 58; x++) {
		putpos('#', 8, 7, x, 14);
		putpos('#', 8, 7, x, 16);
	}

	for (int y = 14; y < 16; y++) {
		putpos('#', 8, 7, 21, y);
		putpos('#', 8, 7, 57, y);
	}

	set_cursor_pos(22, 15);
}