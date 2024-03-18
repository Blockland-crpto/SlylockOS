#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

int putc_unlocked(int c, FILE *stream) {
	if (stream->locked == false) {
		return fputc(c, stream);
	} else {
		return EOF;
	}
}