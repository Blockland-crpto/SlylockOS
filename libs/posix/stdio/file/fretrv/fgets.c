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
#include <string.h>

char *fgets(char *restrict s, int n, FILE *restrict stream) {
	int c = 0;
	int i = 0;

	while (i < n - 1) {
		c = fgetc(stream);
		//added \0 incase its null terminated
		if (c == EOF || c == '\n' || c == '\0') {
			break;
		}
		//check for overflows
		s[i++] = c;
	}

	if (i == 0 && c == EOF) {
		return NULL; // No characters read and EOF reached
	}

	s[i] = '\0'; // Null-terminate the string
	return s;
}