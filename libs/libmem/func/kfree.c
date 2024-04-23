#include <libmem.h>
#include <libmultiboot.h>
#include <string.h>
#include <libssp.h>

extern mem_control_block pmcb; 

void kfree(void *firstbyte) {
	mem_control_block *mcb;
	mcb = firstbyte - asizeof(pmcb);
	mcb->is_available = 1;
	return;
}