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
#include <libmem.h>
#include <libmultiboot.h>
#include <string.h>
#include <libssp.h>


uintptr_t current_break;
int has_initialized = 0;
void *managed_memory_start;
void *last_valid_address;
mem_control_block pmcb; 
	
int ram_size() {
	return (mbi->mem_lower + mbi->mem_upper)+513;
}

void *sbrk(intptr_t incr) {
	uintptr_t old_break = current_break;
    current_break += incr;
    return (void*) old_break;
}

void kalloc_init() {
  	last_valid_address = sbrk(0);
  	managed_memory_start = last_valid_address;
 	has_initialized = 1;  
}


void bzero(void *s, int n) {
  	char * c = s; // Can't work with void *s directly.
  	int i;
  	for (i = 0; i < n; ++i)
   		c[i] = '\0';
}