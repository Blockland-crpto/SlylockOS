#include <string.h>
#include <stddef.h>

size_t strlen(const char *s) {
	size_t i = 0;
	while (s[i] != '\0') ++i;
	return i;
}