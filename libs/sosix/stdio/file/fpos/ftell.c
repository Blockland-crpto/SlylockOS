#include <stdio.h>


long ftell(FILE *stream) {
	return stream->position;
}