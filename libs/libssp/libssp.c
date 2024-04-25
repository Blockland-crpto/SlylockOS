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