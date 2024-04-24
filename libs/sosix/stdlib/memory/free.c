#include <stdlib.h>
#include <stdint.h>
#include <libmem.h>
#include <libproc.h>
#include <libssp.h>

static mem_control_block emcb;

void free(void *ptr) {
	//lets first get the value of the heap amount for the proccess
	proc_control_block current_task = task_queue[0];

	//here it is
	int heap_used = current_task.heap_used;
	
	mem_control_block *mcb;
	mcb = ptr - asizeof(emcb);
	current_task.heap_used = heap_used - mcb->size;
	kfree(ptr);
}