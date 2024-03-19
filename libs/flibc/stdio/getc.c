#include <stdio.h>
#include <stddef.h>

int getc(FILE *stream) {
	if (stream == NULL) {
		return EOF;
	}
	return fgetc(stream);
}