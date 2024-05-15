#include <string.h>
#include <stdint.h>
#include <stddef.h>
 

void *memchr(const void *s, int c, size_t n) {
	
	for (size_t i = 0; i < n; i++) {
		if (((uint8_t *)s)[i] == (uint8_t)c) {
			return (void *)((uintptr_t)s + i);
		}
	}
	return NULL;
}