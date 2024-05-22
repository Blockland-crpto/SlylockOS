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
#include <errno.h>
#include <stddef.h>
#include <libfs.h>


FILE *fopen(const char *filename, const char *mode) {

	//lets check if the process is allowed to
	if (task_queue[0].file_stream_allocations_used == FOPEN_MAX) {
		//if its used then we cant open any more
		return NULL;
	}
	
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
	task_queue[0].file_stream_allocations_used++;
	task_queue[0].file_streams[task_queue[0].file_stream_allocations_used] = file;
	free(buff);
	return file;
}