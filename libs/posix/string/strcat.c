#include <string.h>
 

char* strcat(char *restrict s1, const char *restrict s2) {
	// make `ptr` point to the end of the destination string
	char* ptr = s1 + strlen(s1);

	// appends characters of the source to the destination string
	while (*s2 != '\0') {
		*ptr++ = *s2++;
	}

	// null terminate destination string
	*ptr = '\0';

	// the destination is returned by standard `strcat()`
	return s1;
}