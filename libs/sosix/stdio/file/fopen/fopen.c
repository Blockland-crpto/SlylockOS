#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stddef.h>
#include <libssp.h>
#include <drivers/fs/fs.h>


FILE *fopen(const char *filename, const char *mode) {
	FILE* file = (FILE*)malloc(sizeof(FILE));
	if (file == NULL) {
		free(file);
		return NULL; // Allocation failed
	}

	fs_node_t *fsnode = finddir_fs(fs_root, filename);
	if (fsnode == NULL) {
		free(file); // Clean up allocated memory
		return NULL; // File not found
	}

	char* buff = (char*)malloc(fsnode->length);
	if (buff == NULL) {
		free(file); // Clean up allocated memory
		free(buff); // Clean up allocated memory
		return NULL; // Allocation failed
	}
	
	if (strchr(mode, 'r') != NULL) {
		uint32_t sz = read_fs(fsnode, 0, fsnode->length, buff);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(buff);
			free(file);
			return NULL;
		}
		file->mode = 'r';
		// Handle reading data into the buffer
		fsetpos(file, (fpos_t*)0);
	}

	if (strchr(mode, 'w') != NULL) {
		uint32_t sz = read_fs(fsnode, 0, fsnode->length, buff);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(buff);
			free(file);
			return NULL;
		}
		file->mode = 'w';
		// Handle writing data
		fsetpos(file, (fpos_t*)0);
	}

	if (strchr(mode, 'a') != NULL) {
		uint32_t sz = read_fs(fsnode, 0, fsnode->length, buff);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(buff);
			free(file);
			return NULL;
		}
		fsetpos(file, (fpos_t*)fsnode->length);
		file->mode = 'a';
		// Handle appending data
	}

	file->name = filename;
	file->node = fsnode;
	file->mode = mode;
	file->stream = buff; // Store the buffer in the file stream
	
	free(buff);
	return file;
}