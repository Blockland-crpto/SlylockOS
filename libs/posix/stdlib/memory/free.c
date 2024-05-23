#include <stdlib.h>
#include <stdint.h>
#include <libmem.h>
#include <libproc.h>
 

void free(void *ptr) {
	//lets first get the process
	proc_control_block current_task = task_queue[0];

	//lets compare addresses 
	for (size_t i = 0; i <= current_task.heap_allocations_used; i++) {
		if (current_task.heap_allocations[i] == ptr) {
			//lets free it
			current_task.heap_allocations[i] = NULL;
			kfree(ptr);
			return;
		}
	}

	//lets see if it was posix memaligned
	for (size_t i = 0; i <= current_task.memaligned_allocations_used; i++) {
		if (current_task.memaligned_allocations[i].mem_address == ptr) {
			//lets free it
			kfree(current_task.memaligned_allocations[i].mem_address);
			//and its padding
			if (current_task.memaligned_allocations[i].pad_address != NULL) {
				kfree(current_task.memaligned_allocations[i].pad_address);
			}
			
		}
	}
}