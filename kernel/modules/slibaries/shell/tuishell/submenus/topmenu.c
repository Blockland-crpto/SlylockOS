#include <slibaries/gui.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <drivers/vga.h>

void main_menu(int selected, int uim, int mode) {
	userinputmode = uim;

	if (mode == 1) {
		make_gui_windows("Mini", "\nExit App\nAbout\nBack", 25, 1, 40, 9);
		if (selected == 1) {
			putstrpos("Exit App", 27, 5, COLOR_BLU, COLOR_WHT, 27);
		} else if (selected == 2) {
			putstrpos("About", 27, 6, COLOR_BLU, COLOR_WHT, 27);
		} else if (selected == 3) {
			putstrpos("Back", 27, 7, COLOR_BLU, COLOR_WHT, 27);
		}
	} else if (mode == 2) {
		make_gui_windows("Mini", "\nExit App\nBack\nBack To App", 25, 1, 40, 9);
		if (selected == 1) {
			putstrpos("Exit App", 27, 5, COLOR_BLU, COLOR_WHT, 27);
		} else if (selected == 2) {
			putstrpos("Back", 27, 6, COLOR_BLU, COLOR_WHT, 27);
		} else if (selected == 3) {
			putstrpos("Back To App", 27, 7, COLOR_BLU, COLOR_WHT, 27);
		}
	} else if (mode == 3) {
		make_gui_windows("Mini", "\nPower Options\nApplications\nBack", 25, 1, 42, 10);
		if (selected == 1) {
			putstrpos("Power Options", 27, 5, COLOR_BLU, COLOR_WHT, 27);
		} else if (selected == 2) {
			putstrpos("Applications", 27, 6, COLOR_BLU, COLOR_WHT, 27);
		} else if (selected == 3) {
			putstrpos("Back", 27, 7, COLOR_BLU, COLOR_WHT, 27);
		}
	}

}