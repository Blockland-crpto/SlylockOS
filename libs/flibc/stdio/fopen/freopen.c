#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stddef.h>
#include <drivers/fs/fs.h>

//add error handling
FILE *freopen(const char *restrict pathname, const char *restrict mode, FILE *restrict stream) {
	fflush(stream);
	if (pathname != NULL) {
		fclose(stream);
		clearerr(stream);
		FILE* newstream = fopen(pathname, mode);
		return newstream;
	} else {
		stream->mode = mode;
	}
	
}