#include <stdlib.h>
#include <stddef.h>

long atol(const char *nptr) {
	strtol(nptr, (char **)NULL, 10);
}