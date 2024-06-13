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
#include <stdlib.h>
#include <stddef.h>
#include <libmem.h>
#include <libproc.h>
#include <libdelegate.h>

void *malloc(size_t numbytes) {

	//here it is
	int heap_used = task_queue[0].heap_used;

	if (heap_used + numbytes > task_queue[0].memory_delegated) {

		//lets send a request for more memory to be delegated
		int request_result = delegate_request(RESOURCE_MEMORY, &task_queue[0], numbytes);

		//did it return successful?
		if (request_result == 0) {
			task_queue[0].heap_used += numbytes;
		} else {
			return NULL;
		}
	} else {
		task_queue[0].heap_used += numbytes;
	}

	//todo: see if we can free anything before doing this
	
	//next lets get the kalloc'ed memory
	void* addr = kalloc((long)numbytes);

	//next lets add it to its list
	task_queue[0].heap_allocations[task_queue[0].heap_allocations_used++] = addr;

	//lets return the address
	return addr;
}