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
 

int vsnprintf(char *restrict s, size_t size, const char *restrict template, va_list ap) {
	const char *ptr = template;
	int len = 0;
	while (*ptr && len <= size) {
		if (*ptr == '%') {
			ptr++;
			char buf[256];
			switch (*ptr++) {
				case 's': {
					const char* str = va_arg(ap, const char *);
					while (*str) {
						*s++ = *str++;
						len++;
					}
					break;
				} case 'd': {
					int num = va_arg(ap, int);
					const char* str = itoa(num, buf, 10);
					while (*str) {
						*s++ = *str++;
						len++;
					}
					break;
				} case 'x': {
					int num = va_arg(ap, int);
					const char* str = itoa(num, buf, 16);
					while (*str) {
						*s++ = *str++;
						len++;
					}
					break;
				} default: {
					return -1;
				}
			}
		} else {
			*s++ = *ptr++;
			len++;
		}
	}
	va_end(ap);
	return len;
}
