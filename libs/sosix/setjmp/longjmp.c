#include <setjmp.h>
 

// Longjmp restores the state of the CPU registers
void longjmp(jmp_buf env, int val) {
	asm volatile (
		"movl %0, %%ebp \n\t"   // Restore EBP
		"movl %1, %%esp \n\t"   // Restore ESP
		"jmp *%2 \n\t"          // Jump to saved return address
		:
		: "m" (env[JB_BP]), "m" (env[JB_SP]), "m" (env[JB_PC])
	);
}