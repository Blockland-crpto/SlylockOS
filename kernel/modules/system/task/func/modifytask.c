#include <system/task.h>
#include <system/debug.h>

void modify_task(int state) {
	if (state == TASK_STATE_ENDED) {
		taskpool[current_task.id] = free_task;
		
	}
	if (current_task.priority == TASK_PRIORITY_KERNEL && state == TASK_STATE_ERRORED) {
		panic("A Kernel task has Died.\n", TASK_ERROR);
		
	} 
	current_task.state = state;
}