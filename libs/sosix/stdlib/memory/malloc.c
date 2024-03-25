#include <stdlib.h>
#include <stddef.h>
#include <system/mem.h>

void *malloc(size_t numbytes) {
	return kalloc((long)numbytes);
}