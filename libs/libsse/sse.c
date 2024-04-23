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