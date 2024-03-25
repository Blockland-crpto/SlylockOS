#include <stdio.h>
#include <libssp.h>

int feof(FILE *stream) {
	return stream->eof ? 1 : 0;
}