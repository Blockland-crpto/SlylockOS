#include <stdio.h>

int puts(const char* s) {
	while (*s != '\0') {
		if (putchar(*s) == EOF) {
			return EOF;
		}
		++s;
	}
	return 0;
}