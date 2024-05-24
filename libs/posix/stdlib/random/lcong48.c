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
#include "r48state.h"

extern unsigned long long multiplier;
extern unsigned long long addend;

void lcong48(unsigned short param[7]) {
	// Set the seed values
	_rand48_seed[0] = param[0];
	_rand48_seed[1] = param[1];
	_rand48_seed[2] = param[2];

	// Set the multiplier and addend values
	multiplier = ((unsigned long long)param[3] << 32) | ((unsigned long long)param[4] << 16) | param[5];
	addend = ((unsigned long long)param[6] << 16) | 0x330E;

	// Ensure that the multiplier is odd
	if ((multiplier & 1) == 0) {
		multiplier |= 1;
	}

	// Update the multiplier and addend for the LCG
}