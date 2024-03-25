#include <stdint.h>
#include <stdlib.h>
#include <system/debug.h>

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

void stack_chk_init(void);

__attribute__((noreturn)) void __stack_chk_fail(void);
__attribute__((noreturn)) void __stack_chk_fail_local(void);
void __memcpy_chk (void *__restrict__ dest, const void *__restrict__ src, size_t len, size_t slen);