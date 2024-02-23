#include <screen.h>
#include <keyboard.h>
#include <gui.h>
#include <shell.h>

void infobox(char *title, char *cont, int callerid) {
	userinputmode = callerid;
	make_gui(3, 3, 0, 0);
	make_gui_windows(title, cont, 19, 10, 60, 20);
	set_cursor_pos(22, 15);
}