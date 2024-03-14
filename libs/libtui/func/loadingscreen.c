#include <libtui.h>
#include <drivers/vga.h>
#include <drivers/perip/timer.h>
#include <system/kernel.h>

void loadingscreen(char *title, char* desc) {
	make_tui(themeindex, themeindex, 0, 0);
	make_tui_windows(title, desc, 19, 10, 60, 20);
	//gives a chance for the modules to initialize
	loading_bar(35, 22, 15, 500000);
	clear(COLOR_WHT, COLOR_BLK);
	set_cursor_pos(0,0);
}