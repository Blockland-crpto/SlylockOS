#include <stdio.h>
#include <libssp.h>

int fputc(int c, FILE *stream) {
	if (stream->position >= BUFSIZ || stream->bufmod == _IONBF) {
		// Buffer is full, flush it
		fflush(stream);
	}
	if (stream->bufmod == _IOLBF && (char)c == '\n') {
		// Buffer has new line, flush it
		fflush(stream);
	}
	uint8_t ch = (uint8_t)c;
	stream->stream[(int)stream->position++] = ch;

	if (stream->position >= BUFSIZ - 1) {
		stream->stream[BUFSIZ - 1] = '\0'; // Null-terminate the buffer
	}
	stream->length++;
	return ch;
}