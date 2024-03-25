#include <stddef.h>
#include <string.h>
#include <libssp.h>

char *strrchr(const char *s, int c) {
	const char *last = NULL;
	while (*s != '\0') {
		if (*s == c) {
			last = s;
		}
		s++;
	}
	if (c == '\0') {
		return (char *)s;  // Return a pointer to the null terminator if c is '\0'
	}
	return (char *)last;
}
