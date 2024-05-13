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
#include <libapic.h>
#include <libmodule.h>
#include <system/types.h>



// function to initalize the APIC driver
void apic_init() {
	module_t modules_apic = MODULE("kernel.modules.apic", "Provides APIC support for the kernel");

	//let the apic initalization begin!
	INIT(modules_apic);

	//apic should already be enabled if its present, SlyLock didn't modify it!

	//lets get the bits we need
	volatile uint32_t spurious_interrupt = (unsigned)0x10000030;

	//lets get the current status of the spurious interrupt
	volatile uint32_t* base = (uint32_t*)apic_address;
	volatile uint32_t offset = 0xf0;
	volatile uint32_t* svr = base + offset;

	//lets see it!
	volatile uint32_t start_svr = *svr;
	start_svr |= spurious_interrupt;
	
	//lets set the spurious interrupt register
	svr = (volatile uint32_t*)start_svr;
	
	DONE(modules_apic);
}