#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void *calloc(size_t nelem, size_t elsize) {
	size_t size = nelem * elsize;
	void *ptr = malloc(size);
	if (ptr == NULL) {
		return NULL;
	}
	memset(ptr, 0, size);
	return ptr;
}