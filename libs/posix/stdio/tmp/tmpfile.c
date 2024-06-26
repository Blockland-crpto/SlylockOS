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
#include <libfs.h>


FILE* tmpfile(void) {
	static int openfiles;
	if (openfiles == TMP_MAX) {
		return NULL;
	}
	FILE* file = (FILE*)malloc(sizeof(FILE));
	if (file == NULL) {
		//ouch! out of memory!
		return NULL;
	}
	char *dir = tempnam("./tmp/", "tmp_");
	char *tmp = tmpnam(dir);
	create_file_fs(tmp, 0, 100);
	file->name = "tmpfile";
	file->mode = "w";
	file->bufmod = _IOFBF;
	file->node = finddir_fs(fs_root, tmp); 
	file->stream = (uint8_t*)malloc(file->node->length);
	if (file->stream == NULL) {
		//ouch! out of memory!
		free(file);
		return NULL;
	}
	openfiles++;
	return file;
}