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
#ifndef __LIBDELEGATE_H__
#define __LIBDELEGATE_H__

#include <system/types.h>
#include <libproc.h>

enum resource_type {
	RESOURCE_MEMORY = 0,
	RESOURCE_STORAGE = 1,
	RESOURCE_SUBPROCS = 2,
	RESOURCE_ACPI = 3,
};

#if defined(__cplusplus)
extern "C" {
#endif

	//function to initalize the delegate
	void delegate_init();

	//function to handle delegate requests
	int delegate_request(enum resource_type type, proc_control_block* proc, size_t amount);
#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif