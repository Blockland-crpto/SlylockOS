#include <stdlib.h>
#include <system/mem.h>

void *malloc(long numbytes) {
	return kalloc(numbytes);
}