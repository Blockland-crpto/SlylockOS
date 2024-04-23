#include <stdlib.h>
#include <stdint.h>
#include <libmem.h>
#include <libssp.h>

void free(void *ptr) {
	kfree(ptr);
}