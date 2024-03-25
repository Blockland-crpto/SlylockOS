#include <stdio.h>
#include <libssp.h>

int fsetpos(FILE *stream, const fpos_t *pos) {
	return fseek(stream, pos->offset, SEEK_SET);
}