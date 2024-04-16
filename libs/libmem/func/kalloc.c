#include <libmem.h>
#include <system/multiboot/multibootinfo.h>
#include <string.h>
#include <libssp.h>

extern int has_initialized;
extern mem_control_block pmcb; 
extern void *last_valid_address;
extern void *managed_memory_start;

void *kalloc(long numbytes) {
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
		memory_location = last_valid_address;
		last_valid_address = last_valid_address + numbytes;
		current_location_mcb = memory_location;
		current_location_mcb->is_available = 0;
		current_location_mcb->size = numbytes;
	}
	memory_location = memory_location + asizeof(pmcb);
	return memory_location;
}