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