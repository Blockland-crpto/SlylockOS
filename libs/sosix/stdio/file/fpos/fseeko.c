#include <stdio.h>
#include <libssp.h>
#include <system/types.h>

int fseeko(FILE *stream, off_t offset, int whence) {
	return fseek(stream, (long)offset, whence);
}