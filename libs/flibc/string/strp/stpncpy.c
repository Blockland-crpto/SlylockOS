#include <string.h>

char *stpncpy(char *restrict s1, const char *restrict s2, size_t n) {
	int i = 0;
	while (i < n) {
		*s1++ = *s2++;
	}
	return s1 - 1;
}