#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <libssp.h>

//add error handling
FILE *freopen(const char *restrict pathname, const char *restrict mode, FILE *restrict stream) {
	if (stream == NULL) {
		return NULL;
	}
	
	int result = fflush(stream);
	
	if (result == EOF) {
		return NULL;
	}
	
	if (pathname != NULL) {
		int result = fclose(stream);
		
		if (result == EOF) {
			return NULL;
		}
		
		clearerr(stream);
		
		FILE* newstream = fopen(pathname, mode);
		
		if (newstream == NULL) {
			return NULL;
		}
		
		return newstream;
	} else {
		//TODO: set the stream to be unbuffered
		stream->mode = mode;
	}
	return stream;
}