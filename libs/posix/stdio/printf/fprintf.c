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
 

int fprintf(FILE* stream, const char *format, ...) {
	va_list ap;
	va_start(ap, format);

	const char *ptr = format;
	int len = 0;
	while(*ptr) {
		if (*ptr == '%') {
			ptr++;
			char buf[256];
			char* str;
			switch (*ptr++) {
				case 's': {
					fputs(va_arg(ap, const char *), stream);
					break;
				} case 'd': {
					//its the same thing, fall through
				} case 'i': {
					int num = va_arg(ap, int);
					str = itoa(num, buf, 10);
					fputs(str, stream);
					break;
				} case 'x': {
					int num = va_arg(ap, int);
					str = itoa(num, buf, 16);
					fputs(str, stream);
					break;
				} default: {
					return -1;
				}
			}
		} else {
			fputc(*ptr++, stream);
		}
		len++;
	}

	va_end(ap);
	return len;
}