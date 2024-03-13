#include <system/task.h>

task_t create_task(char* name, int priority, int caller, int id) {
	task_t newTask;
	newTask.name = name;
	newTask.priority = priority;
	newTask.caller = caller;
	newTask.id = id;
	newTask.state = TASK_STATE_STARTING;
	taskpool[id] = newTask;
	return newTask;
}