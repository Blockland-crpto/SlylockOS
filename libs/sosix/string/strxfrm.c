#include <stddef.h>
#include <string.h>
#include <locale.h>

//todo: add locale support
size_t strxfrm(char *restrict s1, const char *restrict s2, size_t n) {
	size_t len = strlen(s2);
	if (n == 0) return len;

	size_t result = 0;
	const char *src = s2;
	char *dest = s1;

	// Copy at most n-1 characters, leaving room for the null terminator
	while (n > 1 && *src != '\0') {
		*dest++ = *src++;
		n--;
		result++;
	}

	// Null-terminate the destination string
	if (n > 0) {
		*dest = '\0';
		result++;
	}

	// Return the required buffer size (not including the null terminator)
	return len > result ? len : result;
}
