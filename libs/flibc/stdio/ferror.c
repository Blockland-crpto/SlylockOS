#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <drivers/fs/fs.h>

int ferror(FILE *stream) {
	char* result = strstr((char*)stream->stream, "[ERROR]");
	if (result == NULL) {
		return 0;
	} else {
		return 1;
	}
}