#include <slibaries/gui.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <drivers/vga.h>

void power_menu(int selected, int uim) {
	userinputmode = uim;

	make_gui_windows("Power", "\nShutdown\nReboot\nExit", 25, 10, 40, 20);
	if (selected == 1) {
		putstrpos("Shutdown", 27, 14, COLOR_BLU, COLOR_WHT, 37);
	} else if (selected == 2) {
		putstrpos("Reboot", 27, 15, COLOR_BLU, COLOR_WHT, 37);
	} else if (selected == 3) {
		putstrpos("Exit", 27, 16, COLOR_BLU, COLOR_WHT, 37);
	}
}