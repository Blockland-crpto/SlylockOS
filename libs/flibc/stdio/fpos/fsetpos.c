#include <stdio.h>


int fsetpos(FILE *stream, const fpos_t *pos) {
	stream->position = pos->offset;
	return 0;
}