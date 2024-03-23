#include <stdlib.h>
 


__attribute__((__noreturn__))
void abort(void) {
	__asm__ __volatile__("hlt");
}