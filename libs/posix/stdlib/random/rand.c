/*
* Authors: Alexander Herbert <herbgamerwow@gmail.com>, Matthyos
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
#include <stdint.h>

// From https://stackoverflow.com/a/4768189

unsigned long int rnext;

void srand(unsigned int seed) {
	rnext = seed;
}

int rand(void) { // RAND_MAX assumed to be the max int number
	rnext = rnext * 1103515245 + 12345;
	uint32_t num = (uint32_t)(rnext/65536) % RAND_MAX;
	srand(num);
	return num;
}

int rand_r(unsigned *seed) {
	unsigned sed = *seed;
	sed = sed * 1103515245 + 12345;
	return (uint32_t)(sed/65536) % RAND_MAX;
}
