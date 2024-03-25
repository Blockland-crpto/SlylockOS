#include <stdlib.h>
#include <libssp.h>

void abort(void) {
	_Exit(2);
}