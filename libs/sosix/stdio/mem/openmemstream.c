#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <libssp.h>
#include <drivers/fs/fs.h>

FILE* open_memstream(char **bufp, size_t *sizep) {
	if (bufp == NULL || sizep == 0) {
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
	file->mode = 'w';
	file->stream = (uint8_t*)bufp;
	file->node = fsnode;
	return file;
}