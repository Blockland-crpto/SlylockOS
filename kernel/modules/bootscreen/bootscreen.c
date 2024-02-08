#include <bootscreen.h>
#include <screen.h>
#include <string.h>
#include <gui.h>


void bootscreen() {
	make_gui(3, 3, 0);
	make_gui_windows("Starting Up", "MiniOS is starting...", 19, 10, 60, 20);
	//gives a chance for the modules to initialize
	for(int i = 0; i < 10000000; i++) {
		__asm__ __volatile__("sti");
	}
	clear(COLOR_WHT, COLOR_BLK);
	set_cursor_pos(0,0);
}