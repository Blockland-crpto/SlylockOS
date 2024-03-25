#include <stdio.h>
#include <libssp.h>

int getchar_unlocked(void) {
	if (stdin->locked == false) {
		return getchar();
	} else {
		return EOF;
	}
}