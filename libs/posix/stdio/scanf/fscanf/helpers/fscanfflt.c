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

int fscanf_flt(FILE *stream, float *result) {

	
	int ch;
	float value = 0;
	int sign = 1;
	int success = 0;
	int exponent = 1;

	// Skip leading whitespace
	while ((ch = fgetc(stream)) != EOF && isspace(ch));

	// Check for sign
	if (ch == '-') {
		sign = -1;
		ch = fgetc(stream);
	}

	int decplace = 0;
	while (ch != EOF && ch != '.') {
		if (isdigit(ch)) {
			decplace++;
		}
	}

	//reset stream position
	fseek(stream, -1, SEEK_CUR);
	
	// Read digits
	while ((ch != EOF && isdigit(ch)) || (ch == '.' || ch == 'E' || ch == 'e')) {
		if (ch == '.') {
			ch = fgetc(stream);
			success = 1;
			continue;
		} else if (ch == 'E' || ch == 'e') {
			int exponent_sign = 1;
			ch = fgetc(stream);
			if (ch == '-') {
				exponent_sign *= -1;
			}
			while (ch != EOF && isdigit(ch)) {
				exponent = exponent * 10 + (ch - '0');
				ch = fgetc(stream);
			}
			exponent *= exponent_sign;
			success = 1;
			break;
		}
		value = value * 10 + (ch - '0');
		ch = fgetc(stream);
		success = 1;
	}
	
	// Handle non-digit character
	if (ch != EOF && !isspace(ch)) {
		// Non-digit character encountered, reset stream position
		fseek(stream, -1, SEEK_CUR);
	}

	//lets divide
	int div = 10;
	for (int i = 0; i < decplace; i++) {
		div *= 10;
	}
	
	if (exponent != 0) {
		for (int i = 0; i < exponent; i++) {
			value = value * value;
		}
	}

	*result = value * sign;
	*result = *result / div;
	
	return success;
}