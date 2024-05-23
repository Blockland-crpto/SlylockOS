#include <stdlib.h>
#include <stddef.h>
#include <libmem.h>
 
#include <string.h>

void *realloc(void *ptr, size_t numbytes) {
	if (numbytes == 0) {
		free(ptr);
		return NULL;
	}

	if (ptr == NULL) {
		return malloc(numbytes);
	}

	void* new_ptr = malloc(numbytes);
	if (new_ptr == NULL) {
		return NULL;
	}

	// Copy the old data to the new block
	// and free the old block
	memcpy(new_ptr, ptr, numbytes);
	free(ptr);

	return new_ptr;

}