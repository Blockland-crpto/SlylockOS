#include <stdio.h>
#include <string.h>
#include <drivers/fs/fs.h>

int fputc(int c, FILE *stream) {
	uint8_t ch = (uint8_t)c;
	write_fs(stream->node, stream->position, stream->node->length, ch);
	stream->position++;
	return 0;
}