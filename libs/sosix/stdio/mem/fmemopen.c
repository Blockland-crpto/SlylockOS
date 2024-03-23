#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <drivers/fs/fs.h>

FILE *fmemopen(void *restrict buf, size_t size, const char *restrict mode) {
	if (buf == NULL || size == 0 || mode == NULL) {
		return NULL;
	}

	fs_node_t *fsnode = finddir_fs(fs_root, "sys/membuf");
	if (fsnode == NULL) {
		return NULL;
	}
	
	FILE* file = (FILE*)malloc(sizeof(FILE));
	if (file == NULL) {
		free(file);
		return NULL;
	}
	
	file->name = "membuf";
	file->mode = mode;
	file->stream = (uint8_t*)buf;
	file->node = fsnode;
	return file;
}