#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <drivers/fs/fs.h>

//test it out
void clearerr(FILE *stream) {
	if (stream == NULL || stream->node == NULL) {
		return;
	}

	uint32_t size = stream->node->length;
	uint8_t *buf = (uint8_t*)malloc(size);
	char* str = (char*)malloc(size + 1);

	if (buf == NULL || str == NULL) {
		// Handle memory allocation failure
		free(buf);
		free(str);
		return;
	}

	uint32_t sz = read_fs(stream->node, 0, size, buf);
	if (sz == 0) {
		// Handle read failure
		free(buf);
		free(str);
		return;
	}

	for (int i = 0; i < sz; i++) {
		str[i] = buf[i];
	}
	str[sz] = '\0';
	str = strremove(str, "EOF");
	str = strremove(str, "[ERROR]:");

	stream->stream = (uint8_t*)str;

	free(buf);
	free(str);
}