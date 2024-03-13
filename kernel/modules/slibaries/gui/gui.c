#include <system/mod.h>
#include <slibaries/gui.h>
#include <system/task.h>

void gui_init() {
	create_task("tui_initalizer", TASK_PRIORITY_KERNEL, TASK_ID_KERNEL);
	module_t modules_gui_gui = MODULE("kernel.modules.gui.gui", "GUI for the kernel (CORE)");
	INIT(modules_gui_gui);
	modify_task(TASK_STATE_ENDED);
}