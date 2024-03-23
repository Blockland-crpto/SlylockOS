#include <stdio.h>

void setbuf(FILE* restrict stream, char *restrict buf) {
	if (buf == NULL) {
		setvbuf(stream, buf, _IONBF);
	} else  {
		setvbuf(stream, buf, _IOFBF);
	}
	return; 
}