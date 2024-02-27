#include <slibaries/shell.h>
#include <slibaries/gui.h>
#include <drivers/perip/keybrd.h>
#include <drivers/vga.h>

void app_menu(int selected, int uim) {
	userinputmode = uim;
	make_gui_windows("Applications", "\nAbout\nHelp\nLs\nCat\nCalculator", 10, 10, 25, 20);
	if (selected == 1) {
		putstrpos("About", 12, 14, COLOR_BLU, COLOR_WHT, 12);
	}
}