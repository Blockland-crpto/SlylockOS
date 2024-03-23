#include <string.h>
#include <stddef.h>

// Function to implement `strstr()` function
char* strstr(const char *s1, const char *s2) {
	while (*s1 != '\0') {
		if ((*s1 == *s2) && compare(s1, s2)) {
			return s1;
		}
		s1++;
	}

	return NULL;
}