#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

int fgetc(FILE *stream) {
	uint8_t buf;
	if (strchr(stream->mode, "r") == NULL) {
		errno = EBADF;
		return EOF;
	}
	read_fs(stream->node, stream->position, 1, buf);
	if (buf == EOF) {
		strcat((char*)stream->stream, EOF);
		return EOF;
	}
	return (int)buf; 
	
}