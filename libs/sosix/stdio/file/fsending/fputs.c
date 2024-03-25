#include <stdio.h>
#include <libssp.h>

int fputs(const char *restrict s, FILE *restrict stream) {
	while (*s != '\0') {
		if (fputc(*s, stream) == EOF) {
			return EOF;
		}
		++s;
	}
	return 0;
}