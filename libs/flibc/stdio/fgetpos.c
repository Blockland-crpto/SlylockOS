#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

int fgetpos(FILE *restrict stream, fpos_t *restrict pos) {
	if (stream->node->length == NULL) {
		errno = EBADF;
		return 1;
	}
	pos->offset = stream->position;
	pos->file = stream;
	return 0;
}