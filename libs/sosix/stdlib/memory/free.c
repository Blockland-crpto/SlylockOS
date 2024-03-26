#include <stdlib.h>
#include <stdint.h>
#include <system/memory.h>
#include <libssp.h>

void free(void *ptr) {
	kfree(ptr);
}