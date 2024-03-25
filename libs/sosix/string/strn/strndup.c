//modified off the Apple(c) XNU

#include <string.h>
#include <stddef.h>
#include <libssp.h>


char* strndup(const char* s, size_t size) {
	size_t i;
	char* copy;
	for(i = 0; i < size; i++) {
		copy[i] = s[i];
	}
	copy[i++] = '\0';
	return (copy);
}
