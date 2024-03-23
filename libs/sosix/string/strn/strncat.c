#include <string.h>
#include <stddef.h>

char *strncat(char* restrict s1, const char* restrict s2, size_t n) {
	// make `ptr` point to the end of the destination string
	char* ptr = s1 + strlen(s1)-n;

	// appends characters of the source to the destination string
	for (size_t i = 0; i < n; i++) {
		*ptr++ = *s2++;
	}

	// the destination is returned by standard `strcat()`
	return s1;
}