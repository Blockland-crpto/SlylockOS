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
#include <libdebug.h>

#define MAX_FILE_SIZE 4096

#define fdopen_exit_prep() \
		do {free(file->stream); \
		free(file);}while(0)

#define fdopen_file_check(sz) \
		do { if (!sz) { \
			fdopen_exit_prep(); \
			errnoset(EBADF, "attempted to open a non existent file", NULL); \
		}} while(0)

extern fs_node_t* root_nodes;


FILE *fdopen(int fd, const char *mode) {

	//lets check if the process is allowed to
	if (task_queue[0].file_stream_allocations_used == FOPEN_MAX) {
		//if its used then we cant open any more
		errnoset(EMFILE, "process attempted to access more file streams then allowed", NULL);
	}
	
	FILE *file = (FILE *)malloc(sizeof(FILE));
	if (!file) {
		// Out of memory error
		errnoset(ENOMEM, "Not enought memory to create FILE", NULL);
	}

	file->stream = (uint8_t*)malloc(MAX_FILE_SIZE); // Allocate buffer for file content
	if (!file->stream) {
		// Out of memory error
		free(file);
		errnoset(ENOMEM, "Not enought memory to allocate a stream", NULL);
	}

	fs_node_t* node = (fs_node_t*)malloc(sizeof(fs_node_t));
	
	node = &root_nodes[fd];
	
	if (!node->inode) {
		// Invalid file descriptor error
		fdopen_exit_prep();
		errnoset(EBADF, "Invalid file descriptor", NULL);
	}
	
	if (!strcmp(mode, "r") || !strcmp(mode, "rb")) {
		uint32_t sz = read_fs(node, 0, node->length, file->stream);
		fdopen_file_check(sz);
		fsetpos(file, (fpos_t*)0);
	} else if (!strcmp(mode, "w") || !strcmp(mode, "wb")) {
		uint32_t sz = read_fs(node, 0, node->length, file->stream);
		fdopen_file_check(sz);
		//lets make a fpos_t
		fpos_t pos = { .file = file, .offset = 0 };
		fsetpos(file, &pos);
	} else if (!strcmp(mode, "a") || !strcmp(mode, "ab")) {
		// Append to the existing file content if opened in append mode
		uint32_t sz = read_fs(node, 0, node->length, file->stream);
		fdopen_file_check(sz);
		//lets make a fpos_t
		fpos_t pos = {.file = file, .offset = node->length};
		fsetpos(file, &pos);
		
	} else if (!strcmp(mode, "r+") || !strcmp(mode, "rb+") || !strcmp(mode, "r+b") || !strcmp(mode, "w+") || !strcmp(mode, "wb+") || !strcmp(mode, "w+b")) {
		uint32_t sz = read_fs(node, 0, node->length, file->stream);
		fdopen_file_check(sz);
		//lets make a fpos_t
		fpos_t pos = { .file = file, .offset = 0 };
		fsetpos(file, &pos);

	} else if (!strcmp(mode, "a+") || !strcmp(mode, "ab+") || !strcmp(mode, "a+b")) {
		// Append to the existing file content if opened in append mode
		uint32_t sz = read_fs(node, 0, node->length, file->stream);
		fdopen_file_check(sz);
		//lets make a fpos_t
		fpos_t pos = { .file = file, .offset = node->length };
		fsetpos(file, &pos);

	} else {
		// Invalid mode error
		fdopen_exit_prep();
		errnoset(EINVAL, "recieved a weird mode", NULL);
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