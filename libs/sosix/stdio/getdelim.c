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
#include <system/types.h>
#include <stddef.h>
 

ssize_t getdelim(char **restrict lineptr, size_t *restrict n, int delimiter, FILE *restrict stream) {
	if (lineptr == NULL || n == NULL || stream == NULL) {
		return -1;
	}

	size_t bufsize = 256;  // Initial buffer size
	size_t len = 0;        // Current line length
	char *line = (char*)malloc(bufsize);
	if (line == NULL) {
		return -1;  // Allocation error
	}

	int c;
	while ((c = fgetc(stream)) != EOF) {
		if (len + 1 >= bufsize) {
			bufsize *= 2;  // Double the buffer size
			char *new_line = (char*)realloc(line, bufsize);
			if (new_line == NULL) {
				free(line);
				return -1;  // Reallocation error
			}
			line = new_line;
			*n = bufsize;
		}

		line[len++] = c;
		if (c == delimiter) {
			break;  // Found delimiter, stop reading
		}
	}

	if (len == 0 && c == EOF) {
		free(line);
		return -1;  // No characters read, end of file reached
	}

	line[len] = '\0';  // Null-terminate the string
	*lineptr = line;
	*n = bufsize;
	return (ssize_t)len;
}