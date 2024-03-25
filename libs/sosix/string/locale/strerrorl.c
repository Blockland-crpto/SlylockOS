#include <string.h>
#include <errno.h>
#include <libssp.h>

char *strerror_l(int errnum, locale_t locale) {
	//todo: add locale function
	return strerror(errnum);
}