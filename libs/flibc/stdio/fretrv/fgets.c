#include <stdio.h>

char *fgets(char *restrict s, int n, FILE *restrict stream) {
	int c;
	int i = 0;

	while (i < n - 1) {
		c = fgetc(stream);
		if (c == EOF) {
			break;
		}
		s[i++] = c;
		if (c == '\n') {
			break;
		}
	}

	if (i == 0 && c == EOF) {
		return NULL; // No characters read and EOF reached
	}

	s[i] = '\0'; // Null-terminate the string
	return s;
}