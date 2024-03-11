#include <slibaries/shell.h>
#include <slibaries/gui.h>
#include <drivers/perip/keybrd.h>
#include <drivers/vga.h>

void app_menu(int selected, int uim) {
	userinputmode = uim;
	make_gui_windows("Applications", "\nAbout\nHelp\nFiles\nText\nCalculator\nCmd\nCalendar\nSettings\nExit", 8, 9, 24, 23);
	if (selected == 1) {
		putstrpos("About", 10, 13, COLOR_BLU, COLOR_WHT, 10);
	} else if (selected == 2) {
		putstrpos("Help", 10, 14, COLOR_BLU, COLOR_WHT, 10);
	} else if (selected == 3) {
		putstrpos("Files", 10, 15, COLOR_BLU, COLOR_WHT, 10);
	} else if (selected == 4) {
		putstrpos("Text", 10, 16, COLOR_BLU, COLOR_WHT, 10);
	} else if (selected == 5) {
		putstrpos("Calculator", 10, 17, COLOR_BLU, COLOR_WHT, 10);
	} else if (selected == 6) {
		putstrpos("Cmd", 10, 18, COLOR_BLU, COLOR_WHT, 10);
	} else if (selected == 7) {
		putstrpos("Calendar", 10, 19, COLOR_BLU, COLOR_WHT, 10);
	} else if (selected == 8) {
		putstrpos("Settings", 10, 20, COLOR_BLU, COLOR_WHT, 10);
	} else if (selected == 9) {
		putstrpos("Exit", 10, 21, COLOR_BLU, COLOR_WHT, 10);
	}
}