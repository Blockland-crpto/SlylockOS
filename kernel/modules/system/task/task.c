#include <system/task.h>
#include <system/mod.h>
#include <system/debug.h>


void task_init() {
	module_t module_task_task = MODULE("kernel.modules.task.task", "Provides task management for the kernel (CORE)");
	create_task("task_manager", TASK_PRIORITY_KERNEL, TASK_ID_KERNEL, 1);
	INIT(module_task_task);
}