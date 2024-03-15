#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stddef.h>
#include <drivers/fs/fs.h>


FILE *fopen(const char *filename, const char *mode) {
	FILE* file = (FILE*)malloc(sizeof(FILE));
	if (file == NULL) {
		return NULL; // Allocation failed
	}

	char* buff = (char*)malloc(4096);
	if (buff == NULL) {
		free(file); // Clean up allocated memory
		return NULL; // Allocation failed
	}

	fs_node_t *fsnode = finddir_fs(fs_root, filename);
	if (fsnode == NULL) {
		free(file); // Clean up allocated memory
		free(buff); // Clean up allocated memory
		return NULL; // File not found
	}

	if (strchr(mode, 'r') != NULL) {
		read_fs(fsnode, 0, fsnode->length, buff);
		// Handle reading data into the buffer
	}

	if (strchr(mode, 'w') != NULL) {
		// Handle writing data
	}

	if (strchr(mode, 'a') != NULL) {
		// Handle appending data
	}

	file->name = filename;
	file->node = fsnode;
	file->mode = mode;
	file->stream = buff; // Store the buffer in the file stream

	return file;
}