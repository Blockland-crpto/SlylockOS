#include <stdio.h>
#include <libfs.h>
#include <libssp.h>

fs_node_t *fileno(FILE* stream) {
	if (stream == NULL) {
		return NULL;
	}
	return stream->node;
}