#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <libssp.h>
#include <libfs.h>

int fclose(FILE *stream) {
	uint8_t* buff = stream->stream;
	uint32_t size = stream->node->length;
	
	if (size == 0) {
		errno = EBADF;
		return EOF;
	}
	
	if (buff == NULL) {
		errno = EIO;
		return EOF;
	}
	write_fs(stream->node, 0, size, buff);
	free(stream);
	return 0;
}