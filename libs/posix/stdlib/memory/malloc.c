#include <stdlib.h>
#include <stddef.h>
#include <libmem.h>
 
#include <libproc.h>
#include <libdelegate.h>

void *malloc(size_t numbytes) {
	//lets first get the size of the heap amount for the proccess
	proc_control_block current_task = task_queue[0];

	//here it is
	int heap_used = current_task.heap_used;

	if (heap_used + numbytes > current_task.memory_delegated) {

		//lets send a request for more memory to be delegated
		int request_result = delegate_request(RESOURCE_MEMORY, &current_task, numbytes);

		//did it return successful?
		if (request_result == 0) {
			current_task.heap_used += numbytes;
		} else {
			return NULL;
		}
	} else {
		current_task.heap_used += numbytes;
	}

	//next lets get the kalloc'ed memory
	void* addr = kalloc((long)numbytes);

	//next lets add it to its list
	current_task.heap_allocations[current_task.heap_allocations_used++] = addr;

	//lets return the address
	return addr;
}