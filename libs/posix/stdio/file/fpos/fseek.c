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
#include <libdebug.h>

int fseek(FILE *stream, long offset, int whence) {
	if (stream == NULL) {
		//throw error, invalid stream
		dlog("invalid stream for fseek");
		return 1;
	}

	//lets try to lock it
	flockfile(stream);
	
	switch (whence) {
		case SEEK_SET:
			//set the position to the offsetq
			stream->position = offset;
			break;
		case SEEK_CUR:
			//set the position to the current position + offset
			stream->position += offset;
			break;
		case SEEK_END:
			//set the position to the end of offset
			stream->position = stream->length - offset;
			break;
		default:
			//oops, invalid whence
			dlog("Invalid whence for fseek");
			funlockfile(stream);
			return 1;
	}

	funlockfile(stream);
	return 0;
}