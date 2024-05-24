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
#include <stddef.h>
#include "rstate.h"

char* rstate;
size_t rstate_size;

char *initstate(unsigned seed, char *state, size_t size) {
	// Calculate the number of integers needed to fill the state array
	size_t num_integers = size / sizeof(int);
	static int num_states;
	rstates[num_states].state = rstate;
	rstates[num_states].size = rstate_size;
	
	rstate = (char*)malloc(num_integers);

	// Initialize the state array
	state[0] = seed & 0xFF;
	state[1] = (seed >> 8) & 0xFF;
	state[2] = (seed >> 16) & 0xFF;
	state[3] = (seed >> 24) & 0xFF;

	for (size_t i = 4; i < num_integers; i++) {
		// Generate pseudo-random values for the state array
		state[i] = (state[i - 4] + state[i - 3] + state[i - 2] + state[i - 1]) & 0xFF;
	}
	for (int i = 0; i < num_integers; i++) {
		rstate[i] = state[i];
	}
	rstate_size = num_integers;
	return state;
}
