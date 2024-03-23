#include <string.h>
#include <stdint.h>

void *memcpy(void *restrict s1, const void *restrict s2, size_t n) {
	uint8_t *p1 = (uint8_t*)s1;
	uint8_t *p2 = (uint8_t*)s2;
  	for (size_t i = 0; i < n; i++) {
		p1[i]=p2[i];
	}
  	return s1;
}