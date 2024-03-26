#include <stdlib.h>
#include <stddef.h>
#include <system/memory.h>
#include <libssp.h>

void *malloc(size_t numbytes) {
	return kalloc((long)numbytes);
}