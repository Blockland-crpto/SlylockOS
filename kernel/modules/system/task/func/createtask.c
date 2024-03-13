#include <system/task.h>

task_t create_task(char* name, int priority, int caller) {
	task_t newTask;
	newTask.name = name;
	newTask.priority = priority;
	newTask.caller = caller;
	newTask.state = TASK_STATE_STARTING;
	for (int i = 0; i < 256; i++) {
		if (taskpool[i].state == TASK_STATE_FREE) {
			newTask.id = i;
			taskpool[i] = newTask;
		}
	}
	current_task = newTask;
	return newTask;
}