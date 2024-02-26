#include <gui.h>
#include <screen.h>
#include <timer.h>

void shutdown_screen() {
	make_gui(3, 3, 0, 0);
	make_gui_windows("Shutting Down", "MiniOS is Shutting down...", 19, 10, 60, 20);
	//gives a chance for the modules to clear commands
	loading_bar(35, 22, 15, 500000);
}