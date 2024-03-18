#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

FILE *fmemopen(void *restrict buf, size_t size, const char *restrict mode) {
	fs_node_t *fsnode = finddir_fs(fs_root, "sys/membuf");
	FILE *file;
	file->name = "membuf";
	file->mode = mode;
	file->stream = (uint8_t*)buf;
	file->node = fsnode;
	return file;
}
