#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <libssp.h>

void *memccpy(void *restrict s1, const void *restrict s2, int c, size_t n) {
	
	int i = 0;
	uint8_t* p1 = (uint8_t*)s1;
	uint8_t* p2 = (uint8_t*)s2;
	
	while (p2[i] != (uint8_t)c && i < n) {
		p1[i]=p2[i];
		i++;
	}
	if (i == n-1) {
		return NULL;
	}
	return s1;
}