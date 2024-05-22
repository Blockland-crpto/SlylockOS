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
#include <string.h>
#include <libproc.h>
#include <libmem.h>

int putenv(char* string) {
	//lets look through env for a variable with name
	//but we have to get it first
	size_t len = 0;
	while (string[len] != '=') {
		len++;
	}
	char* str = (char*)kalloc(len);
	strncpy(str, string, len);
	
	//lets search the enviorment for this variable name
	for (int i = 0; i < MAX_ENVS; i++) {
		if (strncmp(env[i], str, len) != 0) {
			//lets set it 
			strcpy(env[i], string);
			kfree(str);
			return 0;
		}
	}

	//if we get here, we need to add one
	for (int i = 0; i < MAX_ENVS; i++) {
		if (env[i] == NULL) {
			//yeah!
			strcpy(env[i], string);
			kfree(str);
			return 0;
		}
	}

	//if we get here, we need to return an error
	return 1;
}