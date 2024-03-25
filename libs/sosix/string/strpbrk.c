#include <string.h>
#include <stddef.h>
#include <libssp.h>

char *strpbrk(const char *s1, const char *s2) {
	while (*s1 != '\0') {
		while (*s2 != '\0') {
			if (*s2++ == *s1) {
				return (char *) s1;
			}
			++s1;
		}
	}
	return NULL;
}
