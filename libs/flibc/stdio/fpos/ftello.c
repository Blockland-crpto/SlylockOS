#include <stdio.h>
#include <system/types.h>

off_t ftello(FILE *stream) {
	off_t offset = stream->position;
	return offset;
}