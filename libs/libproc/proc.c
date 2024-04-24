#include <libproc.h>
#include <system/types.h>
#include <libssp.h>
#include <libmem.h>
#include <libmodule.h>


//function to create a task
void proc_create(int (*entry_point)(), int priority) {

	//number of tasks
	static int task_count;

	//is task_count less then 10?
	if (task_count == 10) {
		//if yes, panic
		panic("too many tasks", 1);
	} 
	
	//create a new task
	proc_control_block proc;
	proc.entry_point = entry_point;
	proc.priority = priority;
	proc.status = PROC_STATUS_READY;
	proc.heap_used = 0;
	proc.id = task_count;

	task_queue[task_count] = proc;
	task_count++;
}

void proc_scheduler() {
	module_t modules_proc = MODULE("kernel.modules.proc", "task schedualer for the kernel (CORE)");
	INIT(modules_proc);
	DONE(modules_proc);
	while (1) {
		//get the current task
		proc_control_block current_task = task_queue[0];

		//lets check if the entry point is null
		if (current_task.entry_point == NULL) {
			//if yes, lets continue
			continue;
		}
		
		//call its entry point
		int status = current_task.entry_point();

		//lets see if the task is done
		if (status == 0) {
			//if yes, we need to slide down the tasks
		} else {
			//if not, we need to eventually provide error info
		}

		task_queue[0] = task_queue[1];
		task_queue[1] = task_queue[2];
		task_queue[2] = task_queue[3];
		task_queue[3] = task_queue[4];
		task_queue[4] = task_queue[5];
		task_queue[5] = task_queue[6];
		task_queue[6] = task_queue[7];
		task_queue[7] = task_queue[8];
		task_queue[8] = task_queue[9];
		task_queue[9] = task_queue[10];

		//awesome!
		continue;
 	}
}