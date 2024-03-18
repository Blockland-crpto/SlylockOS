#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

int getc_unlocked(FILE *stream) {
	if (stream->locked == false) {
		return getc(stream);
	} else {
		return EOF;
	}
}