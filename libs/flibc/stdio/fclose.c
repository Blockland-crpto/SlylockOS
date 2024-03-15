#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

//test this
int fclose(FILE *stream) {
	uint8_t* buff = stream->stream;
	uint32_t size = stream->node->length;
	
	if (size == NULL) {
		errno = EBADF;
		return EOF;
	}
	
	if (buff == NULL) {
		errno = EIO;
		return EOF;
	}
	write_fs(stream->node, 0, size, buff);
	return 0;
}