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
#include <string.h>
#include <stddef.h>
#include <libdebug.h>
#include <libvalidate.h>

void *memmove(void *s1, const void *s2, size_t n) {
	unsigned char *d = s1;
	const unsigned char *s = s2;

	//lets check if the pointers are null
	if (s1 == NULL || s2 == NULL || n == 0) {
		return NULL;
	}

	//is it valid
	if (!valid_mem_check(s1, n)) {
		return NULL;
	}
	
	if (d == s) {
		return d;
	}

	if (s + n <= d || d + n <= s) {
		return memcpy(d, s, n);
	}

	if (d < s) {
		for (size_t i = 0; i < n; ++i) {
			d[i] = s[i];
		}
	} else {
		for (size_t i = n; i != 0; --i) {
			d[i-1] = s[i-1];
		}
	}

	return d;
}