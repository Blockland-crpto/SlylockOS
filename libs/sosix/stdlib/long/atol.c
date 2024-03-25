#include <stdlib.h>
#include <stddef.h>
#include <libssp.h>

long atol(const char *nptr) {
	return strtol(nptr, (char **)NULL, 10);
}