#include <stdlib.h>
#include <stdint.h>
#include <libmem.h>
#include <libproc.h>
 

void free(void *ptr) {

	//lets compare addresses 
	for (size_t i = 0; i <= task_queue[0].heap_allocations_used; i++) {
		if (task_queue[0].heap_allocations[i] == ptr) {
			//lets free it
			task_queue[0].heap_allocations[i] = NULL;
			kfree(ptr);
			return;
		}
	}
}