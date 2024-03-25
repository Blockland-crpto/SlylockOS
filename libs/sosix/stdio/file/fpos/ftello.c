#include <stdio.h>
#include <system/types.h>
#include <libssp.h>

off_t ftello(FILE *stream) {
	off_t offset = stream->position;
	return offset;
}