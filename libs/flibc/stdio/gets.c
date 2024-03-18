#include <stdio.h>

char *gets(char *s) {
	if (s == NULL) {
		return NULL;
	}

	int c;
	char *p = s;
	while ((c = getchar()) != '\n' && c != EOF) {
		*p++ = c;
	}

	if (c == EOF && p == s) {
		return NULL;  // No characters read, EOF reached
	}

	*p = '\0';  // Null-terminate the string
	return s;
}