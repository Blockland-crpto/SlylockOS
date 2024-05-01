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
#include <system/types.h>
#include <libssp.h>
#include <libmem.h>
#include <libmodule.h>

//function to create a task
void proc_create(int (*entry_point)(), int priority, int parent) {

	//we need to validate the entry point
	if (entry_point == NULL) {
		//exit, invalid entry point
		return;
	}

	//lets validate the parent id
	if (parent > 11 || parent < 0) {
		//exit invalid parent id
		return;
	}

	//lets validate the priority
	if (priority > 1 || priority < 0) {
		//exit invalid priority
		return;
	}
	
	//number of tasks
	static int task_count;

	//lets find the parent

	//lets allocate a "padding" that protects the other processes in the case of a buffer overflow
	//kalloc(128);

	//lets find a free slot dynamicly
	for (int i = 0; i <= 10; i++) {
		if (task_queue[i].entry_point == NULL) {
			//use this slot
			task_count = i;
			break;
		}
		if (i == 10) {
			//no free slot
			panic("no more proc space", 10);
		}
	}

	
	//create a new task
	proc_control_block proc;
	proc.entry_point = entry_point;
	proc.priority = priority;
	proc.status = PROC_STATUS_READY;
	proc.heap_used = 0;
	proc.id = task_count;
	proc.parent_id = parent;
	proc.storage_delegated = 0;
	proc.memory_delegated = 1024;
	proc.subprocesses_delegated = 1;
	proc.subprocesses_active = 0;
	proc.heap_allocations_used = 0;
	proc.acpi_allowed = false;
	task_queue[task_count] = proc;
}

//function to remove a task
void proc_destroy(int id) {
	//find the task
	task_queue[id].entry_point = NULL;

	//now lets free the memory
	for (int i = 0; i <= task_queue[id].heap_allocations_used; i++) {
		kfree(task_queue[id].heap_allocations[i]);
	}

	//lets destroy its subprocesses
	for (int i = 0; i < 10; i++) {
		if (task_queue[i].parent_id == id) {
			//lets destroy this process
			task_queue[id].entry_point = NULL;
			
			//now lets free the memory
			for (int i = 0; i <= task_queue[id].heap_allocations_used; i++) {
				kfree(task_queue[id].heap_allocations[i]);
			}
		} 
	}
	
	//now lets slide things down
	for (int i = 0; i < task_queue[id].subprocesses_active; i++) {
		for (int j = id; j < 10; j++) {
			task_queue[j] = task_queue[j + 1];
		}
	}
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

		//now lets free the memory
		for (int i = 0; i <= current_task.heap_allocations_used; i++) {
			kfree(current_task.heap_allocations[i]);
		}
		
		//lets slide it down!
		for (int i = 0; i < 10; i++) {
			task_queue[i] = task_queue[i + 1];
		}

		//awesome!
		continue;
 	}
}