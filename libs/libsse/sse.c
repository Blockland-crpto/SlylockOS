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
#include <libsse.h>
#include <float.h>
#include <drivers/cpuid.h>
#include <libmodule.h>
#include <system/types.h>
#include <libssp.h>

//static function to check sse (copied from OSdev.org's apic and modified for sse)
static int check_sse(void) {
	unsigned int eax, unused, edx;
	__get_cpuid(1, &eax, &unused, &unused, &edx);
	return edx & CPUID_FEAT_EDX_SSE;
}

// function to initalize the SSE driver
void sse_init() {
	module_t modules_sse = MODULE("kernel.modules.sse", "Provides SSE support for the kernel (CORE)");

	//let the SSE initalization begin!
	INIT(modules_sse);

	//lets check if SSE is supported
	//define a variable for it
	int sse_supported = check_sse();

	//if sse is not supported
	if (sse_supported == 0) {
		//SSE is not supported, gota fail!
		FAIL(modules_sse, "SSE is unsupported");

		//lets return
		return;
	}

	//lets do some inline! (copied from OSdev.org, modified by AI to fit inline asm)
	__asm__ volatile(
		"movl %%cr0, %%eax\n"
		"andw $0xFFFB, %%ax\n"
		"orw $0x2, %%ax\n"
		"movl %%eax, %%cr0\n"
		"movl %%cr4, %%eax\n"
		"orl $0x3000, %%eax\n"
		"movl %%eax, %%cr4\n"
		:
		:
		: "eax"
	);

	//were finished here!
	DONE(modules_sse);
}