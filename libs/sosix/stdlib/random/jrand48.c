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
#include <iso646.h>
 
extern unsigned long long multiplier;
extern unsigned long long addend;

long jrand48(unsigned short xsubi[3]) {
	unsigned long long a = 0x5DEECE66DULL;
	unsigned long long c = 0xBULL;
	//const unsigned long long m = (1ULL << 48);

	if (multiplier != 0 && addend != 0) {
		a = multiplier;
		c = addend;
	}
	
	unsigned long long next = xsubi[0] * a + c;
	xsubi[0] = (unsigned short)(next & 0xFFFF);
	next >>= 16;
	next += xsubi[1] * a + c;
	xsubi[1] = (unsigned short)(next & 0xFFFF);
	next >>= 16;
	next += xsubi[2] * a + c;
	xsubi[2] = (unsigned short)(next & 0xFFFF);

	return (long)(next >> 17) & 0x7FFFFFFF;
}