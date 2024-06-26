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
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <libproc.h>
#include <libfs.h>

int fclose(FILE *stream) {
	
	if (stream->node->length == 0) {
		errno = EBADF;
		return EOF;
	}

	if (stream->node->length > BUFSIZ) {
		errno = EFBIG;
		return EOF;
	}
	
	if (stream->stream == NULL) {
		errno = EIO;
		return EOF;
	}

	//lets see if we have enough space on initrd
	void* test = kalloc(stream->node->length);

	//lets see if we have enough space on initrd
	if (test == NULL) {
		//nope
		errno = ENOSPC;
		return EOF;
	}

	
	kfree(test);
	
	//lets look for the file stream
	for (int i = 0; i < FOPEN_MAX; i++) {
		if (task_queue[0].file_streams[i]->name == stream->name) {
			//okay this is it
			task_queue[0].file_streams[i] = NULL;
			task_queue[0].file_stream_allocations_used--;
			break;
		}
	}

	write_fs(stream->node, 0, stream->node->length, stream->stream);
	free(stream->stream);
	free(stream->node);
	free(stream);

	
	return 0;
}