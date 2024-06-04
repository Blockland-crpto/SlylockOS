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
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "helpers/fscanhelpers.h"


extern int fscanf_dec();
extern int fscanf_flt();
extern int fscanf_hex();
extern int fscanf_int();
extern int fscanf_oct();
extern int fscanf_str();
extern int fscanf_uns();


int fscanf(FILE *restrict stream, const char *restrict format, ...) {
	va_list args;
	va_start(args, format);

	int count = 0;
	const char *ptr = format;

	//lets make sure were not derefrencing a null pointer
	if (ptr == NULL || stream == NULL) {
		va_end(args);
		return EOF;
	}
	
	while (*ptr != '\0') {
		if (*ptr != '%') {
			// Regular character, match with input stream
			int ch = fgetc(stream);
			if (ch == EOF || ch != *ptr) {
				break;  // Failed to match, stop scanning
			}
		} else {	
			ptr++;  // Move past '%'
			static enum types var;

			//lets see the type specifier
			switch (*ptr) {
				case 'h': {
					//lets see if another h is there
					ptr++;
					if (*ptr == 'h') {
						var = TYPE_CHAR;
					} else {
						var = TYPE_SHORT;
					}
					break;
				}
				case 'l': {
					//lets see if another l is there
					ptr++;
					if (*ptr == 'l') {
						var = TYPE_LONGLONG;
					} else {
						var = TYPE_LONG;
					}
					break;
				}
				case 'j': {
					var = TYPE_INTMAX;
					break;
				}
				case 'z': {
					var = TYPE_SIZET;
					break;
				}
				case 't': {
					var = TYPE_PTRDIFF;
					break;
				}
				case 'L': {
					var = TYPE_LONGDOUBLE;
					break;
				}
				default: {
					break;
				}
			}
			
			// Format specifier, process accordingly
			if (*ptr == 'd') {
				// decimal conversion
				//lets check 
				int *arg = va_arg(args, int*);
				if (fscanf_dec(stream, arg) != 1) {
					break;  // Failed to read dec, stop scanning
				}
				count++;
			} else if (*ptr == 'i') {
				//integer conversion
				int *arg = va_arg(args, int*);
				if (fscanf_int(stream, arg) != 1) {
					break; // Failed to read int, stop scanning
				} 
				count++;
			} else if (*ptr == 'o') {
				//octal coversion
				unsigned *arg = va_arg(args, unsigned*);
				if (fscanf_oct(stream, arg) != 1) {
					break; // Failed to read oct, stop scanning
				}
				count++;
			} else if (*ptr == 'u') {
				//unsigned conversion
				unsigned *arg = va_arg(args, unsigned*);
				if (fscanf_uns(stream, arg) != 1) {
					break; // Failed to read uns, stop scanning
				}
				count++;
			} else if (*ptr == 'x') {
				//hex conversion
				unsigned *arg = va_arg(args, unsigned*);
				if (fscanf_hex(stream, arg) != 1) {
					break; // Failed to read hex, stop scanning
				}
				count++;
			} else if (*ptr == 'a' || *ptr == 'e' || *ptr == 'f' || *ptr == 'g' || *ptr == 'A' || *ptr == 'E' || *ptr == 'F' || *ptr == 'G') {
				//float conversion
				float* arg = va_arg(args, float*);
				if (fscanf_flt(stream, arg) != 1) {
					break; // Failed to reaf float, stop scanning
				}
				count++;
			} else if (*ptr == 's') {
				// String conversion
				char *arg = va_arg(args, char*);
				if (fscanf_str(stream, arg) != 1) {
					break;  // Failed to read str, stop scanning
				}
				count++;
			}
			while (isspace(*ptr)) {
				ptr++;
			}
			// Add more format specifiers as needed
		}
		ptr++;  // Move to next format specifier or character
	}

	va_end(args);
	return count;
}

