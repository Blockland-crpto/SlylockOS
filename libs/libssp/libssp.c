#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <libdebug.h>
#include <libssp.h>
#include <string.h>

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;


__attribute__((noreturn)) void __stack_chk_fail(void) {
	panic("Stack smashing detected", SSP_ERROR);
}

__attribute__((noreturn)) void __stack_chk_fail_local(void) {
	panic("Stack smashing detected in local", SSP_LOCAL_ERROR);
}

void __memcpy_chk (void *__restrict__ dest, const void *__restrict__ src, size_t len, size_t slen) {
	if (len > slen) {
		panic("Invalid memory access by memcpy, length is bigger then starting length", 10);
	}
	return memcpy(dest, src, len);
}