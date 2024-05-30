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
 

static int my_fscanf_int(FILE *stream, int *result) {
	int ch;
	int value = 0;
	int sign = 1;
	int success = 0;

	// Skip leading whitespace
	while ((ch = fgetc(stream)) != EOF && isspace(ch));

	// Check for sign
	if (ch == '-') {
		sign = -1;
		ch = fgetc(stream);
	}

	// Read digits
	while (ch != EOF && isdigit(ch)) {
		value = value * 10 + (ch - '0');
		ch = fgetc(stream);
		success = 1;
	}

	// Handle non-digit character
	if (ch != EOF && !isspace(ch)) {
		// Non-digit character encountered, reset stream position
		fseek(stream, -1, SEEK_CUR);
	}

	*result = value * sign;
	return success;
}

static int my_fscanf_string(FILE *stream, char *result) {
	int ch;
	int count = 0;
	int success = 0;

	// Skip leading whitespace
	while ((ch = fgetc(stream)) != EOF && isspace(ch));

	// Read characters until whitespace
	while (ch != EOF && !isspace(ch)) {
		*result++ = ch;
		count++;
		ch = fgetc(stream);
		success = 1;
	}

	// Null-terminate the string
	*result = '\0';

	// Handle non-whitespace character
	if (ch != EOF && !isspace(ch)) {
		// Non-whitespace character encountered, reset stream position
		fseek(stream, -1, SEEK_CUR);
	}

	return success;
}

int vfscanf(FILE *restrict stream, const char *restrict format, va_list args) {

	int count = 0;
	const char *ptr = format;
	if (stream == NULL || format == NULL) {
		return count;
	} 

	while (*ptr != '\0') {
		if (*ptr != '%') {
			// Regular character, match with input stream
			int ch = fgetc(stream);
			if (ch == EOF || ch != *ptr) {
				break;  // Failed to match, stop scanning
			}
		} else {
			// Format specifier, process accordingly
			ptr++;  // Move past '%'
			if (*ptr == 'd') {
				// Integer conversion
				int *arg = va_arg(args, int*);
				if (my_fscanf_int(stream, arg) != 1) {
					break;  // Failed to read integer, stop scanning
				}
				count++;
			} else if (*ptr == 's') {
				// String conversion
				char *arg = va_arg(args, char*);
				if (my_fscanf_string(stream, arg) != 1) {
					break;  // Failed to read string, stop scanning
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

