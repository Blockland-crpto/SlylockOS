#include <stdio.h>


int fseek(FILE *stream, long offset, int whence) {
	if (stream == NULL) {
		//throw error, invalid stream
		return 1;
	}
	if (whence == SEEK_SET) {
		stream->position = offset;
		return 0;
	} else if (whence == SEEK_CUR) {
		stream->position += offset;
		return 0;
	} else if (whence == SEEK_END) {
		stream->position = stream->node->length - offset;
		return 0;
	}

	return 1;
}