#include <stdlib.h>
#include <system/task.h>


__attribute__((__noreturn__))
void abort(void) {
	modify_task(TASK_STATE_ERRORED);
}