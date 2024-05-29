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
#include <stdint.h>
#include <stddef.h>
#include <string.h>
 

char *gets(char *s) {
	//to check for overflows
	size_t len = strlen(s);
	if (len > BUFSIZ) {
		//its a overflow attempt
		return NULL;
	}
	if (s == NULL) {
		return NULL;
	}

	// Use fgets to read at most one less than the size of the buffer
	if (fgets(s, SIZE_MAX, stdin) == NULL) {
		return NULL;  // Error or end of file
	}

	// Remove the newline character if it was read
	if (len > 0 && s[len - 1] == '\n') {
		s[len - 1] = '\0';
	}

	return s;
}
