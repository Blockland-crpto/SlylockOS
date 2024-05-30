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
#include <string.h>
#include <libfs.h>

int mkstemp(char *temp) {
	static int numberid;
	char buf[256];
	char* strfound = strstr(temp, "xxxxxx");
	if (strfound == NULL) {
		return 0;
	}
	temp = rstrstr(temp, "xxxxxx");
	char* strid = itoa(numberid, buf, 10);
	strcat(temp, strid); 
	numberid++;
	uint8_t* buffer = (uint8_t*)kalloc(BUFSIZ);
	create_file_fs(temp, buffer, BUFSIZ);
	FILE* newFile = fopen(temp, "w");
	fs_node_t* node = newFile->node;
	int ret = (signed)node->inode;
	fclose(newFile);
	return ret;
}