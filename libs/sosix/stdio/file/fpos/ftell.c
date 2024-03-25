#include <stdio.h>
#include <libssp.h>

long ftell(FILE *stream) {
	return stream->position;
}