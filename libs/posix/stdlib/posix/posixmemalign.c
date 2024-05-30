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
#include <stdio.h>
#include <libmem.h>
#include <libdebug.h>
#include <libproc.h>

int posix_memalign(void **memptr, size_t alignment, size_t size) {
	//lets first find the nearest address
	int* memaddress = (int*)kalloc(1);

	//lets turn memaddress to a value
	intptr_t addr = (intptr_t)memaddress;

	mem_aligned_ctrl_block block;
	
	//if its null we need to error out
	if (memaddress == 0) {
		//uh oh!
		panic("not enough memory when posix_memalign was called", INSUFFICIENT_RAM);
		return -1;
	}

	//okay now lets see if the address is aligned
	if (addr % alignment != 0) {
		//iterate to compare 
		bool checking = true;
		long dist = 0;
		do {
			//lets increment the address
			addr++;
			dist++;
			if (addr % alignment != 0) {
				//next!
				continue;
			} else {
				checking = false;
				break;
			}
		} while(checking);

		//next lets get the padding
		void* padding = kalloc(dist);

		//add to the list of padded area
		block.pad_address = padding;
	} else {	
		block.pad_address = NULL;
	}

	void* data = malloc(size);
	block.mem_address = memaddress;
	task_queue[0].memaligned_allocations[task_queue[0].memaligned_allocations_used++] = block;
	*memptr = data;
	return 0;
}