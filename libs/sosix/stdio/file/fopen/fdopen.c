#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

#define MAX_FILE_SIZE 4096

FILE *fdopen(fs_node_t* fd, const char *mode) {
	FILE *file = (FILE *)malloc(sizeof(FILE));
	if (file == NULL) {
		// Out of memory error
		return NULL;
	}

	file->stream = (char *)malloc(MAX_FILE_SIZE); // Allocate buffer for file content
	if (file->stream == NULL) {
		// Out of memory error
		free(file);
		return NULL;
	}

	
	if (strchr(mode, 'r') != NULL) {
		uint32_t sz = read_fs(fd, 0, fd->length, file->stream);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(file->stream);
			free(file);
			return NULL;
		}
		fsetpos(file, (fpos_t*)0);
	} else if (strchr(mode, 'w') != NULL) {
		uint32_t sz = read_fs(fd, 0, fd->length, file->stream);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(file->stream);
			free(file);
			return NULL;
		}
		fsetpos(file, (fpos_t*)0);
	} else if (strchr(mode, 'a') != NULL) {
		// Append to the existing file content if opened in append mode
		uint32_t sz = read_fs(fd, 0, fd->length, file->stream);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(file->stream);
			free(file);
			return NULL;
		}
		fsetpos(file, (fpos_t*)fd->length);
	} else {
		errno = EINVAL; // Invalid mode error
		free(file->stream);
		free(file);
		return NULL;
	}

	file->name = fd->name;
	file->node = fd;
	file->mode = mode;

	return file;
}