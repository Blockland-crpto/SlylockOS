#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <system/debug.h>
#include <libssp.h>


uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void stack_chk_init(void) {
	unsigned short param[7] = {123, 234, 345, 456, 567, 678, 789};
	lcong48(param);
	__stack_chk_guard = lrand48();
	return;
}

__attribute__((noreturn)) void __stack_chk_fail(void) {
	panic("Stack smashing detected", SSP_ERROR);
}

__attribute__((noreturn)) void __stack_chk_fail_local(void) {
	panic("Stack smashing detected in local", SSP_LOCAL_ERROR);
}

void __memcpy_chk (void *__restrict__ dest, const void *__restrict__ src, size_t len, size_t slen) {
	if (len > slen) {
		panic("Invalid memory access", 10);
	}
}