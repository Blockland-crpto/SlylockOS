#include <string.h>
#include <stdint.h>
#include <stddef.h>
 

//This functions works as a security feature by preventing programs from modifing the memory
//located at the void*.
void* memprotect(const void *s, enum protected_mem_modes mode) {
	static int protected_mem;
	protected_mem_block_t block;
	block.address = s;
	block.mode = mode;
	
	if (protected_mem < 100) {
		protected_mem_blocks[protected_mem] = block;
		protected_mem++;
	}
}