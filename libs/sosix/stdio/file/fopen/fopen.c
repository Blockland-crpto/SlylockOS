#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stddef.h>
#include <libssp.h>
#include <libfs.h>


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

	uint8_t* buff = (uint8_t*)malloc(fsnode->length);
	
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
		file->mode = "r";
		// Handle reading data into the buffer
		//lets make a fpos
		fpos_t pos;
		pos.file = file;
		pos.offset = 0;
		fsetpos(file, &pos);
	}

	if (strchr(mode, 'w') != NULL) {
		uint32_t sz = read_fs(fsnode, 0, fsnode->length, buff);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(buff);
			free(file);
			return NULL;
		}
		file->mode = "w";
		// Handle writing data
		fpos_t pos;
		pos.file = file;
		pos.offset = 0;
		fsetpos(file, &pos);
	}

	if (strchr(mode, 'a') != NULL) {
		uint32_t sz = read_fs(fsnode, 0, fsnode->length, buff);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(buff);
			free(file);
			return NULL;
		}
		fpos_t pos;
		pos.file = file;
		pos.offset = fsnode->length;
		fsetpos(file, &pos);
		file->mode = "a";
		// Handle appending data
	}

	file->name = filename;
	file->node = fsnode;
	file->mode = mode;
	file->stream = buff; // Store the buffer in the file stream
	
	free(buff);
	return file;
}