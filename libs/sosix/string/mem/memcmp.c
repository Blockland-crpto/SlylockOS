#include <string.h>
#include <stdint.h>
#include <libssp.h>

int memcmp(const void *s1, const void *s2, size_t n) {
	
	uint8_t *p = (uint8_t*)s1;
	uint8_t *q = (uint8_t*)s2;
	int charCompareStatus = 0;
	
	if (p == q) {
		return charCompareStatus;
	}
	
	while (n > 0) {
		if (*p != *q) {
			charCompareStatus = (*p >*q)?1:-1;
			break;
		}
		n--;
		p++;
		q++;
	}
	
	return charCompareStatus;
}