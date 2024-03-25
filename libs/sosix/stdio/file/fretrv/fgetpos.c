#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <libssp.h>

int fgetpos(FILE *restrict stream, fpos_t *restrict pos) {
	if (stream == NULL || stream->node == NULL) {
		errno = EBADF;
		return 1; // Invalid stream
	}
	pos->offset = stream->position;
	pos->file = stream;
	return 0;
}