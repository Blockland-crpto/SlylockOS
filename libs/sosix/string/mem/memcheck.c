#include <string.h>
#include <stdint.h>
#include <stddef.h>
 

//This functions searches to see if a memory block is protected
enum protected_mem_modes memcheck(const void *s) {
	for (int i = 0; i < 100; i++) {
		if (protected_mem_blocks[i].address == s) {
			return protected_mem_blocks[i].mode;
		}
	}	

	return 0;
}