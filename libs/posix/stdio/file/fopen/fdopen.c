/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <libproc.h>
#include <libfs.h>
#include <libinitrd.h>

#define MAX_FILE_SIZE 4096

extern fs_node_t* root_nodes;

FILE *fdopen(int fd, const char *mode) {

	//lets check if the process is allowed to
	if (task_queue[0].file_stream_allocations_used == FOPEN_MAX) {
		//if its used then we cant open any more
		errno = EMFILE;
		return NULL;
	}
	
	FILE *file = (FILE *)malloc(sizeof(FILE));
	if (file == NULL) {
		// Out of memory error
		errno = ENOMEM;
		return NULL;
	}

	file->stream = (uint8_t*)malloc(MAX_FILE_SIZE); // Allocate buffer for file content
	if (file->stream == NULL) {
		// Out of memory error
		errno = ENOMEM;
		free(file);
		return NULL;
	}

	fs_node_t* node = (fs_node_t*)malloc(sizeof(fs_node_t));
	
	node = &root_nodes[fd];
	
	if (node->inode == 0) {
		// Invalid file descriptor error
		free(file->stream);
		free(file);
		errno = EBADF;
		return NULL;
	}

	
	if (strchr(mode, 'r') != NULL) {
		uint32_t sz = read_fs(node, 0, node->length, file->stream);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(file->stream);
			free(file);
			return NULL;
		}
		fsetpos(file, (fpos_t*)0);
		
	} else if (strchr(mode, 'w') != NULL) {
		uint32_t sz = read_fs(node, 0, node->length, file->stream);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(file->stream);
			free(file);
			return NULL;
		}
		//lets make a fpos_t
		fpos_t pos;
		pos.file = file;
		pos.offset = 0;
		fsetpos(file, &pos);
		
	} else if (strchr(mode, 'a') != NULL) {
		// Append to the existing file content if opened in append mode
		uint32_t sz = read_fs(node, 0, node->length, file->stream);
		if (sz == 0xFFFFFFFF) {
			//File does not exist 
			free(file->stream);
			free(file);
			return NULL;
		}

		//lets make a fpos_t
		fpos_t pos;
		pos.file = file;
		pos.offset = node->length;
		fsetpos(file, &pos);
		
	} else {
		errno = EINVAL; // Invalid mode error
		free(file->stream);
		free(file);
		return NULL;
	}

	file->name = node->name;
	file->node = node;
	file->mode = mode;
	for (int i = 0; i < FOPEN_MAX; i++) {
		if (task_queue[0].file_streams[i] == NULL) {
			task_queue[0].file_streams[i] = file;
			task_queue[0].file_stream_allocations_used++;
			break;
		}
	}
	
	return file;
}