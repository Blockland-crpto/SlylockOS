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
#include <stdarg.h>
#include <stdlib.h>
#include <libfs.h>


//REQUIRES REWRITE

int dprintf(int fd, const char *format, ...) {
	
	FILE* file = fdopen(fd, "w");
	va_list ap;
	va_start(ap, format);
	
	const char *ptr = format;
	int len = 0;
	while(*ptr) {
		if (*ptr == '%') {
			ptr++;
			char buf[256];
			switch (*ptr++) {
				case 's':
					write_fs(file->node, file->length, (sizeof(ap)), (uint8_t*)va_arg(ap, const char *));
					break;
				case 'd':
					write_fs(file->node, file->length, (sizeof(ap)), (uint8_t*)itoa(va_arg(ap, int), buf, 10));
					break;
				case 'x':
					write_fs(file->node, file->length, (sizeof(ap)), (uint8_t*)itoa(va_arg(ap, int), buf, 16));
					break;
				default:
					return EOF;
			}
		} else {
			write_fs(file->node, file->length, (sizeof(ptr+1)), (uint8_t*)ptr++);
			len++;
		}
	}

	va_end(ap);
	fclose(file);
	return len-1;
}
