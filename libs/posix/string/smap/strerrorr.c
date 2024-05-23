#include <string.h>
#include <stddef.h>
 
#include <errno.h>

int strerror_r(int errnum, char* strerrbuf, size_t buflen) {
	//todo: add locale function
	const char* err = strerror(errnum);
	if (buflen < strlen(err)) {
		return 1;
	}
	strcpy(strerrbuf, err);
	return 0;
}