#include <stdlib.h>
#include <stddef.h>
#include <libmem.h>
#include <libssp.h>

void *malloc(size_t numbytes) {
	return kalloc((long)numbytes);
}