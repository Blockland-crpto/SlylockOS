#include <stdlib.h>
#include <stdint.h>
#include <system/mem.h>

void free(void *ptr) {
	kfree(ptr);
}