#include <string.h>
#include <stddef.h>
#include <libssp.h>

char* strncpy(char *restrict s1, const char *restrict s2, size_t n){
	char* ptr = s1;
	size_t i;

	for (i = 0; i < n && *s2 != '\0'; i++) {
		*ptr++ = *s2++;
	}
	for (; i < n; i++) {
		*ptr++ = '\0';
	}

	return &s1[n];
}
