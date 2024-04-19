#include <libmem.h>
#include <libmultiboot.h>
#include <string.h>
#include <libssp.h>


uintptr_t current_break;
int has_initialized = 0;
void *managed_memory_start;
void *last_valid_address;
mem_control_block pmcb; 
	
int ram_size() {
	return (mbi->mem_lower + mbi->mem_upper)+513;
}

void *sbrk(intptr_t incr) {
	uintptr_t old_break = current_break;
    current_break += incr;
    return (void*) old_break;
}

void kalloc_init() {
  	last_valid_address = sbrk(0);
  	managed_memory_start = last_valid_address;
 	has_initialized = 1;  
}


void bzero(void *s, int n) {
  	char * c = s; // Can't work with void *s directly.
  	int i;
  	for (i = 0; i < n; ++i)
   		c[i] = '\0';
}