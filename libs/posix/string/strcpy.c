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
 

char *strcpy(char *restrict s1, const char *restrict s2) {
	// return if no memory is allocated to the destination
	if (s1 == NULL || s2 == NULL) {
		return NULL;
	}

	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	
	if (len1 > len2 || len1 < len2) {
		//attempted stack smashing
		return NULL;
	}

	// take a pointer pointing to the beginning of the destination string
	char *ptr = s1;

	// copy the C-string pointed by source into the array
	// pointed by destination
	while (*s2 != '\0' || *s2 != '\n')
	{
		*s1 = *s2;
		s1++;
		s2++;
	}

	// include the terminating null character
	*s1 = '\0';

	// the destination is returned by standard `strcpy()`
	return ptr;
}