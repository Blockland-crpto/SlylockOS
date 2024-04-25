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
#include <system/types.h>
#include <stddef.h>
#include <libssp.h>

unsigned int *acpiGetRSDPtr(void) {
   	unsigned int *addr;
   	unsigned int *rsdp;

   	// search below the 1mb mark for RSDP signature
   	for (addr = (uint32_t *) 0x000E0000; (int) addr<0x00100000; addr += 0x10/sizeof(addr)) {
	  	rsdp = acpiCheckRSDPtr(addr);
	  	if (rsdp != NULL)
		 	return rsdp;
   	}


   	// at address 0x40:0x0E is the RM segment of the ebda
   	int ebda = *((short *) 0x40E);   // get pointer
   	ebda = ebda*0x10 &0x000FFFFF;   // transform segment into linear address

	// search Extended BIOS Data Area for the Root System Description Pointer signature
   	for (addr = (uint32_t *) ebda; (int) addr<ebda+1024; addr+= 0x10/sizeof(addr)) {
	  	rsdp = acpiCheckRSDPtr(addr);
	  	if (rsdp != NULL)
		 	return rsdp;
   	}

   	return NULL;
}