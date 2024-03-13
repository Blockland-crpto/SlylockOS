#include <stdlib.h>
#include <system/task.h>


__attribute__((__noreturn__))
void abort(task_t task) {
	modify_task(task, TASK_STATE_ERRORED);
}