#include <string.h>
#include <stddef.h>

char* strncpy(char* destination, const char* source, size_t num) {
	char* ptr = destination;
	size_t i;

	for (i = 0; i < num && *source != '\0'; ++i) {
		*ptr++ = *source++;
	}
	for (; i < num; ++i) {
		*ptr++ = '\0';
	}

	return destination;
}
