#include <stdio.h>
#include <libssp.h>

int putc_unlocked(int c, FILE *stream) {
	if (stream->locked == false) {
		return fputc(c, stream);
	} else {
		return EOF;
	}
}