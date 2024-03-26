#include <stdio.h>
#include <stdlib.h>
#include <system/types.h>
#include <stddef.h>
#include <libssp.h>

ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream) {
	if (lineptr == NULL || n == NULL || stream == NULL) {
		return -1;
	}

	size_t bufsize = 256;  // Initial buffer size
	size_t len = 0;        // Current line length
	char *line = malloc(bufsize);
	if (line == NULL) {
		return -1;  // Allocation error
	}

	int c;
	while ((c = fgetc(stream)) != EOF && c != '\n') {
		if (len + 1 >= bufsize) {
			bufsize *= 2;  // Double the buffer size
			char *new_line = realloc(line, bufsize);
			if (new_line == NULL) {
				free(line);
				return -1;  // Reallocation error
			}
			line = new_line;
		}

		line[len++] = c;
	}

	if (len == 0 && c == EOF) {
		free(line);
		return -1;  // No characters read, end of file reached
	}

	line[len] = '\0';  // Null-terminate the string
	*lineptr = line;
	*n = bufsize;
	return len;
}