#include <stdio.h>
#include <libssp.h>

void clearerr(FILE *stream) {
	if (stream == NULL || stream->node == NULL) {
		return;
	}
	stream->error = 0;
}