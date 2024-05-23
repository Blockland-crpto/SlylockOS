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
 

//add error handling
FILE *freopen(const char *restrict pathname, const char *restrict mode, FILE *restrict stream) {
	if (stream == NULL) {
		return NULL;
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
			return NULL;
		}
		
		return newstream;
	} else {
		stream->bufmod = _IONBF;
		stream->mode = mode;
	}
	return stream;
}