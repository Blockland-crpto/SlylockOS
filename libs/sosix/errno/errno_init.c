#include <errno.h>
#include <libssp.h>

void errno_init() {
	errno = 0;
}