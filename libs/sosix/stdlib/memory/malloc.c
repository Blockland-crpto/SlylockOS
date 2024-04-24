#include <stdlib.h>
#include <stddef.h>
#include <libmem.h>
#include <libssp.h>
#include <libproc.h>

void *malloc(size_t numbytes) {
	//lets first get the size of the heap amount for the proccess
	proc_control_block current_task = task_queue[0];

	//here it is
	int heap_used = current_task.heap_used;

	if (heap_used + numbytes > 1024) {
		return NULL;
	} else {
		current_task.heap_used += numbytes;
		return kalloc((long)numbytes);
	}
}