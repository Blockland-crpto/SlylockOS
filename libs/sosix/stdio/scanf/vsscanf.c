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
#include <libssp.h>

int vsscanf(const char *restrict str, const char *restrict format, va_list args) {
	int count = 0; // Number of successfully matched and assigned input items
	const char *ptr = format;

	while (*ptr != '\0' && *str != '\0') {
		if (*ptr != '%') {
			// Regular character, match with input string
			if (*str != *ptr) {
				break;  // Failed to match, stop scanning
			}
			str++;  // Move to next character in input string
		} else {
			// Format specifier, process accordingly
			ptr++;  // Move past '%'
			if (*ptr == 'd') {
				// Integer conversion
				int *arg = va_arg(args, int*);
				int value = 0;
				int sign = 1;
				// Check for sign
				if (*str == '-') {
					sign = -1;
					str++;  // Move past sign character
				}
				// Read digits
				while (isdigit(*str)) {
					value = value * 10 + (*str - '0');
					str++;  // Move to next character in input string
				}
				*arg = value * sign;
				count++;
			} else if (*ptr == 's') {
				// String conversion
				char *arg = va_arg(args, char*);
				int count = 0;

				// Skip leading whitespace
				while (isspace(*str)) {
					str++;  // Move to next character in input string
				}

				// Read characters until whitespace
				while (*str != '\0' && !isspace(*str)) {
					*arg++ = *str;
					str++;  // Move to next character in input string
					count++;
				}

				// Null-terminate the string
				*arg = '\0';

				if(count == 0) {
					break;
				}  // Successfully read a string if count > 0
				count++;
			} else if (*ptr == 'c') {
				// Character conversion
				char *arg = va_arg(args, char*);
				*arg = *str;
				str++;  // Move to next character in input string
				count++;
			}
			// Add more format specifiers as needed
		}
		ptr++;  // Move to next format specifier or character in format string
	}

	va_end(args);
	return count;
}
