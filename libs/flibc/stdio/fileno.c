#include <stdio.h>
#include <drivers/fs/fs.h>

fs_node_t *fileno(FILE* stream) {
	if (stream == NULL) {
		return NULL;
	}
	return stream->node;
}