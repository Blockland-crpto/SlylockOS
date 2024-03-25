#include <stdlib.h>
#include <stddef.h>
#include <libssp.h>

long long atoll(const char *nptr) {
	return strtoll(nptr, (char **)NULL, 10);
}