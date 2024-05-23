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
//i know this is very crappy but i just want somthing here
//todo: handle equal responces

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
	typedef struct {
		void* value;
		int id;
	} qsort_t;
	
	if (nel == 0) {
		return;
	}
	//get a array of values
	qsort_t vals[nel];
	for (size_t i = 0; i < nel; i++) {
		vals[i].id = (int)compar((base+i), (base+i+1));
		vals[i].value = (base+i);
		i++;
	}

	int highest;
	qsort_t order[nel];

	for (size_t i = 0; i < nel; i++) {
		if (vals[i].id > highest) {
			highest = vals[i].id;
			vals[nel-1].id = highest;
		}
	}
	
	for (size_t i = 0; i < nel; i++) {
		for (size_t j = 0; j < nel; j++) {
			if (vals[j].id > order[nel-i-1].id) {
				order[nel-i-1] = vals[j];
			}
		}
	}

	//now lets make a array
	for (size_t i = 0; i < nel; i++) {
		memmove(base+i, order[i].value, width);
	}
	return;
}