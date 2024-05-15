#include <stdlib.h>
#include <stdint.h>
#include <libmem.h>
#include <libproc.h>
 

void free(void *ptr) {
	//lets first get the process
	proc_control_block current_task = task_queue[0];

	//lets compare addresses 
	for (int i = 0; i <= current_task.heap_allocations_used; i++) {
		if (current_task.heap_allocations[i] == ptr) {
			//lets free it
			current_task.heap_allocations[i] = NULL;
			kfree(ptr);
			return;
		}
	}
}