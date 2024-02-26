#include <slibaries/gui.h>
#include <drivers/vga.h>
#include <drivers/perip/timer.h>

void loadingscreen(char *title, char* desc) {
	make_gui(3, 3, 0, 0);
	make_gui_windows(title, desc, 19, 10, 60, 20);
	//gives a chance for the modules to initialize
	loading_bar(35, 22, 15, 500000);
	//loading_bar_two(20, 22, 15);

	//time_sleep(10000000);
	clear(COLOR_WHT, COLOR_BLK);
	set_cursor_pos(0,0);
}