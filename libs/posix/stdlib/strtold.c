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
#include <ctype.h>
#include <stddef.h>
 

long double strtold(const char *restrict nptr, char **restrict endptr) {
	long double result = 0.0;
	int sign = 1;
	int decimal = 0;

	int exponent = 0;
	const char *str = nptr;

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

	// Parse digits before decimal point
	while (isdigit(*str)) {
		result = result * 10 + (*str - '0');
		str++;
	}

	// Parse decimal point and digits after decimal point
	if (*str == '.') {
		str++;
		while (isdigit(*str)) {
			result = result * 10 + (*str - '0');
			decimal++;
			str++;
		}
	}

	int exp_sign = 1;
	
	// Parse exponent
	if (*str == 'e' || *str == 'E') {
		str++;
		if (*str == '-') {
			exp_sign = -1;
			str++;
		} else if (*str == '+') {
			str++;
		}
		while (isdigit(*str)) {
			exponent = exponent * 10 + (*str - '0');
			str++;
		}
		exponent *= exp_sign;
	}

	// Adjust result for decimal and exponent
	while (decimal-- > 0) {
		result /= 10;
	}
	while (exponent > 0) {
		result *= 10;
		exponent--;
	}
	while (exponent < 0) {
		result /= 10;
		exponent++;
	}

	// Set endptr if provided
	if (endptr != NULL) {
		*endptr = (char *)str;
	}

	return sign * result;
}