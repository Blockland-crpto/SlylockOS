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
#include <libacpi.h>
#include <libmem.h>
#include <libmodule.h>
#include <libports.h>
#include <libproc.h>
#include <system/types.h>
#include <libvga.h>
#include <libdebug.h>
#include <string.h>
#include <stddef.h>
#include <libssp.h>


//function to check if the ACPI header is valid
int acpiCheckHeader(uint32_t *ptr, char *sig) {

	//lets check if a process initiated the request
	//processes are not allowed to initiate the request
	//as its a kernel only function
	if (task_queue[0].entry_point != NULL) {
		//oops a process initiated the request! we gotta kill the process!
		proc_kill();
	}

	//lets validate the input
	if (ptr == NULL || sig == NULL) {
		//if its invalid, we need to panic
		panic("invalid input for acpi check header", ACPI_ERROR);
	}
	
	if (memcmp(ptr, sig, 4) == 0) {
		char *checkPtr = (char *) ptr;
		int len = *(ptr + 1);
		char check = 0;
		while (0<len--) {
			check += *checkPtr;
			checkPtr++;
		}
		if (check == 0)
			return 0;
	}
	return -1;
}