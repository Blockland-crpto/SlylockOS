#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <libssp.h>
#include <drivers/fs/fs.h>

int fflush(FILE *stream) {
	uint8_t buff = stream->stream;
	uint32_t size = (strlen((char*)buff) * sizeof(char));
	if (stream->node->length == NULL) {
		errno = EBADF;
		return EOF;
	}
	write_fs(stream->node, 0, size, buff);
	stream->position = 0;
	return 0;
}