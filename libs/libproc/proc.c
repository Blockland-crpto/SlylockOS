/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libproc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <libdebug.h>
#include <libmem.h>
#include <libmodule.h>

//function to create a task
void proc_create(int (*entry_point)(), enum proc_priority priority, int parent) {

	//we need to validate the entry point
	if (entry_point == NULL || priority == 0) {
		//exit, invalid entry point
		return;
	}

	//lets validate the parent id
	if (parent > KERNEL_PROC_ID || parent < 0) {
		//exit invalid parent id
		return;
	}
	
	//number of tasks
	static int task_count;

	//lets find the parent

	//lets allocate a "padding" that protects the other processes in the case of a buffer overflow
	//kalloc(128);

	//lets find a free slot dynamicly
	for (int i = 0; i < MAX_PROCS_QUEUED; i++) {
		if (task_queue[i].entry_point == NULL) {
			//use this slot
			task_count = i;
			break;
		}
		if (i == MAX_PROCS_QUEUED) {
			//no free slot
			panic("no more proc space", TASK_MAX);
		}
	}
	
	//create a new task
	task_queue[task_count].entry_point = entry_point;
	task_queue[task_count].priority = priority;
	task_queue[task_count].status = PROC_STATUS_READY;
	task_queue[task_count].heap_used = 0;
	task_queue[task_count].id = task_count;
	task_queue[task_count].parent_id = parent;
	task_queue[task_count].storage_delegated = 0;
	task_queue[task_count].memory_delegated = 1024;
	task_queue[task_count].subprocesses_delegated = 1;
	task_queue[task_count].subprocesses_active = 0;
	task_queue[task_count].heap_allocations_used = 0;
	task_queue[task_count].acpi_allowed = false;
	task_queue[task_count].file_stream_allocations_used = 0;
}

//function to remove a task
void proc_destroy(int id) {
	//find the task
	task_queue[id].entry_point = NULL;

	//now lets free the memory
	for (size_t i = 0; i <= task_queue[id].heap_allocations_used; i++) {
		kfree(task_queue[id].heap_allocations[i]);
	}

	//lets destroy its subprocesses
	for (int i = 0; i < MAX_PROCS_USABLE; i++) {
		if (task_queue[i].parent_id == id) {
			//lets destroy this process
			task_queue[id].entry_point = NULL;
			
			//now lets free the memory
			for (size_t i = 0; i <= task_queue[id].heap_allocations_used; i++) {
				kfree(task_queue[id].heap_allocations[i]);
			}
		} 
	}
	
	//now lets slide things down
	for (size_t i = 0; i < task_queue[id].subprocesses_active; i++) {
		for (int j = id; j < MAX_PROCS_USABLE; j++) {
			task_queue[j] = task_queue[j + 1];
		}
	}
}

//function to kill the current task
void proc_kill(enum proc_exit_status status) {

	//we need to close its file streams
	for (int i = 0; i < FOPEN_MAX; i++) {
		//is it used?
		if (task_queue[0].file_streams[i] != NULL) {
			fclose(task_queue[0].file_streams[i]);
		}
	}

	errno = EINTR;
	
	//lets skip to next process
	//lets destory the current process
	proc_destroy(task_queue[0].id);

	//lets slide down the process pool
	//lets slide it down!
	for (int i = 0; i < MAX_PROCS_USABLE; i++) {
		task_queue[i] = task_queue[i + 1];
	}

	//lets see if it errored
	switch (status) {
		case PROC_EXIT_STATUS_SUCCESS:
			//exit with success
			break;
		case PROC_EXIT_STATUS_FAILURE:
			//oops!
			break;
		case PROC_EXIT_STATUS_ABORTED:
			//aborted
			break;
		default:
			//panic!!
			panic("oops! a process exited with an invalid status", PROC_RET_INVALID);
	}
	
	//now lets recall the schedualer
	proc_scheduler();
}

//function to yield a process
void proc_yield() {
	//lets switch process queues
	proc_control_block current_proc = task_queue[0];
	task_queue[0] = task_queue[1];
	task_queue[1] = current_proc;

	//lets set the process to yielded
	task_queue[1].status = PROC_STATUS_YIELDED;

	//now lets recall the schedualer
	proc_scheduler();
	
}

//the SlyLockOS process scheduler
void proc_scheduler() {
	static bool initalized;
	if (!initalized) {
		module_t modules_proc = MODULE("kernel.modules.proc", "task scheduler for the kernel (CORE)");
		INIT(modules_proc);
		DONE(modules_proc);
		initalized = true;
	}
	
	while (1) {

		//lets check if the entry point is null
		if (task_queue[0].entry_point == NULL) {
			//if yes, lets continue
			continue;
		}

		//is the current task yielded?
		if (task_queue[0].status == PROC_STATUS_YIELDED) {
			//if yes, we need to break so it can continue
			break;
		}
		
		//set the task as running
		task_queue[0].status = PROC_STATUS_RUNNING;
		
		//call its entry point
		int status = task_queue[0].entry_point();

		//lets see if the task is done
		if (!status) {
			//if yes, we need to slide down the tasks
		} else {
			//if not, we need to eventually provide error info
		}

		//now lets free the memory
		for (size_t i = 0; i <= task_queue[0].heap_allocations_used; i++) {
			kfree(task_queue[0].heap_allocations[i]);
		}
		
		//lets slide it down!
		for (int i = 0; i < MAX_PROCS_USABLE; i++) {
			task_queue[i] = task_queue[i + 1];
		}

		//awesome!
		continue;
 	}
}