#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

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

	s[i] = '\0'; // Null-terminate the string
	return s;
}