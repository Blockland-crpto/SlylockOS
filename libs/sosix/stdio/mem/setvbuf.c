#include <stdio.h>
#include <drivers/fs/fs.h>

int setvbuf(FILE *restrict stream, char *restrict buf, int type) {
	if (stream == NULL || stream->node == NULL) {
		return EOF;
	}
	stream->bufmod = type;
	fputs(buf, stream);
	return 0;
}