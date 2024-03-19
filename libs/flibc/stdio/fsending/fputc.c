#include <stdio.h>

int fputc(int c, FILE *stream) {
	if (stream->position >= BUFSIZ) {
		// Buffer is full, flush it
		fflush(stream);
	}
	uint8_t ch = (uint8_t)c;
	stream->stream[(int)stream->position++] = ch;

	if (stream->position >= BUFSIZ - 1) {
		stream->stream[BUFSIZ - 1] = '\0'; // Null-terminate the buffer
	}
	return ch;
}