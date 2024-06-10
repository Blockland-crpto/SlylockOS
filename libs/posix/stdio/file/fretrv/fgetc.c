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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <libfs.h>

int fgetc(FILE *stream) {
	
	if (stream == NULL || strchr(stream->mode, 'r') == NULL || strchr(stream->mode, '+') == NULL) {
		errnoset(EBADF, "got a bad stream", EOF);
	}

	if ((uint32_t)stream->position >= stream->node->length) {
		errnoset(EOVERFLOW, "attempted stream overflow", EOF); // End of file
	}
	
	uint8_t buf;
	uint32_t sz = read_fs(stream->node, (uint32_t)stream->position, 1, &buf);

	
	if (sz == 0) {
		errnoset(EIO, "bad file read", EOF); //File reading error
	}

	stream->position++;
	return (int)buf; 
	
}