#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

int getchar_unlocked(void) {
	if (stdin->locked == false) {
		return getchar();
	} else {
		return EOF;
	}
}