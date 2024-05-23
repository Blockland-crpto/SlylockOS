#include <string.h>
#include <stddef.h>
 

size_t strnlen(const char *s, size_t maxlen) {
	size_t i = 0;
	while (s[i] != '\0' && i < maxlen) ++i;
	return i;
}