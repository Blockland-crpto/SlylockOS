#include <stdlib.h>
#include <stdint.h>
#include <system/mem.h>
#include <libssp.h>

void free(void *ptr) {
	kfree(ptr);
}