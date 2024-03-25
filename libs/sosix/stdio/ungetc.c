#include <stdio.h>
#include <stdint.h>
#include <libssp.h>

int ungetc(int c, FILE *stream) {
	if (c == EOF || stream == NULL) {
		return EOF; // Error: invalid input or no more space in unget buffer
	}

	for (size_t i = stream->length; i > 0; i--) {
		stream->stream[i] = stream->stream[i - 1];
	}
	

	stream->stream[0] = (uint8_t*)c;
	return c;
}