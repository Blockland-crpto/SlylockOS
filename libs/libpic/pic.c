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
#include <libpic.h>
#include <libports.h>
#include <libmodule.h>
#include <system/types.h>
#include <drivers/cpuid.h>

//pic ports
#define PIC1 0x20
#define PIC2 0xA0

//pic data ports
//note osdev.org shows to do this, lets do it just in case
#define PIC1_DATA (PIC1 + 1)
#define PIC2_DATA (PIC2 + 1)

//static function to check apic (copied from OSdev.org)
static int check_apic(void) {
	unsigned int eax, unused, edx;
	__get_cpuid(1, &eax, &unused, &unused, &edx);
	return edx & CPUID_FEAT_EDX_APIC;
}

//function to initialize the pic driver
void pic_init() {
	module_t modules_pic = MODULE("kernel.modules.pic", "Provides PIC support for the kernel");

	//let the init begin!
	INIT(modules_pic);
	
	//lets see if were using PIC or APIC
	if (check_apic()) {
		//we are using APIC
		//we need to disable PIC
		//this is what the osdev.org code shows
		outb(PIC1_DATA, 0xff);
		outb(PIC2_DATA, 0xff);
		
	}

	//were done!
	DONE(modules_pic);
}