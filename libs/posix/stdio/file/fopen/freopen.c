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
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <libdebug.h>
#include <libfs.h>
#include <libinitrd.h>
#include <libproc.h>

//add error handling
FILE *freopen(const char *restrict pathname, const char *restrict mode, FILE *restrict stream) {
	if (stream == NULL) {
		errnoset(EBADF, "stream is null", NULL);
	}

	if (!strcmp("sys", pathname) || !strcmp("tmp", pathname)) {
		errnoset(EACCES, "attempted to open /sys or /tmp", NULL);
	}

	if (stream->node->flags == FS_DIRECTORY) {
		if (strchr(mode, 'w') != NULL || strchr(mode, 'a') != NULL || strchr(mode, '+') != NULL) {
			//uh oh can't write on a directory
			errnoset(EISDIR, "attemped to get write access to a directory", NULL);
		}
	}

	if (task_queue[0].file_stream_allocations_used >= FOPEN_MAX) {
		//to many files
		errnoset(EMFILE, "process cant open anymore files", NULL);
	}

	if (strlen(pathname) > FILENAME_MAX) {
		//pathname too long
		errnoset(ENAMETOOLONG, "pathname is too long", NULL);
	}

	if (task_queue[0].file_stream_allocations_used == (FOPEN_MAX - 3)) {
		//to many files for system
		errnoset(ENFILE, "system cant open anymore files", NULL);
	}

	if (pathname == NULL || initrd_find(pathname) == NULL) {
		//pathname is non exisitent
		errnoset(ENOENT, "pathname is non exsistent", NULL);
	}

	if (strrchr(pathname, '/') != NULL) {
		//lets iterate through the path name to see if theres a alpha numerical character
		bool nonslash_char = false;
		for (size_t i = 0; i < strlen(pathname); i++) {
			if (isalnum(pathname[i]) == 1) {
				nonslash_char = true;
			}
		}
		if (nonslash_char) {
			//we need to check if this is a actual file
			if (initrd_find(pathname)->flags != FS_FILE) {
				//this is not a file
				errnoset(ENOENT, "pathname has trailing slashes", NULL);
			} else if (initrd_find(pathname)->flags != FS_DIRECTORY) {
				//this is not a directory
				errnoset(ENOTDIR, "pathname has trailing slashes and is not a directory", NULL);
			}
		}
	}
	
	int result = fflush(stream);
	
	if (result == EOF) {
		return NULL;
	}
	
	if (pathname != NULL) {
		int result = fclose(stream);
		
		if (result == EOF) {
			return NULL;
		}
		
		clearerr(stream);
		
		FILE* newstream = fopen(pathname, mode);
		
		if (newstream == NULL) {
			//lets check errno
			if (errno == ENOMEM) {
				// no space
				errnoset(ENOSPC, "no space for new file", NULL);
			}
			
		}

		if (newstream->node->length > SIZE_MAX) {
			//file too big
			errnoset(EOVERFLOW, "new stream file length to big for off_t", NULL);
		}
		
		return newstream;
	} else {
		stream->bufmod = _IONBF;
		stream->mode = mode;
	}
	return stream;
}