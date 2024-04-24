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

#define PROC_STATUS_READY 0
#define PROC_STATUS_RUNNING 1
#define PROC_STATUS_ABORTED 2

#define PROC_PRIORITY_HIGH 0
#define PROC_PRIORITY_LOW 1

#if defined(__cplusplus)
extern "C" {
#endif

	//process control block
	typedef struct {
		//process id
		int id;

		//entry point
		int (*entry_point)();

		//process priority
		int priority;

		//process heap
		void* heap;

		//process status
		int status;
	} proc_control_block;

	//taskqueue
	proc_control_block task_queue[10];

	//function to create a task to task queue
	void proc_create(int (*entry_point)(), int priority);

	//schedualer
	void proc_scheduler();

	

#if defined(__cplusplus)
} /* extern "C" */
#endif
#endif