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
#ifndef __LIBPROC_H__
#define __LIBPROC_H__

#include <system/types.h>

//enum for process status
enum proc_status {
	PROC_STATUS_READY,
	PROC_STATUS_RUNNING,
	PROC_STATUS_YIELDED,
	PROC_STATUS_ABORTED,
};

//enum for priority
enum proc_priority {
	PROC_PRIORITY_LOW,
	PROC_PRIORITY_NORMAL,
	PROC_PRIORITY_HIGH,
};

#define MAX_PROCS_QUEUED 10
#define KERNEL_PROC_ID (MAX_PROCS_QUEUED + 1)
#define MAX_PROCS_USABLE (MAX_PROCS_QUEUED - 1)

#if defined(__cplusplus)
extern "C" {
#endif

	//process control block
	typedef struct {
		//process id
		int id;

		//parent proccess id
		int parent_id;

		//entry point
		int (*entry_point)();

		//process priority
		enum proc_priority priority;

		//process status
		enum proc_status status;

		//process heap
		int heap_used;

		//storage delegated
		size_t storage_delegated;

		//memory delegated
		size_t memory_delegated;

		//subprocesses delegated
		size_t subprocesses_delegated;

		//subprocesses active
		size_t subprocesses_active;

		//process allocations
		size_t heap_allocations_used;
	
		//heap allocations
		void* heap_allocations[100];

		//ACPI permissions
		bool acpi_allowed;
	} proc_control_block;

	//taskqueue
	proc_control_block task_queue[MAX_PROCS_QUEUED];

	//function to create a task to task queue
	void proc_create(int (*entry_point)(), enum proc_priority priority, int parent);

	//function to destroy a task from task queue
	void proc_destroy(int id);

	//function to yield a process
	void proc_yield();

	//function to kill the current task
	void proc_kill();
	
	//scheduler
	void proc_scheduler();

#if defined(__cplusplus)
} /* extern "C" */
#endif
#endif