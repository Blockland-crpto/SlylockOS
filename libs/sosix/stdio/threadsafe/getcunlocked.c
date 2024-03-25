#include <stdio.h>
#include <libssp.h>

int getc_unlocked(FILE *stream) {
	if (stream->locked == false) {
		return getc(stream);
	} else {
		return EOF;
	}
}