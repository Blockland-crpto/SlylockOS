#include <slibaries/shell.h>
#include <slibaries/gui.h>
#include <drivers/perip/keybrd.h>
#include <drivers/vga.h>

void app_menu(int selected, int uim) {
	userinputmode = uim;
	make_gui_windows("Applications", "\nAbout\nHelp\nLs\nCat\nCalculator\nExit", 10, 10, 25, 20);
	if (selected == 1) {
		putstrpos("About", 12, 14, COLOR_BLU, COLOR_WHT, 12);
	} else if (selected == 2) {
		putstrpos("Help", 12, 15, COLOR_BLU, COLOR_WHT, 12);
	} else if (selected == 3) {
		putstrpos("Ls", 12, 16, COLOR_BLU, COLOR_WHT, 12);
	} else if (selected == 4) {
		putstrpos("Cat", 12, 17, COLOR_BLU, COLOR_WHT, 12);
	} else if (selected == 5) {
		putstrpos("Calculator", 12, 18, COLOR_BLU, COLOR_WHT, 12);
	} else if (selected == 6) {
		putstrpos("Exit", 12, 19, COLOR_BLU, COLOR_WHT, 12);
	}
}