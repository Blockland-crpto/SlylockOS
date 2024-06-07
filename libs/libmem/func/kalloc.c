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
#include <libmem.h>
#include <libmultiboot.h>
#include <string.h>
//#include <libvalidate.h>
 

extern int has_initialized;
extern mem_control_block pmcb; 
extern void *last_valid_address;
extern void *managed_memory_start;

__attribute__ ((malloc, alloc_size(1))) void *kalloc(long numbytes) {
	void *current_location;
	mem_control_block *current_location_mcb;
	void *memory_location;

	if (!has_initialized) {
		kalloc_init();
	}

	numbytes = numbytes + asizeof(pmcb);
	memory_location = 0;
	current_location = managed_memory_start;

	while (current_location != last_valid_address) {
		current_location_mcb = (mem_control_block *)current_location;
		if (current_location_mcb->is_available) {
			if (current_location_mcb->size >= numbytes) {
				current_location_mcb->is_available = 0;
				memory_location = current_location;
				break;
			}
		}
		current_location = current_location + current_location_mcb->size;
	}

	if (!memory_location) {
		sbrk(numbytes);
		/*
		if (!valid_mem_check(last_valid_address, (size_t)numbytes)) {
			return NULL;
		}
		*/
		memory_location = last_valid_address;
		last_valid_address = last_valid_address + numbytes;
		current_location_mcb = memory_location;
		current_location_mcb->is_available = 0;
		current_location_mcb->size = numbytes;
	}
	memory_location = memory_location + asizeof(pmcb);
	
	return memory_location;
}

void kfree(void *firstbyte) {
	mem_control_block *mcb;
	mcb = firstbyte - asizeof(pmcb);
	int size = mcb->size;
	mcb->is_available = 1;
	memset(mcb, 0, size);
	return;
}