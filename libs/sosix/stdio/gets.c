#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <libssp.h>

char *gets(char *s) {
	if (s == NULL) {
		return NULL;
	}

	// Use fgets to read at most one less than the size of the buffer
	if (fgets(s, SIZE_MAX, stdin) == NULL) {
		return NULL;  // Error or end of file
	}

	// Remove the newline character if it was read
	size_t len = strlen(s);
	if (len > 0 && s[len - 1] == '\n') {
		s[len - 1] = '\0';
	}

	return s;
}
