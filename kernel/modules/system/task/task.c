#include <system/task.h>
#include <system/mod.h>
#include <system/debug.h>


void task_init() {
	module_t module_task_task = MODULE("kernel.modules.task.task", "Provides task management for the kernel (CORE)");
	free_task.name = "free_task";
	free_task.state = TASK_STATE_FREE;
	
	for (int i = 1; i < 256; i++) {
		free_task.id = i;
		taskpool[i] = free_task;
	}
	
	create_task("task_manager", TASK_PRIORITY_KERNEL, TASK_ID_KERNEL);
	running_tasks = 1;
	INIT(module_task_task);
}