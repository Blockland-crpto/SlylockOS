#include <system/mod.h>
#include <slibaries/gui.h>


void gui_init() {
	module_t modules_gui_gui = MODULE("kernel.modules.gui.gui", "GUI for the kernel (CORE)");
	INIT(modules_gui_gui);
}