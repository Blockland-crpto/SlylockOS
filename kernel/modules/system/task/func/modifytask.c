#include <system/task.h>
#include <system/debug.h>

void modify_task(task_t task, int state) {
	if (task.priority == TASK_PRIORITY_KERNEL) {
		if (state == TASK_STATE_ERRORED) {
			panic("A Kernel task has Died.\n", TASK_ERROR);
		}
	}
	task.state = state;
}