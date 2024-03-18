#include <stdio.h>
#include <string.h>
#include <drivers/fs/fs.h>

int fputc(int c, FILE *stream) {
	uint8_t c = (uint8_t)c;
	write_fs(stream->node, stream->position, stream->node->length, c);
	stream->position++;
	return 0;
}