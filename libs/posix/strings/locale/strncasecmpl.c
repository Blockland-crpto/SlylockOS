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

#include <strings.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int strncasecmp_l(const char *s1, const char *s2, size_t n, locale_t locale) {	
	printf(locale);
	char* ls1 = (char*)malloc(strlen(s1) * sizeof(char));
	if (ls1 == NULL) {
		return -1;
	}
	char* ls2 = (char*)malloc(strlen(s2) * sizeof(char));
	if (ls2 == NULL) {
		free(ls1);
		return -1;
	}
	
	if (s1 == NULL || s2 == NULL) {
		//null pointers
		free(ls1);
		free(ls2);
		return -1;
	}
	strncpy(ls1, s1, n);
	strncpy(ls2, s2, n);
	
	int ret = strcasecmp(ls1, ls2);

	free(ls1);
	free(ls2);

	return ret;
}