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
#include <stddef.h>
#include <ctype.h>
 

unsigned long strtoul(const char *restrict str, char **restrict endptr, int base) {
	unsigned long result = 0;
	int sign = 1;

	// Skip leading whitespace
	while (isspace(*str)) {
		str++;
	}

	// Check for sign
	if (*str == '-') {
		sign = -1;
		str++;
	} else if (*str == '+') {
		str++;
	}

	// Determine base if not provided
	if (base == 0) {
		if (*str == '0') {
			if (*(str + 1) == 'x' || *(str + 1) == 'X') {
				base = 16;
				str += 2;
			} else {
				base = 8;
				str++;
			}
		} else {
			base = 10;
		}
	}

	// Parse digits
	while (isalnum(*str)) {
		int digit;
		if (isdigit(*str)) {
			digit = *str - '0';
		} else {
			digit = tolower(*str) - 'a' + 10;
		}
		if (digit >= base) {
			break;
		}
		result = result * base + digit;
		str++;
	}

	// Set endptr if provided
	if (endptr != NULL) {
		*endptr = (char *)str;
	}

	return sign * result;
}