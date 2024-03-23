#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

int fgetc(FILE *stream) {
	if (strchr(stream->mode, 'r') == NULL) {
		errno = EBADF;
		return EOF;
	}

	if (stream->position >= stream->node->length) {
		return EOF; // End of file
	}
	
	uint8_t buf;
	uint32_t sz = read_fs(stream->node, stream->position, 1, &buf);

	
	if (sz == 0xFFFFFFFF) {
		return EOF; //File reading error
	}

	stream->position++;
	return (int)buf; 
	
}