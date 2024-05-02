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

#ifndef __LIBAPIC_H__
#define __LIBAPIC_H__

#include <system/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

	//MADT informatiom that contains the apic address
	unsigned long* apic_address;
	unsigned long apic_flags;
	int8_t starting_core_apic_id;
	unsigned long starting_core_apic_flags;
	
	//function to initialize the apic drivers
	void apic_init();
	

#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif