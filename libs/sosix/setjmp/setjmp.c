#include <setjmp.h>
 

// Setjmp saves the current state of the CPU registers
int setjmp(jmp_buf env) {
	asm volatile (
		"movl %%ebp, %0 \n\t"   // Save EBP
		"movl %%esp, %1 \n\t"   // Save ESP
		"movl $1f, %2 \n\t"     // Save return address
		"1: \n\t"
		: "=m" (env[JB_BP]), "=m" (env[JB_SP]), "=m" (env[JB_PC])
	);
	return 0;
}
