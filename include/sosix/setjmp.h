#ifndef __SETJMP_H
#define __SETJMP_H

#if defined(__cplusplus)
extern "C" {
#endif

	#include <stdint.h>
	
	#define JB_BP 0
	#define JB_SP 1
	#define JB_PC 2
	
	// Define a jump buffer type
	typedef uint32_t jmp_buf[6];
	
	int setjmp(jmp_buf env);
	void longjmp(jmp_buf env, int val);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif